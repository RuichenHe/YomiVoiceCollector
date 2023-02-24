
#include "YomiVoice.h"
#include "audiolevel.h"

#include "ui_YomiVoice.h"

#include <QAudioProbe>
#include <QAudioRecorder>
#include <QDir>
#include <QFileDialog>
#include <QMediaRecorder>
#include <QStandardPaths>
#include <filesystem>
#include <QMessageBox>
#include <QtWidgets/QRadioButton>
#include <QtMultimedia/qaudiodeviceinfo.h>
#include <QtCore/quuid.h>
#include <QtCore/qfile.h>
#include <fstream>
static qreal getPeakValue(const QAudioFormat& format);
static QVector<qreal> getBufferLevels(const QAudioBuffer& buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T* buffer, int frames, int channels);
//Set the command here.

//Use the function to load the command list from a txt file
AudioRecorder::AudioRecorder()
    : ui(new Ui::AudioRecorder)
{
    ui->setupUi(this);
    
    m_audioRecorder = new QAudioRecorder(this);
    m_probe = new QAudioProbe(this);
    connect(m_probe, &QAudioProbe::audioBufferProbed,
        this, &AudioRecorder::processBuffer);
    m_probe->setSource(m_audioRecorder);

    //audio devices
    for (auto& device : m_audioRecorder->audioInputs()) {
        ui->audioDeviceBox->addItem(device, QVariant(device));
    }
    ui->playbackButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    //Load command list from txt file
    std::ifstream nameFileout;
    QString commandListFileName = QDir::currentPath() + "/" + "commandList.txt";
    qDebug() << commandListFileName;
    nameFileout.open(commandListFileName.toStdString());
    std::string line;
    while (std::getline(nameFileout, line))
    {
        qDebug() << QString::fromStdString(line);
        commandList.push_back(line);
    }
    //audio codecs
    /*for (auto& codecName : m_audioRecorder->supportedAudioCodecs()) {
        ui->audioCodecBox->addItem(codecName, QVariant(codecName));
    }*/

    //containers
    /*for (auto& containerName : m_audioRecorder->supportedContainers()) {
        ui->containerBox->addItem(containerName, QVariant(containerName));
    }*/

    //sample rate
    /*ui->sampleRateBox->addItem(tr("Default"), QVariant(0));
    for (int sampleRate : m_audioRecorder->supportedAudioSampleRates()) {
        ui->sampleRateBox->addItem(QString::number(sampleRate), QVariant(
            sampleRate));
    }*/

    //channels
    /*ui->channelsBox->addItem(tr("Default"), QVariant(-1));
    ui->channelsBox->addItem(QStringLiteral("1"), QVariant(1));
    ui->channelsBox->addItem(QStringLiteral("2"), QVariant(2));
    ui->channelsBox->addItem(QStringLiteral("4"), QVariant(4));*/

    //quality
    //ui->qualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));
    //ui->qualitySlider->setValue(int(QMultimedia::NormalQuality));

    ////bitrates:
    //ui->bitrateBox->addItem(tr("Default"), QVariant(0));
    //ui->bitrateBox->addItem(QStringLiteral("32000"), QVariant(32000));
    //ui->bitrateBox->addItem(QStringLiteral("64000"), QVariant(64000));
    //ui->bitrateBox->addItem(QStringLiteral("96000"), QVariant(96000));
    //ui->bitrateBox->addItem(QStringLiteral("128000"), QVariant(128000));

    connect(m_audioRecorder, &QAudioRecorder::durationChanged, this, &AudioRecorder::updateProgress);
    connect(m_audioRecorder, &QAudioRecorder::statusChanged, this, &AudioRecorder::updateStatus);
    connect(m_audioRecorder, &QAudioRecorder::stateChanged, this, &AudioRecorder::onStateChanged);
    connect(m_audioRecorder, QOverload<QMediaRecorder::Error>::of(&QAudioRecorder::error), this,
        &AudioRecorder::displayErrorMessage);
    QList<QRadioButton*> allButtons = ui->groupBox_2->findChildren<QRadioButton*>();
    for (int i = 0; i < allButtons.size(); ++i)
    {
        connect(allButtons[i], &QRadioButton::clicked, this, &AudioRecorder::onButtonSelected);
    }
    connect(ui->nextLabelButton, &QPushButton::clicked, this, &AudioRecorder::nextLabel);
    connect(ui->pushButton, &QPushButton::clicked, this, &AudioRecorder::preLabel);
    connect(ui->playbackButton, &QToolButton::clicked, this, &AudioRecorder::playRecordedAudio);
    connect(ui->recordButton, &QPushButton::clicked, this, &AudioRecorder::toggleRecord);
}

