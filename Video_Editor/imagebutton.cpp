#include "imagebutton.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtWidgets\qmessagebox.h>
ImageButton::ImageButton(QWidget *parent)
	: QPushButton(parent)
{
	state = 0;
	setMouseTracking(true);
}

ImageButton::ImageButton(QListWidgetItem* item, QWidget* parent)
{
	state = 0;
	setMouseTracking(true);
	m_item = item;
	connect(this, SIGNAL(clicked(bool)), this, SLOT(on_BtnClicked()));
}

ImageButton::~ImageButton()
{

}
void ImageButton::on_BtnClicked() {
	emit setIsFade(m_item);
}
void ImageButton::setImages(QString normal, QString over, QString press)
{
	normal_img.load(normal);
	press_img.load(press);
	over_img.load(over);
}
void ImageButton::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	if (state == 0)
	{
		QImage scaled_img = normal_img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap::fromImage(scaled_img));
	}
	else if (state == 1)
	{
		QImage scaled_img = over_img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap::fromImage(scaled_img));
		state = 0;
	}
	else
	{
		QImage scaled_img = press_img.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap::fromImage(scaled_img));
		state = 0;
	}
}
void ImageButton::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton)
	{
		state = 2;
		update();
	}
	QPushButton::mousePressEvent(e);
}
void ImageButton::mouseReleaseEvent(QMouseEvent* e)
{
	//state = 1;
	state = 0;
	update();
	QPushButton::mouseReleaseEvent(e);
}
void ImageButton::mouseMoveEvent(QMouseEvent *e)
{
	state = 1;
	update();
	QPushButton::mouseMoveEvent(e);
}