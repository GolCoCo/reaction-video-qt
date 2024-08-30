#ifndef VIDEO_EDITOR_H
#define VIDEO_EDITOR_H

#include <QtWidgets/QMainWindow>
#include <QMultiMedia>
#include <QVideoWidget>
#include <QMediaPlayer>
#include "Global.h"
#include "videoitem.h"
#include "trimbar.h"
#include "videolistwidget.h"
#include "common.h"
#include "cxprogressdlg.h"
#include "dropdeletepane.h"
#include "spiningdlg.h"
#include "shadow.h"
#include <QStackedWidget>
#include <QSpacerItem>
#include "imagebutton.h"
#include "videoitem.h"
#include "CameraPreiview.h"
#include <windows.h>
#include "wavfile.h"
#include <ColorPickerDlg.h>
#pragma comment(lib, "winmm.lib")

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QListWidget;
class QListWidgetItem;
QT_END_NAMESPACE
class Video_Editor : public QMainWindow
{
	Q_OBJECT

public:
	Video_Editor(QWidget *parent = 0);
	void rounded_rectangle1(Mat& src, Point topLeft, Point bottomRight, const Scalar lineColor, int thickness, const int lineType, const int cornerRadius);
	void videoClose();
	~Video_Editor();
private slots:
	void updateVideoPreview();
	QPixmap processImage(Mat& frame);
	void onUpload();
	void createWavFileFromVideo(QString filepath, QString filename);
	void openWavFile(QString wavfilepath);
	void recordVideo();
	void changeBorderThin();
	void changeBackgroundColor();
	void changeBorderShape();
	QString createScaledFromImage(QString filepath, QString filename);
	void play();
	void stop();
	void pause();
	void createVideoWriter(Mat frame, QString filename);
	void selectVideo(int current);
	void videoPlay();
	void playSeekChange(qreal seek);
	void leftSeekChange(qreal seek);
	void rightSeekChange(qreal seek);

	void mergeSimpleVideoFiles(QString resultFileName, QString recVideoFileName);
	void UpSpin();
	void DownSpin();
	void refreshVideoItems();
	void deleteVideoItem();
	void setEnabledLoadDeleteBtn(bool isEnable);
	void openColorPickerDlg();
	void updateAllPreview();
	void delay();
	void changeVideoBorderColor();
	void saveResultVideo();
	void RecordListner();
	void EndButtonListner();
	void initUI();

private:

		
	QAbstractButton *playButton;
	QAbstractButton *nextButton;
	QAbstractButton *previousButton;
	ImageButton* mergeModeCheck;

	VideoListWidget* video_listwidget;
	QList<VideoItem*> videoItem_list;

	int current_index;
	int current_frame;

	int frame_counter;
	int record_frame_counter;
	ColorPickerDlg* my_progress_dialog;
	QTimer *timer;
	int playerState;
	QLabel *time_label;

	CXProgressDlg* m_progressDlg;
	QPixmap empty_pixmap;
	Shadow *shadow;
	QWidget *main_widget;
	QStackedWidget *stack;
	SpiningDlg *spin;
	QSpacerItem *control_spacerItem;
	bool mergeOption;

	//
	CameraPreiview* camPrieview;
	VideoItem* video;
	QPushButton* startBtn;
	QPushButton* saveBtn;
	VideoCapture current_video;
	TrimBar* trimbar;
	ImageButton* up_btn;
	ImageButton* down_btn;
	ImageButton* upload_btn;
	ImageButton* delete_btn;
	ImageButton* boldborder_btn;
	ImageButton* pickback_btn;
	ImageButton* shapeborder_btn;
	ImageButton* shapebordercam_btn;

	VideoCapture cap;

	Scalar* backvalue;

	VideoWriter outputVidWriter;
	TrimBar* camTrimbar;
	//Temp
	QLabel* tempLabel;
	double m_recoStartTime;
	Mat vidframe;
	vector<Mat>* resultFrames;

	QPixmap vidFramePixmap;
	QTimer* recordTimer;
	WavManager* wavman;
	int camDelay;
	bool m_isRecordState;
	int m_CurrentIndex;
	double m_RecordDuration;

	// for processing video pixmap
	double vidTop;
	double vidLeft;
	double vidBottom;
	double vidRight;
	Scalar* __value;
	bool isVidBorderThin;
	bool isVidBorderShape;
	bool isCamBorderShape;
};

#endif // VIDEO_EDITOR_H