void AudioRecorder::updateProgress(qint64 duration)
{
    if (m_audioRecorder->error() != QMediaRecorder::NoError || duration < 2000)
        return;

    ui->statusbar->showMessage(tr("Recorded %1 sec").arg(duration / 1000));
}

void AudioRecorder::updateStatus(QMediaRecorder::Status status)
{
    QString statusMessage;

    switch (status) {
    case QMediaRecorder::RecordingStatus:
        statusMessage = tr("Recording to %1").arg(m_audioRecorder->actualLocation().toString());
        break;
    case QMediaRecorder::PausedStatus:
        clearAudioLevels();
        statusMessage = tr("Paused");
        break;
    case QMediaRecorder::UnloadedStatus:
    case QMediaRecorder::LoadedStatus:
        clearAudioLevels();
        statusMessage = tr("Stopped");
    default:
        break;
    }

    if (m_audioRecorder->error() == QMediaRecorder::NoError)
        ui->statusbar->showMessage(statusMessage);
}

void AudioRecorder::onStateChanged(QMediaRecorder::State state)
{
    switch (state) {
    case QMediaRecorder::RecordingState:
        ui->recordButton->setText(tr("Stop"));
        //ui->pauseButton->setText(tr("Pause"));
        break;
    case QMediaRecorder::PausedState:
        ui->recordButton->setText(tr("Stop"));
        //ui->pauseButton->setText(tr("Resume"));
        break;
    case QMediaRecorder::StoppedState:
        ui->recordButton->setText(tr("Record"));
        //ui->pauseButton->setText(tr("Pause"));
        break;
    }

    //ui->pauseButton->setEnabled(m_audioRecorder->state() != QMediaRecorder::StoppedState);
}

static QVariant boxValue(const QComboBox* box)
{
    int idx = box->currentIndex();
    if (idx == -1)
        return QVariant();

    return box->itemData(idx);
}

void AudioRecorder::toggleRecord()
{
    if (m_recordReady == false) {
        return;
    }
    if (m_audioRecorder->state() == QMediaRecorder::StoppedState) {
        m_audioRecorder->setAudioInput(boxValue(ui->audioDeviceBox).toString());

        QAudioEncoderSettings settings;
        settings.setCodec("audio/pcm");
        settings.setSampleRate(16000);
        settings.setBitRate(64000);
        settings.setChannelCount(2);
        settings.setQuality(QMultimedia::VeryHighQuality);
        settings.setEncodingMode(QMultimedia::ConstantQualityEncoding);

        //QString container = boxValue(ui->containerBox).toString();
        QString container = "audio/x-wav";
        m_audioRecorder->setEncodingSettings(settings, QVideoEncoderSettings(), container);
        m_audioRecorder->record();
    }
    else {
        m_audioRecorder->stop();
        ui->nextLabelButton->setEnabled(true);
        ui->nextLabelButton->setText("Next label\n(" + QString::fromStdString(std::to_string(labelNum + 1)) + "/" + QString::fromStdString(std::to_string(commandList.size())) + ")");
        ui->nextLabelButton->setStyleSheet("QPushButton{ color: green;}");
        ui->recordButton->setStyleSheet("QPushButton{ color: white;}");
        AudioRecorder::checkExist();
        ui->recordButton->setText("Restart");
        AudioRecorder::updatePlaybackStatus();
    }
    
}

void AudioRecorder::togglePause()
{
    if (m_audioRecorder->state() != QMediaRecorder::PausedState)
        m_audioRecorder->pause();
    else
        m_audioRecorder->record();
}

void AudioRecorder::setOutputLocation()
{
    QString fileName = QFileDialog::getExistingDirectory();
    qDebug() << fileName;
    m_resultFolderLocation = fileName;
    AudioRecorder::checkExist();
}

