#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QMainWindow>
#include <QMediaRecorder>
#include <QUrl>
#include <QtMultimedia/qsoundeffect.h>

QT_BEGIN_NAMESPACE
namespace Ui { class AudioRecorder; }
class QAudioRecorder;
class QAudioProbe;
class QAudioBuffer;
QT_END_NAMESPACE

class AudioLevel;

class AudioRecorder : public QMainWindow
{
    //Q_OBJECT

public:
    AudioRecorder();

public slots:
    void processBuffer(const QAudioBuffer&);

private slots:
    void setOutputLocation();
    void togglePause();
    void toggleRecord();

    void updateStatus(QMediaRecorder::Status);
    void onStateChanged(QMediaRecorder::State);
    void updateProgress(qint64 pos);
    void displayErrorMessage();
    void soundPlayingChanges();

private:
    void clearAudioLevels();
    void onButtonSelected();
    void checkExist();
    void preLabel();
    void nextLabel();
    void updatePlaybackStatus();
    void playRecordedAudio();
    Ui::AudioRecorder* ui = nullptr;
    QSoundEffect* s = nullptr;
    QString tempFilename;
    QAudioRecorder* m_audioRecorder = nullptr;
    QAudioProbe* m_probe = nullptr;
    int labelNum = -1;
    QList<AudioLevel*> m_audioLevels;
    bool m_outputLocationSet = false;
    bool m_recordReady = false;
    QString m_resultFolderLocation = "";

};

#endif // AUDIORECORDER_H
