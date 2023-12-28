#pragma once


#ifdef _WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include "vlc/vlc.h"

#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include <qpixmap.h>
#include <qfiledialog.h>
#include <qmessagebox.h>



class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    void setTime_Slider(int value);
    void setVolum_Slider(int value);
    qint64 getDurations();
    void setTimeText(QString str);
    libvlc_media_player_t* media_player();

private slots:
    void on_btnOpen_clicked();
    void on_btnPlay_clicked();
    void on_btnPause_clicked();
    void timeSlider(int value);
    void volumSlider(int value);
    
private:
    libvlc_instance_t* m_pInstance = nullptr;
    libvlc_media_player_t* m_PMediaPlayer = nullptr;
    libvlc_media_t* m_pMedia = nullptr;
    libvlc_event_manager_t* m_pEvent_manager = nullptr;

    // 定义视频时长
    qint64 m_totalSecs = -1;

private:
    Ui::MainWindowClass ui;
};
