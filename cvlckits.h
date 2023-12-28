#pragma once
/*
* libvlc功能封装
*/
#ifdef _WIN32
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#endif

#include "vlc/vlc.h"
#include <qobject.h>

class cvlckits : public QObject
{
	Q_OBJECT
public:
    libvlc_media_player_t* media_player();
    int initVLC();
public:
	cvlckits();
	~cvlckits();
private:
    libvlc_instance_t* m_pInstance = nullptr;
    libvlc_media_player_t* m_PMediaPlayer = nullptr;
    libvlc_media_t* m_pMedia = nullptr;
    libvlc_event_manager_t* m_pEvent_manager = nullptr;

    // 定义视频时长
    qint64 m_totalSecs = -1;
};

