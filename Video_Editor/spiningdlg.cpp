#include "spiningdlg.h"
#include <QBitmap>
#include <QMovie>
#include <QHBoxLayout>

SpiningDlg::SpiningDlg(QWidget *parent)
	: QLabel(parent)
{
	QHBoxLayout *layout = new QHBoxLayout();
	QLabel *lbl = new QLabel;
	QMovie *movie = new QMovie(":/Video_Editor/Resources/loading.gif");
	lbl->setMovie(movie);
	layout->addWidget(lbl,1,Qt::AlignCenter);
	movie->start();
	setStyleSheet("QLabel{background-color:black}");
	setLayout(layout);

}

SpiningDlg::~SpiningDlg()
{

}
void SpiningDlg::resizeEvent(QResizeEvent *)
{
	
}