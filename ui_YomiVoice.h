/********************************************************************************
** Form generated from reading UI file 'YomiVoiceqxKyEV.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef YOMIVOICEQXKYEV_H
#define YOMIVOICEQXKYEV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AudioRecorder
{
public:
    QWidget* centralwidget;
    QGridLayout* gridLayout_3;
    QGroupBox* groupBox_2;
    QGridLayout* gridLayout_4;
    QLabel* commandLabel;
    QToolButton* playbackButton;
    QFrame* line;
    QVBoxLayout* levelsLayout;
    QGroupBox* horizontalGroupBox;
    QHBoxLayout* horizontalLayout;
    QLabel* levelLabel;
    QGroupBox* gridGroupBox;
    QGridLayout* gridLayout;
    QPushButton* recordButton;
    QPushButton* nextLabelButton;
    QPushButton* pushButton;
    QGridLayout* gridLayout_2;
    QLabel* label_2;
    QLabel* label;
    QComboBox* audioDeviceBox;
    QTextEdit* textEdit;
    QStatusBar* statusbar;

    void setupUi(QMainWindow* AudioRecorder)
    {
        if (AudioRecorder->objectName().isEmpty())
            AudioRecorder->setObjectName(QString::fromUtf8("AudioRecorder"));
        AudioRecorder->resize(629, 468);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AudioRecorder->sizePolicy().hasHeightForWidth());
        AudioRecorder->setSizePolicy(sizePolicy);
        AudioRecorder->setMinimumSize(QSize(252, 468));
        AudioRecorder->setStyleSheet(QString::fromUtf8("QGroupBox  {color: white; background-color: rgb(37, 37, 37)}\n"
            "QComboBox {color: white; background-color: rgb(37, 37, 37); selection-background-color: rgb(37, 37, 37); border: 1px solid white}\n"
            "QPushButton {color: white; background-color: rgb(37, 37, 37); selection-background-color: rgb(37, 37, 37); border: 1px solid white}\n"
            "QTextEdit {color: white; background-color: rgb(37, 37, 37); selection-background-color: rgb(37, 37, 37); border: 1px solid white}\n"
            "QWidget {color: white; background-color: rgb(37, 37, 37)}\n"
            ""));
        centralwidget = new QWidget(AudioRecorder);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(5);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setMinimumSize(QSize(0, 0));
        groupBox_2->setFlat(false);
        gridLayout_4 = new QGridLayout(groupBox_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(11, -1, -1, -1);
        commandLabel = new QLabel(groupBox_2);
        commandLabel->setObjectName(QString::fromUtf8("commandLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(10);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(commandLabel->sizePolicy().hasHeightForWidth());
        commandLabel->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(10);
        commandLabel->setFont(font);
        commandLabel->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(commandLabel, 1, 0, 1, 1);

        playbackButton = new QToolButton(groupBox_2);
        playbackButton->setObjectName(QString::fromUtf8("playbackButton"));
        playbackButton->setEnabled(false);
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(playbackButton->sizePolicy().hasHeightForWidth());
        playbackButton->setSizePolicy(sizePolicy3);
        playbackButton->setStyleSheet(QString::fromUtf8("QToolButton {color: white; background-color: white; selection-background-color: white; border: 1px solid white}"));

        gridLayout_4->addWidget(playbackButton, 2, 0, 1, 1, Qt::AlignRight);


        gridLayout_3->addWidget(groupBox_2, 6, 0, 1, 3);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(1);
        line->setFrameShape(QFrame::HLine);

        gridLayout_3->addWidget(line, 5, 0, 1, 3);

        levelsLayout = new QVBoxLayout();
        levelsLayout->setSpacing(7);
        levelsLayout->setObjectName(QString::fromUtf8("levelsLayout"));

        gridLayout_3->addLayout(levelsLayout, 4, 0, 1, 3);

        horizontalGroupBox = new QGroupBox(centralwidget);
        horizontalGroupBox->setObjectName(QString::fromUtf8("horizontalGroupBox"));
        horizontalGroupBox->setFlat(true);
        horizontalLayout = new QHBoxLayout(horizontalGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        levelLabel = new QLabel(horizontalGroupBox);
        levelLabel->setObjectName(QString::fromUtf8("levelLabel"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(levelLabel->sizePolicy().hasHeightForWidth());
        levelLabel->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(levelLabel);


        gridLayout_3->addWidget(horizontalGroupBox, 3, 0, 1, 3);

        gridGroupBox = new QGroupBox(centralwidget);
        gridGroupBox->setObjectName(QString::fromUtf8("gridGroupBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(5);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(gridGroupBox->sizePolicy().hasHeightForWidth());
        gridGroupBox->setSizePolicy(sizePolicy5);
        gridLayout = new QGridLayout(gridGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        recordButton = new QPushButton(gridGroupBox);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy6.setHorizontalStretch(2);
        sizePolicy6.setVerticalStretch(2);
        sizePolicy6.setHeightForWidth(recordButton->sizePolicy().hasHeightForWidth());
        recordButton->setSizePolicy(sizePolicy6);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(14);
        recordButton->setFont(font1);

        gridLayout->addWidget(recordButton, 0, 0, 1, 1);

        nextLabelButton = new QPushButton(gridGroupBox);
        nextLabelButton->setObjectName(QString::fromUtf8("nextLabelButton"));
        nextLabelButton->setEnabled(true);
        QSizePolicy sizePolicy7(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy7.setHorizontalStretch(1);
        sizePolicy7.setVerticalStretch(1);
        sizePolicy7.setHeightForWidth(nextLabelButton->sizePolicy().hasHeightForWidth());
        nextLabelButton->setSizePolicy(sizePolicy7);
        nextLabelButton->setMinimumSize(QSize(15, 0));
        nextLabelButton->setFont(font1);
        nextLabelButton->setStyleSheet(QString::fromUtf8("QPushButton {color: green;}"));
        nextLabelButton->setCheckable(false);
        nextLabelButton->setChecked(false);
        nextLabelButton->setAutoDefault(false);

        gridLayout->addWidget(nextLabelButton, 0, 2, 1, 1);

        pushButton = new QPushButton(gridGroupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);
        QSizePolicy sizePolicy8(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy8.setHorizontalStretch(1);
        sizePolicy8.setVerticalStretch(2);
        sizePolicy8.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy8);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {color: rgb(37, 37, 37); background-color: rgb(37, 37, 37); selection-background-color: rgb(37, 37, 37); border: 1px solid rgb(37, 37, 37)}"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);


        gridLayout_3->addWidget(gridGroupBox, 9, 0, 1, 3);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        audioDeviceBox = new QComboBox(centralwidget);
        audioDeviceBox->setObjectName(QString::fromUtf8("audioDeviceBox"));

        gridLayout_2->addWidget(audioDeviceBox, 0, 1, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy9);
        textEdit->setMinimumSize(QSize(0, 20));
        textEdit->setMaximumSize(QSize(16777215, 20));
        textEdit->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(255, 255, 255);\n"
            "selection-color: rgb(0, 85, 127);"));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout_2->addWidget(textEdit, 1, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 1, 0, 1, 3);

        AudioRecorder->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(AudioRecorder);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setEnabled(true);
        AudioRecorder->setStatusBar(statusbar);

        retranslateUi(AudioRecorder);
        QObject::connect(recordButton, SIGNAL(clicked()), AudioRecorder, SLOT(toggleRecord()));

        QMetaObject::connectSlotsByName(AudioRecorder);
    } // setupUi

    void retranslateUi(QMainWindow* AudioRecorder)
    {
        AudioRecorder->setWindowTitle(QCoreApplication::translate("AudioRecorder", "Yomi Voice Collector v0.1", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AudioRecorder", "Command", nullptr));
        commandLabel->setText(QCoreApplication::translate("AudioRecorder", "Please set the output location first...", nullptr));
        playbackButton->setText(QString());
        levelLabel->setText(QCoreApplication::translate("AudioRecorder", "Audio Level:", nullptr));
        recordButton->setText(QCoreApplication::translate("AudioRecorder", "Record", nullptr));
        nextLabelButton->setText(QCoreApplication::translate("AudioRecorder", "Continue...", nullptr));
        pushButton->setText(QCoreApplication::translate("AudioRecorder", "Previous", nullptr));
        label_2->setText(QCoreApplication::translate("AudioRecorder", "Output Name:", nullptr));
        label->setText(QCoreApplication::translate("AudioRecorder", "Input Device:", nullptr));
        textEdit->setHtml(QCoreApplication::translate("AudioRecorder", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
            "p, li { white-space: pre-wrap; }\n"
            "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">labels</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AudioRecorder : public Ui_AudioRecorder {};
} // namespace Ui

QT_END_NAMESPACE

#endif // YOMIVOICEQXKYEV_H
