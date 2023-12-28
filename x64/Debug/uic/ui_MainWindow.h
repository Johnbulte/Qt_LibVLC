/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *video_widget;
    QSlider *timeSlider;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnAduio;
    QSlider *volume_Slider;
    QPushButton *btnOpen;
    QPushButton *btnPlay;
    QPushButton *btnPause;
    QSpacerItem *horizontalSpacer;
    QPushButton *showList;
    QSpacerItem *horizontalSpacer_3;
    QLabel *timerLable;

    void setupUi(QWidget *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName("MainWindowClass");
        MainWindowClass->resize(579, 404);
        verticalLayout = new QVBoxLayout(MainWindowClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        video_widget = new QWidget(MainWindowClass);
        video_widget->setObjectName("video_widget");
        video_widget->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(video_widget);

        timeSlider = new QSlider(MainWindowClass);
        timeSlider->setObjectName("timeSlider");
        timeSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(timeSlider);

        frame = new QFrame(MainWindowClass);
        frame->setObjectName("frame");
        frame->setMaximumSize(QSize(16777215, 50));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        btnAduio = new QPushButton(frame);
        btnAduio->setObjectName("btnAduio");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/rec/audio.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAduio->setIcon(icon);
        btnAduio->setIconSize(QSize(24, 24));
        btnAduio->setCheckable(false);

        horizontalLayout->addWidget(btnAduio);

        volume_Slider = new QSlider(frame);
        volume_Slider->setObjectName("volume_Slider");
        volume_Slider->setMinimumSize(QSize(50, 0));
        volume_Slider->setMaximumSize(QSize(50, 16777215));
        volume_Slider->setMaximum(100);
        volume_Slider->setValue(50);
        volume_Slider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(volume_Slider);

        btnOpen = new QPushButton(frame);
        btnOpen->setObjectName("btnOpen");

        horizontalLayout->addWidget(btnOpen);

        btnPlay = new QPushButton(frame);
        btnPlay->setObjectName("btnPlay");

        horizontalLayout->addWidget(btnPlay);

        btnPause = new QPushButton(frame);
        btnPause->setObjectName("btnPause");

        horizontalLayout->addWidget(btnPause);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        showList = new QPushButton(frame);
        showList->setObjectName("showList");

        horizontalLayout->addWidget(showList);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        timerLable = new QLabel(frame);
        timerLable->setObjectName("timerLable");

        horizontalLayout->addWidget(timerLable);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(frame);


        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "MainWindow", nullptr));
        btnAduio->setText(QString());
        btnOpen->setText(QCoreApplication::translate("MainWindowClass", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        btnPlay->setText(QCoreApplication::translate("MainWindowClass", "\346\222\255\346\224\276", nullptr));
        btnPause->setText(QCoreApplication::translate("MainWindowClass", "\346\232\202\345\201\234", nullptr));
        showList->setText(QCoreApplication::translate("MainWindowClass", "\346\230\276\347\244\272\345\210\227\350\241\250", nullptr));
        timerLable->setText(QCoreApplication::translate("MainWindowClass", "00:00/00:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