void AudioRecorder::displayErrorMessage()
{
    ui->statusbar->showMessage(m_audioRecorder->errorString());
}

void AudioRecorder::clearAudioLevels()
{
    for (int i = 0; i < m_audioLevels.size(); ++i)
        m_audioLevels.at(i)->setLevel(0);
}

// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
    // Note: Only the most common sample formats are supported
    if (!format.isValid())
        return qreal(0);

    if (format.codec() != "audio/pcm")
        return qreal(0);

    switch (format.sampleType()) {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if (format.sampleSize() != 32) // other sample formats are not supported
            return qreal(0);
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if (format.sampleSize() == 32)
            return qreal(INT_MAX);
        if (format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
    case QAudioFormat::UnSignedInt:
        if (format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if (format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }

    return qreal(0);
}

// returns the audio level for each channel
QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
    QVector<qreal> values;

    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if (buffer.format().codec() != "audio/pcm")
        return values;

    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch (buffer.format().sampleType()) {
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        break;
    case QAudioFormat::Float:
        if (buffer.format().sampleSize() == 32) {
            values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
        }
        break;
    case QAudioFormat::SignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] /= peak_value;
        break;
    }

    return values;
}

template <class T>
QVector<qreal> getBufferLevels(const T* buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }

    return max_values;
}

void AudioRecorder::processBuffer(const QAudioBuffer& buffer)
{
    if (m_audioLevels.count() != buffer.format().channelCount()) {
        qDeleteAll(m_audioLevels);
        m_audioLevels.clear();
        for (int i = 0; i < buffer.format().channelCount(); ++i) {
            AudioLevel* level = new AudioLevel(ui->centralwidget);
            m_audioLevels.append(level);
            ui->levelsLayout->addWidget(level);
        }
    }

    QVector<qreal> levels = getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i)
        m_audioLevels.at(i)->setLevel(levels.at(i));
}

void AudioRecorder::onButtonSelected()
{
    //QButtonGroup buttonGroup;
    QList<QRadioButton*> allButtons = ui->groupBox_2->findChildren<QRadioButton *>();
    for (int i = 0; i < allButtons.size(); ++i)
    {
        if (allButtons[i]->isChecked()) {
            QString outputFilename = m_resultFolderLocation + "/" + allButtons[i]->text().replace(" ", "_");
            m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(outputFilename));
        }
    }
    AudioRecorder::checkExist();
}

