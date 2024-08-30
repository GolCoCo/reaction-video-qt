#include "cxprogressdlg.h"
#include <QTime>
#include <QCloseEvent>
#include <QLabel>
#include <QMovie>
#include <QHBoxLayout>
#include <QBitmap>
#include <QPainter>
CXProgressDlg::CXProgressDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
	//this->setFixedSize(300, 300);
	back.load(":/Video_Editor/Resources/loading.gif");
	m_process = new QProcess(this);
	m_process->setProcessChannelMode(QProcess::MergedChannels);
	connect(m_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(onProcessFinished(int, QProcess::ExitStatus)));
	initUI();
}

CXProgressDlg::~CXProgressDlg()
{

}
void CXProgressDlg::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	QPixmap scaled_img = back.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	painter.drawPixmap(0,0,width(),height(),scaled_img);
}
void CXProgressDlg::initUI()
{
	QHBoxLayout *layout = new QHBoxLayout;
	layout->setContentsMargins(0, 0, 0, 0);
	QLabel *lbl_banner = new QLabel(this);
	QMovie *movie = new QMovie(":/Video_Editor/Resources/loading.gif");
	lbl_banner->setMovie(movie);
	layout->addWidget(lbl_banner);
	setLayout(layout);
	movie->start();
}
void CXProgressDlg::setSingleAudioPath(QString str)
{
	m_singleAudioPath = str;
	m_state = SINGLEVIDEOCREATE;
}

void CXProgressDlg::startProgress()
{
	exec();
}

void CXProgressDlg::startProgress(QStringList arg, int dur, QString str)
{
	m_process->start("ffmpeg", arg);
	exec();
}

void CXProgressDlg::startProgress(QString cmd)
{
	m_process->start(cmd);
	exec();
}


void CXProgressDlg::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
	emit __processFinished();
	accept();
}

void CXProgressDlg::onProcessStandardOutput()
{
	
}

void CXProgressDlg::closeEvent(QCloseEvent* event)
{
	emit __processFinished();
	if (m_process->state() == QProcess::Running) m_process->terminate();
	event->accept();
}
void CXProgressDlg::resizeEvent(QResizeEvent*)
{
	setMask(back.mask());
}
