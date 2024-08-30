#ifndef COMMON_H
#define COMMON_H

#define SCENEWIDTH 1280
#define SCENEHEIGHT 720

#include <QMessageBox>
#include <QString>
#include <QObject>
#include <QTime>
#include <QPixmap>
#include <QFileInfo>
#include <QImage>
#include "include/opencv2/highgui/highgui.hpp"
#include "include/opencv2/imgproc/imgproc.hpp"
#include "include/opencv2/core/core.hpp"

#define DEFAULTFRAMERATE 29.7
#define TRIMBARHEIGHT 50
#define SEEKW 8
using namespace cv ;

static RNG rng(12345);

struct videoInfo{
	QString fileName ;
	int duration ;
	int fps ;
	int totFrame; 
	int startTime ;
	int endTime ;
};

QString  createUuid() ;
QString createSimpleUuid() ;
int getMSec(QTime t) ;
QTime getTime(int msec) ;

QImage Mat2QImage(Mat const& src) ;
Mat QImage2Mat(QImage const& src) ;
videoInfo getVideoDuration(QString filePath) ;
bool isValidSuffix(QString fileName) ;
bool isVideoFile(QString filePath);

QString mmss( int t ) ;
#endif // COMMON_H