void AudioRecorder::checkExist()
{
    QList<QRadioButton*> allButtons = ui->groupBox_2->findChildren<QRadioButton*>();
    for (int i = 0; i < allButtons.size(); ++i)
    {
        QString outputFilename = m_resultFolderLocation + "/" + allButtons[i]->text().replace(" ", "_");
        if (std::filesystem::exists(outputFilename.toStdString() + ".wav")) {
            allButtons[i]->setStyleSheet("QRadioButton{ color: green;}");
        }
        else {
            allButtons[i]->setStyleSheet("QRadioButton{ color: white;}");
        }
    }
}
void AudioRecorder::updatePlaybackStatus() {
    QString outputFilename = m_resultFolderLocation + "/" + ui->commandLabel->text().replace(" ", "_");
    if (std::filesystem::exists(outputFilename.toStdString() + ".wav") == true) {
        ui->playbackButton->setEnabled(true);
        //ui->playbackButton->setStyleSheet("QPushButton{color: white}");
        //ui->playbackButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
    else {
        ui->playbackButton->setEnabled(false);
        //ui->playbackButton->setStyleSheet("QPushButton{color: rgb(37, 37, 37); border: 1px solid rgb(37, 37, 37);}");
    }
}
void AudioRecorder::playRecordedAudio() {
    QString outputFilename = m_resultFolderLocation + "/" + ui->commandLabel->text().replace(" ", "_") + ".wav";
    s = new QSoundEffect(this);
    connect(s, &QSoundEffect::playingChanged, this, &AudioRecorder::soundPlayingChanges);
    const auto uuid = QUuid::createUuid();
    tempFilename = m_resultFolderLocation + "/" + uuid.toString().replace("{", "").replace("}", "").replace("-", "") + ".wav";
    qDebug() << outputFilename;
    qDebug() << tempFilename;
    std::ifstream  src(outputFilename.toStdString(), std::ios::binary);
    std::ofstream  dst(tempFilename.toStdString(), std::ios::binary);
    dst << src.rdbuf();
    s->setSource(QUrl::fromLocalFile(tempFilename));
    s->setLoopCount(1);
    s->play();
    ui->playbackButton->setEnabled(false);
}
void AudioRecorder::soundPlayingChanges() {
    ui->playbackButton->setEnabled(true);
    QFile::remove(tempFilename);
}
void AudioRecorder::preLabel() {
    labelNum = labelNum - 1;
    if (labelNum == 0){
        ui->pushButton->setStyleSheet("QPushButton{color: rgb(37, 37, 37); border: 1px solid rgb(37, 37, 37);}");
        ui->pushButton->setEnabled(false);
    }
    ui->nextLabelButton->setText("Next label\n(" + QString::fromStdString(std::to_string(labelNum + 1)) + "/" + QString::fromStdString(std::to_string(commandList.size())) + ")");
    ui->nextLabelButton->setStyleSheet("QPushButton{ color: white;}");
    ui->recordButton->setStyleSheet("QPushButton{ color: green;}");
    ui->recordButton->setEnabled(true);
    ui->commandLabel->setText(QString::fromStdString(commandList[labelNum]));
    QString outputFilename = m_resultFolderLocation + "/" + ui->commandLabel->text().replace(" ", "_");
    qDebug() << outputFilename;
    m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(outputFilename));
    ui->nextLabelButton->setEnabled(true);
    AudioRecorder::updatePlaybackStatus();
}
void AudioRecorder::nextLabel()
{
    if (ui->nextLabelButton->text() == "Finished!") {
        exit(0);
    }
    if (m_outputLocationSet == false) {
        QString fileName = QDir::currentPath() + "/" + ui->textEdit->toPlainText();
        std::filesystem::create_directory(fileName.toStdString());
        m_resultFolderLocation = fileName;
        AudioRecorder::checkExist();
        m_outputLocationSet = true;
        ui->commandLabel->setText("The audio file will be saved here: \n" + fileName);
        ui->commandLabel->setStyleSheet("QLabel{ font: 10pt;}");
        ui->nextLabelButton->setText("Confirm \nlocation...");
    }
    else {
        if (labelNum == commandList.size()-1) {
            ui->nextLabelButton->setText("Finished!");
            return;
        }
        else if (labelNum > -1){
            QString outputFilename = m_resultFolderLocation + "/" + ui->commandLabel->text().replace(" ", "_");
            if (std::filesystem::exists(outputFilename.toStdString() + ".wav") == false) {
                ui->nextLabelButton->setText("Please record the current command first!");
                return;
            }
        }
        labelNum = labelNum + 1;
        if (labelNum < commandList.size()) {
            if (labelNum > 0) {
                ui->pushButton->setStyleSheet("QPushButton{color: white; border: 1px solid white;}");
                ui->pushButton->setEnabled(true);
            }
            ui->commandLabel->setStyleSheet("QLabel{ font: 15pt;}");
            m_recordReady = true;
            ui->commandLabel->setText(QString::fromStdString(commandList[labelNum]));
            ui->nextLabelButton->setText("Next label\n(" + QString::fromStdString(std::to_string(labelNum+1)) + "/" + QString::fromStdString(std::to_string(commandList.size())) + ")");
            ui->nextLabelButton->setStyleSheet("QPushButton{ color: red;}");
            ui->recordButton->setStyleSheet("QPushButton{ color: green;}");
            ui->recordButton->setText("Record");
            ui->recordButton->setEnabled(true);

            ui->nextLabelButton->setEnabled(false);
            QString outputFilename = m_resultFolderLocation + "/" + ui->commandLabel->text().replace(" ", "_");
            if (std::filesystem::exists(outputFilename.toStdString() + ".wav") == true) {
                ui->nextLabelButton->setEnabled(true);
                ui->nextLabelButton->setStyleSheet("QPushButton{ color: white;}");
            }
            qDebug() << outputFilename;
            m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(outputFilename));
        }
    }
    AudioRecorder::updatePlaybackStatus();
}