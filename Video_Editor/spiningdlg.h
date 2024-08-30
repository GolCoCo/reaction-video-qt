#ifndef SPININGDLG_H
#define SPININGDLG_H

#include <QLabel>

class SpiningDlg : public QLabel
{
	Q_OBJECT

public:
	SpiningDlg(QWidget *parent=0);
	~SpiningDlg();

protected:
	void resizeEvent(QResizeEvent *);
private:
	QPixmap back;

};

#endif // SPININGDLG_H
