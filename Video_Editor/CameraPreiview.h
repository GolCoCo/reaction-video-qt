
#ifndef CAMERAPREVIEW_H
#define CAMERAPREVIEW_H

#include <QLabel>
#include <QtWidgets>
#include <QFrame>
#include <QtWidgets/QMainWindow>
#include <QMultiMedia>
#include "Global.h"
#include <common.h>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class CameraPreiview : public QFrame
{
	Q_OBJECT
public:
    explicit CameraPreiview(QSize videoS, QWidget* parent = 0);
    void setVisibleRecordLabel(bool isvisible);
    ~CameraPreiview();
    void setVideoPixmap(QPixmap pixmap);
    void setFixedAlignment();
    void setCameraPixmap(QPixmap pixmap);
public slots:
    void mouseDoubleClickEvent(QMouseEvent* event);
signals:
    void doulbleclicked();
public:
    QLabel* videoPreview;
    QLabel* record;
	int m_width;
	int m_height;
	bool isDoubleClick;
};

#endif // CAMERAPREVIEW_H