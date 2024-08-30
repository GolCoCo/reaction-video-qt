#include "common.h"
#include <QUuid>
#include <QProcess>

QString createUuid()
{
	return QUuid::createUuid().toString() ;
}

QString createSimpleUuid()
{
	QString ret = createUuid() ;
	ret.chop(1) ;
	ret = ret.right(ret.length()-1) ;
	return ret ;
}
bool isVideoFile(QString filePath)
{
	QFileInfo finfo(filePath);
	QString filename = finfo.baseName();
	QString suf = finfo.suffix().toLower();
	if (suf == "mp4" || suf == "wmv" || suf == "avi") return 1;
	return 0;
}

int getMSec(QTime t) 
{
	int ret = t.hour()*3600 ;
	ret += t.minute()*60 ;
	ret += t.second() ;
	ret = ret*1000+t.msec() ;
	return ret ;
}

QTime getTime(int msec) 
{
	int s = msec/1000 ;
	msec %= 1000 ;
	int h = s/3600 ;
	s %= 3600 ;
	int m = s/60 ;
	s%=60 ;
	return QTime(h,m,s,msec) ;
}

QImage Mat2QImage(cv::Mat const& src)
{
	cv::Mat temp; // make the same cv::Mat
	cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
	QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
	dest.bits(); // enforce deep copy, see documentation 
	// of QImage::QImage ( const uchar * data, int width, int height, Format format )
	return dest;
}

cv::Mat QImage2Mat(QImage const& qimage)
{
	cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
	cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
	int from_to[] = { 0,0,  1,1,  2,2 };
	cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
	return mat2;
}


videoInfo getVideoDuration(QString filePath)
{
	videoInfo ret ;
	ret.fileName = filePath ;
	ret.duration = -1 ;
	if( !isValidSuffix(filePath) ) return ret ;
	VideoCapture cap(filePath.toStdString().c_str()) ;
	ret.totFrame = cap.get(CV_CAP_PROP_FRAME_COUNT) ;
	ret.fps = cap.get(CV_CAP_PROP_FPS) ;
	if( ret.fps ) ret.duration = ret.totFrame*1000/ret.fps ;
	ret.startTime = 0 ;
	ret.endTime = ret.duration ;
	cap.release() ;
//	ret.duration = 10
//	QMessageBox::information(NULL,"",QString("%1").arg(ret)) ;
	return ret ;
}

bool isValidSuffix(QString fileName)
{
	QString suf = QFileInfo(fileName).suffix().toLower();
	if (suf == "mp4" || suf == "wmv" || suf == "avi" || suf == "jpg" || suf == "png") return 1;
	return 0;
}

QString mmss( int t )
{
	return getTime(t).toString("mm:ss") ;
}