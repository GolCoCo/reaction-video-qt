#include "videolistwidget.h"

VideoListWidget::VideoListWidget(QList<VideoItem*>* vilist, QWidget *parent)
	: QListWidget(parent)
{
	space = 10;
	itemSize = 80;
	this->end = 0;
	this->start = 0;
	m_vilist = vilist;

	setDragEnabled(true);
	setIconSize(QSize(itemSize, itemSize));
	setSpacing(space);
	setAcceptDrops(true);
	setDropIndicatorShown(true);
}

VideoListWidget::~VideoListWidget()
{

}

void VideoListWidget::addVideoItem(QPixmap pixmap, QString path, QString str, int location, bool isFade)
{
	QListWidgetItem *videoItem = new QListWidgetItem(this);
	videoItem->setFont(QFont("Javanese Text", 4, -1, false));
	videoItem->setForeground(QBrush(Qt::white));
	videoItem->setText("");
	videoItem->setToolTip(path);
	videoItem->setIcon(QIcon(pixmap));
	videoItem->setData(Qt::UserRole, QVariant(pixmap));
	videoItem->setData(Qt::UserRole + 1, location);
	videoItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	//videoItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);

	this->addItem(videoItem);

}
void VideoListWidget::ListItemClickLinster(QListWidgetItem* item)
{

	QString title = item->text().split(".").at(0);

	int cnt = m_vilist->size();
	for (int i = 0; i < cnt; i++) {

		if (m_vilist->at(i)->m_fileName == title) {

			if (m_vilist->at(i)->m_IsFadeEffect) {
				m_vilist->at(i)->m_IsFadeEffect = false;
			}
			else {
				m_vilist->at(i)->m_IsFadeEffect = true;
			}
		}
	}
	fclose(stdout);

	emit refresh();
}
void VideoListWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat(VideoListWidget::mimeType()))
	{
		event->accept();
		startPos = event->pos();
	}
	else
		event->ignore();
}
void VideoListWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasFormat(VideoListWidget::mimeType())) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else {
		event->ignore();
	}
}

void VideoListWidget::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat(VideoListWidget::mimeType())) {
		QPoint curPos = event->pos();
		int delta = (curPos.y() - startPos.y()) / (itemSize + space);
		end = start + delta;

		QByteArray pieceData = event->mimeData()->data(VideoListWidget::mimeType());
		QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
		QPixmap pixmap;
		int location;
		QString str;
		QString path;
		dataStream >> pixmap>>str>>path >> location;

		addVideoItem(pixmap, str,path, location,true);

		event->setDropAction(Qt::MoveAction);
		event->accept();
		emit __dragAndDrop(start, end);
	}
	else {
		event->ignore();
	}
	start = -1;
	end = -1;
}

void VideoListWidget::startDrag(Qt::DropActions)
{
	QListWidgetItem *item = currentItem();

	QByteArray itemData;
	QDataStream dataStream(&itemData, QIODevice::WriteOnly);
	QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
	int location = item->data(Qt::UserRole + 1).toInt();
	QString str = item->text();
	QString path = item->toolTip();
	dataStream << pixmap << str <<path << location;
	start = location;
	QMimeData *mimeData = new QMimeData;
	mimeData->setData(VideoListWidget::mimeType(), itemData);

	QDrag *drag = new QDrag(this);
	drag->setMimeData(mimeData);
	drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
	drag->setPixmap(pixmap);
	drag->exec(Qt::MoveAction);
	/*if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
		delete takeItem(row(item));*/
}