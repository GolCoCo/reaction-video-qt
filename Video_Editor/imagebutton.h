#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QPushButton>
#include <QListWidget>

class ImageButton : public QPushButton
{
	Q_OBJECT

public:
	ImageButton(QWidget *parent=0);
	ImageButton(QListWidgetItem* item, QWidget* parent = 0);
	~ImageButton();
	void setImages(QString normal,QString over, QString press);

signals:
	void setIsFade(QListWidgetItem* item);

private slots:
	void on_BtnClicked();

protected:
	void paintEvent(QPaintEvent*);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
private:
	QImage normal_img;
	QImage press_img;
	QImage over_img;
	QListWidgetItem* m_item;

	int state;

	
};

#endif // IMAGEBUTTON_H
