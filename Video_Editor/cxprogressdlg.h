#ifndef CXPROGRESSDLG_H
#define CXPROGRESSDLG_H

#include <QDialog>
#include <QProcess>

#include "common.h"
#define SINGLEVIDEOCREATE 0
#include <QLabel>

class CXProgressDlg : public QDialog
{
	Q_OBJECT

public:
	CXProgressDlg(QWidget *parent = 0);
	~CXProgressDlg();
signals:
	void __processFinished();
public:
	
	void setSingleAudioPath(QString str);
	void startProgress(QStringList arg, int dur = -1, QString str = "Processing ...");
	void startProgress(QString cmd);
	void startProgress();
	private slots:
	void onProcessFinished(int, QProcess::ExitStatus);
	void onProcessStandardOutput();
protected:
	void closeEvent(QCloseEvent* event);
	void resizeEvent(QResizeEvent*);
	void paintEvent(QPaintEvent*);
private:
	void initUI();
	QProcess* m_process;
	int m_state;
	QString m_singleAudioPath;
	QPixmap back;
};

#endif // CXPROGRESSDLG_H
