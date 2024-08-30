#include "trimbar.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

int m_seekHeight = 40;
int m_seekWidth = 20;
int counter = 0;
TrimBar::TrimBar(int typeOfBar, QWidget *parent)
	: QLabel(parent)
{
	m_st = 0;
	m_en = 1;
	this->typeOfBar = typeOfBar;
	this->isControl = true;
	m_movingIndex = -1;
	m_play = new QLabel(this);
	m_left = new QLabel(this);
	m_right = new QLabel(this);

	if (typeOfBar == 0) {

		m_play->setStyleSheet("QLabel{background:qlineargradient(spread:reflect, x1:0.051, y1:0.023, x2:0.507, y2:0.023, stop:0 rgba(23, 14, 50, 255), stop:0.198864 rgba(2, 79, 0, 255), stop:1 rgba(91, 153, 77, 255));}");
		m_left->setStyleSheet("QLabel{background:qlineargradient(spread:reflect, x1:0.051, y1:0.023, x2:0.507, y2:0.023, stop:0 rgba(23, 14, 50, 255), stop:0.198864 rgba(2, 79, 0, 255), stop:1 rgba(91, 153, 77, 255));}");
		m_right->setStyleSheet("QLabel{background:qlineargradient(spread:reflect, x1:0.051, y1:0.023, x2:0.507, y2:0.023, stop:0 rgba(23, 14, 50, 255), stop:0.198864 rgba(2, 79, 0, 255), stop:1 rgba(91, 153, 77, 255));}");
	}
	else {
		m_play->setStyleSheet("QLabel{background:qlineargradient(spread:reflect, x1:0.006, y1:0.017, x2:0.518, y2:0.0173182, stop:0 rgba(43, 38, 1, 255), stop:0.125 rgba(111, 102, 0, 255), stop:0.693182 rgba(252, 255, 64, 255));}");
		m_left->setStyleSheet("QLabel{background:qlineargradient(spread:reflect, x1:0.006, y1:0.017, x2:0.518, y2:0.0173182, stop:0 rgba(43, 38, 1, 255), stop:0.125 rgba(111, 102, 0, 255), stop:0.693182 rgba(252, 255, 64, 255));}");
		m_right->setStyleSheet("QLabel{background:qlineargradient(spread:reflect, x1:0.006, y1:0.017, x2:0.518, y2:0.0173182, stop:0 rgba(43, 38, 1, 255), stop:0.125 rgba(111, 102, 0, 255), stop:0.693182 rgba(252, 255, 64, 255));}");
	}
	
	
}

TrimBar::~TrimBar()
{

}
void TrimBar::setEnableControl(bool iscon)
{
	this->isControl = iscon;
}
void TrimBar::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	painter.fillRect(QRect(0, 0, width(), 40), QBrush(Qt::gray, Qt::SolidPattern));

}
void TrimBar::mousePressEvent(QMouseEvent* e)
{
	if ( this->typeOfBar == 0 && isControl) {
		QLabel::mousePressEvent(e);
		QPoint m_pos = e->pos();
		if (m_left->geometry().contains(m_pos) && m_left->isVisible()) { m_movingIndex = 0; }
		else if (m_right->geometry().contains(m_pos) && m_right->isVisible()) { m_movingIndex = 1; }
		else if ((m_play->geometry().contains(m_pos) && !m_left->geometry().contains(m_pos)) && m_play->isVisible()) { m_movingIndex = 2; }
		else {
			qreal m_val = (double)m_pos.x();
			m_val = realToVirtual(m_val);
			if (m_val > realToVirtual(m_en * trim_width)) return;
			double m_st = m_val / (double)(trim_width - m_seekWidth);
			emit __SeekJumpChanged(m_st);
		}
	}
	else {
		return;
	}
}
void TrimBar::mouseMoveEvent(QMouseEvent* e)
{
	
	qreal m_val = (double)e->pos().x();
	if (m_val < 0 || m_val > trim_width || m_movingIndex == -1) return;
	m_val = realToVirtual(m_val);
	
	if (m_movingIndex == 0)
	{
		//if (m_val >realToVirtual(m_en *trim_width))return;
		//m_st = m_val / (double)(trim_width - m_seekWidth);
		//emit __leftSeekChanged(m_st);
		//fitSeekItems(m_st, m_en);
		return;
	}
	if (m_movingIndex == 1)
	{
		//if (m_val < realToVirtual(m_st * trim_width))return;
		//m_en = m_val / (double)(trim_width - m_seekWidth);
		//emit __rightSeekChanged(m_en);
		//fitSeekItems(m_st, m_en);
		return;
	}
	if (m_movingIndex == 2)
	{
		if (m_val < realToVirtual(m_st * trim_width))return;
		double m_en = m_val / (double)(trim_width - m_seekWidth);
		emit __playSeekChanged(m_en);
	}
		
	QLabel::mouseMoveEvent(e);
}
void TrimBar::mouseReleaseEvent(QMouseEvent* e)
{
	QLabel::mouseReleaseEvent(e);
	m_movingIndex = -1;
}
void TrimBar::fitSeekItems(qreal lseek, qreal rseek)
{
	
	m_left->setGeometry((trim_width - m_seekWidth)*lseek, 0, m_seekWidth, m_seekHeight);
	m_right->setGeometry((trim_width - m_seekWidth)*rseek, 0, m_seekWidth, m_seekHeight);
	m_play->setGeometry((trim_width - m_seekWidth) * lseek, 0, m_seekWidth/2, m_seekHeight);
}
void TrimBar::fitSeekPlayItems(qreal pseek)
{
	m_play->setGeometry((trim_width - m_seekWidth / 2) * pseek, 0, m_seekWidth/2, m_seekHeight);
}

void TrimBar::setSeekItems(qreal lseek, qreal rseek)
{
	qreal tmp_lseek,tmp_rseek;
	m_st = lseek;
	m_en = rseek;

	fitSeekItems(m_st, m_en);
}
void TrimBar::resizeEvent(QResizeEvent *)
{
	trim_width = width();
	fitSeekItems(m_st,m_en);
}
int TrimBar::realToVirtual(int real)
{
	int val=-1;
	val = ((trim_width - m_seekWidth) / trim_width)*real;
	return val;
}
int TrimBar::virtualToReal(int vir)
{
	int val = -1;
	val = (trim_width / (trim_width - m_seekWidth))*vir;
	return val;
}