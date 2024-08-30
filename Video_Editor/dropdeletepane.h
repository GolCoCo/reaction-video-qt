#ifndef DROPDELETEPANE_H
#define DROPDELETEPANE_H

#include <QLabel>

class DropDeletePane : public QLabel
{
	Q_OBJECT

public:
	DropDeletePane(QWidget *parent=0);
	~DropDeletePane();
signals:
	void __selectedDeleteItem(int loc);
protected:
	void paintEvent(QPaintEvent *e);
	void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
private:
	
};

#endif // DROPDELETEPANE_H
