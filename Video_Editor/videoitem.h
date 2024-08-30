#ifndef VIDEOITEM_H
#define VIDEOITEM_H


#include <QPixmap>

class VideoItem 
{
	
public:
	VideoItem();
	~VideoItem();

	int m_index;
	QString m_filePath;
	QString m_fileName;
	QPixmap m_titleImg;
	bool m_IsFadeEffect = true;
	double m_startTime;
	double m_endTime;
	double m_fps;
	double m_frameCount;
	double m_duration;

	double m_startOffset;
	double m_endOffset;
	bool m_IsVideo;
};

#endif // VIDEOITEM_H
