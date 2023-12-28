#include "MainWindow.h"
#include <qpixmap.h>
#include <qfiledialog.h>
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


MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

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

	// 将文本清空
	ui.btnOpen->setText("");
	ui.btnPlay->setText("");
	ui.btnPause->setText("");
	ui.btnAduio->setText("");
	ui.showList->setFixedHeight(32);
	ui.timerLable->setFixedHeight(32);

	// 设置固定大小
	ui.btnOpen->setFixedSize(32, 32);
	ui.btnPlay->setFixedSize(32, 32);
	ui.btnPause->setFixedSize(32, 32);
	ui.btnAduio->setFixedSize(32, 32);

	// 设置图标
	QIcon openIcon(":/rec/folder.png");
	QIcon playIcon(":/rec/play.png");
	QIcon pauseIcon(":/rec/pause.png");
	QIcon aduioIcon(":/rec/audio.png");

	ui.btnOpen->setIcon(openIcon);
	ui.btnOpen->setIconSize(QSize(24, 24));

	ui.btnPlay->setIcon(playIcon);
	ui.btnPlay->setIconSize(QSize(24, 24));

	ui.btnPause->setIcon(pauseIcon);
	ui.btnPause->setIconSize(QSize(24, 24));

	ui.btnAduio->setIcon(aduioIcon);
	ui.btnAduio->setIconSize(QSize(24, 24));

	ui.btnAduio->setStyleSheet("border:none");
	ui.btnPlay->setStyleSheet("border:none");
	ui.btnPause->setStyleSheet("border:none");
	ui.btnOpen->setStyleSheet("border:none");
}


void MainWindow::setTime_Slider(int value)
{
	ui.timeSlider->setValue(value);
}

void MainWindow::setVolum_Slider(int value)
{
	ui.volume_Slider->setValue(value);
}

qint64 MainWindow::getDurations()
{
	return m_totalSecs;
}

// 设置时长到Qlabel控件中
void MainWindow::setTimeText(QString str)
{
	ui.timerLable->setText(str);
}

libvlc_media_player_t* MainWindow::media_player()
{
	return m_PMediaPlayer;
}


// 设置视频进度条的位置
void MainWindow::timeSlider(int value)
{
	libvlc_media_player_set_position(m_PMediaPlayer, value / 100.0);
}

// 设置声音进度条的位置
void MainWindow::volumSlider(int value)
{
	libvlc_audio_set_volume(m_PMediaPlayer, value);
}

// 打开文件
void MainWindow::on_btnOpen_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "请选择要打开的文件", "E:/study", \
		"视频文件(*.mp4 *.flv *.avi);;所有文件(*.*)");

	if (fileName.isEmpty())
		return;

	// 将打开的文件置入到窗口中
	// 设置路径
	/*使用qt函数库中的函数进行反斜杠的转译,否则m_pmedia的内容会是空*/
	fileName = QDir::toNativeSeparators(fileName);
	m_pMedia = libvlc_media_new_path(m_pInstance, fileName.toStdString().c_str());
	if (m_pMedia)
	{
		// 解析media
		libvlc_media_parse(m_pMedia);

		// 设置media
		libvlc_media_player_set_media(m_PMediaPlayer, m_pMedia);

		// 设置播放的窗口句柄
		libvlc_media_player_set_hwnd(m_PMediaPlayer, (void*)(ui.video_widget->winId()));

		// 视频总时长，单位MS
		m_totalSecs = libvlc_media_get_duration(m_pMedia) / 1000;

		// 释放media
		libvlc_media_release(m_pMedia);
		m_pMedia = nullptr;

		// 播放视频
		libvlc_media_player_play(m_PMediaPlayer);
	}
	else
	{
		QMessageBox::information(this, "错误", "libvlc_media_player_play failed");
		exit(EXIT_FAILURE);
	}
	ui.timerLable->setText("");

	// 拖动进度条，实现视频移动到当前进度播放
	connect(ui.timeSlider, &QSlider::sliderMoved, this, &MainWindow::timeSlider);

	// 拖动声音条，改变播放视频的声音
	connect(ui.volume_Slider, &QSlider::sliderMoved, this, &MainWindow::volumSlider);
}



// 播放视频按钮
void MainWindow::on_btnPlay_clicked()
{
	// 播放视频
	if (libvlc_media_player_get_state(m_PMediaPlayer) == libvlc_state_t::libvlc_Paused)
	{
		libvlc_media_player_play(m_PMediaPlayer);
	}
}


// 停止播放视频按钮
void MainWindow::on_btnPause_clicked()
{
	if (libvlc_media_player_get_state(m_PMediaPlayer) == libvlc_state_t::libvlc_Playing)
	{
		libvlc_media_player_pause(m_PMediaPlayer);
	}
}


MainWindow::~MainWindow()
{
	// 释放mediaPlayer资源
	if (m_PMediaPlayer)
	{
		libvlc_media_player_release(m_PMediaPlayer);
		m_PMediaPlayer = nullptr;
	}


	// 释放资源
	if (m_pInstance)
	{
		libvlc_release(m_pInstance);
		m_pInstance = nullptr;
	}

}