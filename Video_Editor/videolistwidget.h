#ifndef VIDEOLISTWIDGET_H
#define VIDEOLISTWIDGET_H

#include <QListWidget>

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QMessageBox>
#include "imagebutton.h"
#include "videoitem.h"
#include <QtWidgets\qboxlayout.h>
#include <QLabel>

class VideoListWidget : public QListWidget
{
	Q_OBJECT

public:
	VideoListWidget(QList<VideoItem*>* vilist, QWidget *parent=0);
	~VideoListWidget();
	void addVideoItem(QPixmap pixmap, QString path, QString str, int location, bool isFade);

	int space;
	int itemSize;
	static QString mimeType(){ return "videoitem"; }

public slots:
	void ListItemClickLinster(QListWidgetItem* item);
	
signals:
	void __dragAndDrop(int st, int ed);
	void refresh();
protected:
	void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
	void startDrag(Qt::DropActions supportedActions) Q_DECL_OVERRIDE;


private:
	int start;
	QPoint startPos;
	int end;
	QList<VideoItem*>* m_vilist;
};

#endif // VIDEOLISTWIDGET_H
