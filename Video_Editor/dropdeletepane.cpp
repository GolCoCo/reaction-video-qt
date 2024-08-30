#include "dropdeletepane.h"
#include <QPainter>
#include "videolistwidget.h"
#include <QDropEvent>
#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

DropDeletePane::DropDeletePane(QWidget *parent)
	: QLabel(parent)
{
	setAcceptDrops(true);
}

DropDeletePane::~DropDeletePane()
{

}
void DropDeletePane::paintEvent(QPaintEvent*)
{
	QPixmap pixmap(":/Video_Editor/Resources/trash.png");
	QPixmap scaled_pixmap = pixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QPainter painter(this);
	painter.drawPixmap(0, 0, width(), height(), scaled_pixmap);
}
void DropDeletePane::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat(VideoListWidget::mimeType()))
	{
		event->accept();
	}
	else
		event->ignore();
}
void DropDeletePane::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat(VideoListWidget::mimeType())) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else {
		event->ignore();
	}
}

void DropDeletePane::dropEvent(QDropEvent *e)
{
	if (e->mimeData()->hasFormat(VideoListWidget::mimeType())) {
	
		QByteArray pieceData = e->mimeData()->data(VideoListWidget::mimeType());
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
		QPixmap pixmap;
		int location;
		QString str;
		QString path;
		dataStream >> pixmap >> str>>path >> location;

		emit __selectedDeleteItem(location);
	}
	else {
		e->ignore();
	}
}
