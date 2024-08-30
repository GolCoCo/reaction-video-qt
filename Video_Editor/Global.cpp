#include "Global.h"
#include "videoitem.h"
#include "common.h"

VideoInfo getInfomationOfVideo(QString filepath)
{
	VideoInfo video;

	video.m_filePath = filepath;
	QFileInfo finfo(filepath);
	video.m_fileName = finfo.baseName();
	video.m_duration = -1;

	VideoCapture cap(filepath.toStdString().c_str());
	
	if (cap.isOpened())
	{
		video.m_frameCount = cap.get(CV_CAP_PROP_FRAME_COUNT);
		video.m_fps = cap.get(CV_CAP_PROP_FPS);
		if (video.m_fps) video.m_duration = video.m_frameCount * 1000 / video.m_fps;
		video.m_startTime = 0;
		video.m_endTime = video.m_duration;

		cap.set(CV_CAP_PROP_POS_MSEC, video.m_startTime);
		Mat mat;
		cap.read(mat);
		if (!mat.empty())
		{
			QImage img= Mat2QImage(mat);
			video.m_titleImg = QPixmap::fromImage(img);
		}
			
		cap.release();
	}
	return video;
}
