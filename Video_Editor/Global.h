#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMessageBox>
#include <QString>
#include <QObject>
#include <QTime>
#include <QPixmap>
#include <QFileInfo>

#include "include/opencv2/core/core.hpp"
#include "include/opencv2/highgui/highgui.hpp"
#include "include/opencv2/imgproc/imgproc.hpp"
using namespace cv;
class VideoItem;
struct VideoInfo{
	QString m_filePath;
	QString m_fileName;
	QPixmap m_titleImg;
	double m_startTime;
	double m_endTime;
	double m_fps;
	double m_frameCount;
	double m_duration;
};

//QImage Mat2QImage(Mat const& src);
//Mat QImage2Mat(QImage const& src);
//bool isValidSuffix(QString fileName);
VideoInfo getInfomationOfVideo(QString filepath);
#endif // GLOBAL_H