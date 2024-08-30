#ifndef TRIMBAR_H
#define TRIMBAR_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

class TrimBar : public QLabel
{
	Q_OBJECT

public:
	TrimBar(int typeOfBar, QWidget *parent=0);
	~TrimBar();
	void setEnableControl(bool iscon);
public slots:
	void fitSeekItems(qreal lseek,qreal rseek);
	void fitSeekPlayItems(qreal pseek);
	void setSeekItems(qreal lseek, qreal rseek);
signals:
	void __SeekJumpChanged(qreal seek);
	void __playSeekChanged(qreal seek);
	void __leftSeekChanged(qreal seek);
	void __rightSeekChanged(qreal seek);
	
	
protected:
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent* e);
	void mouseMoveEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void resizeEvent(QResizeEvent *);
private:
	int realToVirtual(int real);
	int virtualToReal(int vir);

	QLabel *m_left;
	QLabel *m_right;
	QLabel* m_play;

	qreal curSeekPos;
	qreal m_st;
	qreal m_en;
	int m_movingIndex;
	QLineEdit *lineEdit;
	QTimer *timer;
	qreal trim_width;
	int typeOfBar;
	bool isControl;
	
};

#endif // TRIMBAR_H
