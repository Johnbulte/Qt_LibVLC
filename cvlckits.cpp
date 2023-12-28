#include "cvlckits.h"
#include <qmessagebox.h>


// 监听事件，执行回调函数
void vlc_callback(const struct libvlc_event_t* p_event, void* p_data)
{
	MainWindow* pMain = static_cast<MainWindow*> (p_data);

	// 设置进度条根据视频播放进度自动进行调整
	switch (p_event->type)
	{
	case libvlc_MediaPlayerPositionChanged:
	{
		float pos = libvlc_media_player_get_position(pMain->media_player());
		pMain->setTime_Slider(pos * 100);

		// 获取播放视频的总时长
		qint64 curSecs = libvlc_media_player_get_time(pMain->media_player()) / 1000;

		// 转换为小时
		int curH = curSecs / 3600;

		// 转换为分钟
		int curMinute = (curSecs - curH * 3600) / 60;

		// 转换为秒
		int curSec = curSecs - (curH * 3600) - (curMinute * 60);

		// 定义一个char数组
		char buf1[256] = { 0 };
		sprintf(buf1, "%02d:%02d:%02d", curH, curMinute, curSec);

		// 将char数组转换为字符串
		QString str1(buf1);

		// 获取视频的总小时、分钟、秒
		qint64 totalSecs = pMain->getDurations();
		int hour = totalSecs / 3600;
		int minute = (totalSecs - curH * 3600) / 60;
		int sec = totalSecs - curH * 3600 - curMinute * 60;

		char buf2[256] = { 0 };
		sprintf(buf2, "%02d:%02d:%02d", hour, minute, sec);

		QString str2(buf2);

		// 拼接字符串
		QString text = str1 + "/" + str2;
		pMain->setTimeText(text);
	}
	break;

	case libvlc_MediaPlayerAudioVolume:
	{
		// 设置开始播放的默认声音
		int volum = libvlc_audio_get_volume(pMain->media_player());
		pMain->setVolum_Slider(volum);
	}
	break;
	}

}


libvlc_media_player_t* cvlckits::media_player()
{
	return m_PMediaPlayer;
}

int cvlckits::initVLC()
{
	// vlc初始化
	m_pInstance = libvlc_new(0, nullptr);

	// 判断是否为空，为空提示错误
	if (m_pInstance)
	{
		m_PMediaPlayer = libvlc_media_player_new(m_pInstance);
		if (m_PMediaPlayer)
		{
			m_pEvent_manager = libvlc_media_player_event_manager(m_PMediaPlayer);
			libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerPositionChanged, vlc_callback, this);
			libvlc_event_attach(m_pEvent_manager, libvlc_MediaPlayerAudioVolume, vlc_callback, this);
		}
	}
	else
	{
		QMessageBox::information(this, "错误", "libvlc_new failed");
		exit(EXIT_FAILURE);
	}
}


libvlc_media_player_t* MainWindow::media_player()
{
	return m_PMediaPlayer;
}

}


cvlckits::cvlckits()
{
	
}

cvlckits::~cvlckits()
{
}
