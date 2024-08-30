#include "video_editor.h"
#include <qtoolbutton.h>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QFileDialog>
#include <QGroupBox>
#include <qtimer.h>
#include <QTimerEvent>
#include <QListWidget>
#include <qcheckbox.h>
#include <windows.h>
#include <stdio.h>
#include <ColorPickerDlg.h>

Video_Editor::Video_Editor(QWidget *parent)
	: QMainWindow(parent)
{
	// Create log

	if (QDir("./sound_temp").exists()) {
		QDir("./sound_temp").removeRecursively();
	}
	if (QDir("./vid_temp").exists()) {
		QDir("./vid_temp").removeRecursively();
	}
	if (QDir("./image_temp").exists()) {
		QDir("./image_temp").removeRecursively();
	}

	// make sound_temp and vid_temp directory
	if (!QDir("./sound_temp").exists()) {
		QDir().mkdir("./sound_temp");
	}
	if (!QDir("./vid_temp").exists()) {
		QDir().mkdir("./vid_temp");
	}
	if (!QDir("./image_temp").exists()) {
		QDir().mkdir("./image_temp");
	}

	m_isRecordState = false;
	m_CurrentIndex = 0;
	m_RecordDuration = 500000;

	empty_pixmap.load(":/Video_Editor/Resources/empty.png");
	m_progressDlg = new CXProgressDlg(this);

	frame_counter = 0;
	mergeOption = true;
	video = NULL;
	m_recoStartTime = 0.0;
	
	timer = new QTimer(this);
	recordTimer = new QTimer(this);

	shadow = new Shadow(this);
	shadow->setWindowFlags(Qt::SplashScreen);
	shadow->setWindowOpacity(0.6);

	__value = new Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	backvalue = new Scalar(0, 0, 0);

	initUI();
	resultFrames = new vector<Mat>();
	trimbar->setEnableControl(false);
	connect(timer, SIGNAL(timeout()), this, SLOT(videoPlay()));

	connect(recordTimer, SIGNAL(timeout()), this, SLOT(recordVideo()));

	connect(m_progressDlg, SIGNAL(__processFinished()), shadow, SLOT(close()));
	
	record_frame_counter = 0;
	isVidBorderThin = true;
	isVidBorderShape = false;
}
void Video_Editor::createWavFileFromVideo(QString filepath, QString filename) {
	QString wavfilepath = QDir().currentPath() + "/sound_temp/" + QString("%1.wav").arg(filename);
	QString cmdMp4ToWav = QString("ffmpeg -i \"%1\" -vn -y  \"%2\"").arg(filepath).arg(wavfilepath);
	m_progressDlg->startProgress(cmdMp4ToWav);
	//openWavFile(wavfilepath);
}
void Video_Editor::openWavFile(QString wavfilepath) {
	wavfilepath.replace("/", "\\\\");
	try {
		mciSendString(L"close wav1", NULL, 0, 0);
		QString mciCmd = QString("open \"%1\" alias wav1").arg(wavfilepath);
		mciSendString(mciCmd.toStdWString().c_str(), NULL, 0, 0);
		mciSendString(L"set wav1 time format ms", NULL, 0, 0);
	}
	catch (Exception e) {
	}
}
void Video_Editor::recordVideo()
{
	Mat resultMat = QImage2Mat(vidFramePixmap.toImage());
	resultFrames->push_back(resultMat);
	
	record_frame_counter = record_frame_counter + 1;
	if (record_frame_counter % 40 > 20) {
		camPrieview->setVisibleRecordLabel(false);
	}
	else {
		camPrieview->setVisibleRecordLabel(true);
	}
	double perFrame = double(record_frame_counter) * 1000 / video->m_fps;
	camTrimbar->fitSeekPlayItems((perFrame) / (m_RecordDuration));

}

void Video_Editor::rounded_rectangle1(Mat& src, Point topLeft, Point bottomRight, const Scalar lineColor, int thickness, const int lineType, const int cornerRadius)
{
	Point p1 = topLeft;
	Point p2 = Point(bottomRight.x, topLeft.y);
	Point p3 = bottomRight;
	Point p4 = Point(topLeft.x, bottomRight.y);

	line(src, Point(p1.x + cornerRadius, p1.y), Point(p2.x - cornerRadius, p2.y), lineColor, thickness, lineType);
	line(src, Point(p2.x, p2.y + cornerRadius), Point(p3.x, p3.y - cornerRadius), lineColor, thickness, lineType);
	line(src, Point(p4.x + cornerRadius, p4.y), Point(p3.x - cornerRadius, p3.y), lineColor, thickness, lineType);
	line(src, Point(p1.x, p1.y + cornerRadius), Point(p4.x, p4.y - cornerRadius), lineColor, thickness, lineType);

	ellipse(src, p1 + Point(cornerRadius, cornerRadius), Size(cornerRadius, cornerRadius), 180.0, 0, 90, lineColor, thickness, lineType);
	ellipse(src, p2 + Point(-cornerRadius, cornerRadius), Size(cornerRadius, cornerRadius), 270.0, 0, 90, lineColor, thickness, lineType);
	ellipse(src, p3 + Point(-cornerRadius, -cornerRadius), Size(cornerRadius, cornerRadius), 0.0, 0, 90, lineColor, thickness, lineType);
	ellipse(src, p4 + Point(cornerRadius, -cornerRadius), Size(cornerRadius, cornerRadius), 90.0, 0, 90, lineColor, thickness, lineType);

	// choose arbitrary starting point for fill => Top left plus 10,10
	Point fillFrom(topLeft.x + 10, topLeft.y + 10);
	Scalar fillColor(0, 0, 0, 0);
	// You may want to use `lineColor` instead of `fillColor`
	floodFill(src, fillFrom, fillColor);
}
void Video_Editor::videoClose() {
	current_video.release();

}

Video_Editor::~Video_Editor()
{
	videoClose();
	if (QDir("./image_temp").exists()) {
		QDir("./image_temp").removeRecursively();
	}
	if (QDir("./sound_temp").exists()) {
		QDir("./sound_temp").removeRecursively();
	}
	if (QDir("./vid_temp").exists()) {
		QDir("./vid_temp").removeRecursively();
	}
}
void Video_Editor::delay()
{
		selectVideo(m_CurrentIndex);
		refreshVideoItems();
}

void Video_Editor::changeVideoBorderColor()
{
	if (video == NULL) return; 
	QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color", QColorDialog::DontUseNativeDialog);
	//value = new Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	int R, G, B;
	color.getRgb(&R, &G, &B);
	__value = new Scalar(B, G, R);
	updateVideoPreview();
}

void Video_Editor::updateVideoPreview() {
	Mat frame;
	if (video->m_IsVideo) {
		current_video.set(CV_CAP_PROP_POS_MSEC, video->m_startOffset);
		current_video >> frame;
	}
	else {
		frame = QImage2Mat(QImage(video->m_filePath));
	}

	camPrieview->setVideoPixmap(processImage(frame));
}

void Video_Editor::saveResultVideo()
{
	if (playerState != 0) return;

	if (resultFrames->size() == 0) return;
	QString resultFileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("MP4 files (*.mp4)"));

	QString recVideoFileName = QDir().currentPath() + "/vid_temp/" + QString("%1_recVid.avi").arg(video->m_fileName);
	if (resultFileName.isEmpty())return;

	createVideoWriter(resultFrames->at(0), recVideoFileName);

	for (int i = 0; i < resultFrames->size(); i++ ) {
		Mat temp = resultFrames->at(i);
		outputVidWriter.write(temp);
	}

	outputVidWriter.release();

	mergeSimpleVideoFiles(resultFileName, recVideoFileName);
	QMessageBox::information(NULL, "", QString("Created the reaction video. The file is in %1%2").arg(resultFileName).arg("."));
	resultFrames->clear();
}
void Video_Editor::initUI()
{
	// File UpLoad UI
	QWidget* FileUpLoadPart = new QWidget();
	QHBoxLayout* fileupload_layout = new QHBoxLayout();
	FileUpLoadPart->setStyleSheet("QWidget{background-color:#404040}");
	QPushButton* fileLoadBtn = new QPushButton("VideoFile LOAD");
	connect(fileLoadBtn, SIGNAL(clicked(bool)), this, SLOT(onUpload()));
	fileLoadBtn->setFixedHeight(35);
	fileLoadBtn->setStyleSheet("QPushButton{font-size:20px; font-weight:bold; background-color: #cecece; color:black;}");
	fileupload_layout->addWidget(fileLoadBtn);
	fileupload_layout->setContentsMargins(0, 0, 0, 0);
	FileUpLoadPart->setLayout(fileupload_layout);
	
	// Video Preview UI

	QWidget* VideoPreviewPart = new QWidget();

	// Video Preview UI
	camPrieview = new CameraPreiview(QSize(880,530), VideoPreviewPart);
	connect(camPrieview, &CameraPreiview::doulbleclicked, this, &Video_Editor::changeVideoBorderColor);

	//Video Control UI
	QWidget* ControlVideoPart = new QWidget();
	QWidget* videoSeeKPart = new QWidget();
	QHBoxLayout* videoSeeKPart_layout = new QHBoxLayout();

	trimbar = new TrimBar(0);
	trimbar->setFixedHeight(42);
	//connect(trimbar, SIGNAL(__leftSeekChanged(qreal)), this, SLOT(leftSeekChange(qreal)));
	//connect(trimbar, SIGNAL(__rightSeekChanged(qreal)), this, SLOT(rightSeekChange(qreal)));
	connect(trimbar, SIGNAL(__playSeekChanged(qreal)), this, SLOT(playSeekChange(qreal)));
	connect(trimbar, SIGNAL(__SeekJumpChanged(qreal)), this, SLOT(playSeekChange(qreal)));
	startBtn = new QPushButton("Start");
	startBtn->setFixedSize(100, 42);
	startBtn->setStyleSheet("QPushButton{font-size:20px; font-weight:bold; background-color: #ff8a37; color: black;}");
	connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(play()));

	videoSeeKPart_layout->addWidget(trimbar);
	videoSeeKPart_layout->addWidget(startBtn);
	videoSeeKPart_layout->setStretch(0, 10);
	videoSeeKPart_layout->setStretch(1, 2);
	videoSeeKPart_layout->setContentsMargins(5, 5, 5, 0);
	videoSeeKPart->setLayout(videoSeeKPart_layout);
	QWidget* updownSpinPart = new QWidget();
	updownSpinPart->setFixedWidth(70);
	up_btn = new ImageButton();
	up_btn->setFixedSize(32, 32);
	up_btn->setContentsMargins(15, 0, 5, 0);
	up_btn->setImages(":/Video_Editor/Resources/upspin_normal.png", ":/Video_Editor/Resources/upspin_normal.png", ":/Video_Editor/Resources/upspin_press.png");
	connect(up_btn, SIGNAL(clicked(bool)), this, SLOT(UpSpin()));
	down_btn = new ImageButton();
	down_btn->setFixedSize(32, 32);
	down_btn->setContentsMargins(15, 0, 5, 0);
	down_btn->setImages(":/Video_Editor/Resources/downspin_normal.png", ":/Video_Editor/Resources/downspin_normal.png", ":/Video_Editor/Resources/downspin_press.png");
	connect(down_btn, SIGNAL(clicked(bool)), this, SLOT(DownSpin()));

	QHBoxLayout *spin_layout = new QHBoxLayout;
	spin_layout->addWidget(down_btn);
	spin_layout->addWidget(up_btn);
	updownSpinPart->setLayout(spin_layout);

	QWidget* timeLabelPart = new QWidget();
	QHBoxLayout* timeLabelPart_layout = new QHBoxLayout();
	time_label = new QLabel;
	QString st = QTime::fromMSecsSinceStartOfDay(0).toString();
	time_label->setText("<font color='white'>" + QString("%1 / %2").arg(st).arg(st) + "</font>");
	time_label->setAlignment(Qt::AlignCenter);
	time_label->setFont(QFont("", 18, -1, false));
	timeLabelPart_layout->addWidget(time_label);
	timeLabelPart_layout->setAlignment(Qt::AlignCenter);
	timeLabelPart_layout->addWidget(updownSpinPart);
	timeLabelPart_layout->setContentsMargins(0, 0, 0, 0);
	timeLabelPart->setLayout(timeLabelPart_layout);

	QWidget* camvideoSeekPart = new QWidget();
	QHBoxLayout* camvideoSeekPart_layout = new QHBoxLayout();

	camTrimbar = new TrimBar(1);
	camTrimbar->setFixedHeight(42);
	saveBtn = new QPushButton("End");
	saveBtn->setFixedSize(100,42);

	saveBtn->setStyleSheet("QPushButton{font-size:20px; font-weight:bold; background-color: #ff8a37; color: black;}");
	camvideoSeekPart_layout->addWidget(camTrimbar);
	camvideoSeekPart_layout->addWidget(saveBtn);
	camvideoSeekPart_layout->setStretch(0, 10);
	camvideoSeekPart_layout->setStretch(1, 2);
	camvideoSeekPart_layout->setContentsMargins(5, 0, 5, 0);
	camvideoSeekPart->setLayout(camvideoSeekPart_layout);
	connect(saveBtn, SIGNAL(clicked(bool)), this, SLOT(EndButtonListner()));

	QVBoxLayout* controlvideo_layout = new QVBoxLayout();
	controlvideo_layout->setContentsMargins(5, 2, 5, 10);
	controlvideo_layout->addWidget(videoSeeKPart);
	controlvideo_layout->addWidget(timeLabelPart);
	controlvideo_layout->addWidget(camvideoSeekPart);
	ControlVideoPart->setStyleSheet("QWidget{background-color:#404040}");
	ControlVideoPart->setLayout(controlvideo_layout);
	ControlVideoPart->setFixedHeight(170);

	QWidget* submainWidget1 = new QWidget();
	QVBoxLayout* submainLayout1 = new QVBoxLayout();
	submainLayout1->addWidget(camPrieview);	
	submainLayout1->addWidget(ControlVideoPart);
	submainLayout1->setContentsMargins(0, 5, 0, 2);
	submainLayout1->setSpacing(0);
	submainLayout1->setStretch(0, 10);
	submainLayout1->setStretch(1, 2);
	submainWidget1->setLayout(submainLayout1);

	QWidget* submainwidget2 = new QWidget();
	submainwidget2->setFixedWidth(100);
	video_listwidget = new VideoListWidget(&videoItem_list);
	connect(video_listwidget, SIGNAL(currentRowChanged(int)), this, SLOT(selectVideo(int)));
	video_listwidget->setStyleSheet("QListWidget{background-color:#404040; outline:0;} QListWidget::item {padding:1px; padding-left:1px; color:black;} QListWidget::item:selected{border-style:solid; border-width:4px; border-color:blue; background-color:rgb(56, 83, 125);}");

	QHBoxLayout* btn_layout = new QHBoxLayout;

	upload_btn = new ImageButton;
	upload_btn->setToolTip("Open Multi Video Files");
	upload_btn->setImages(":/Video_Editor/Resources/open_normal.png", ":/Video_Editor/Resources/open_over.png", ":/Video_Editor/Resources/open_press.png");
	upload_btn->setFixedSize(48, 48);
	connect(upload_btn, SIGNAL(clicked(bool)), this, SLOT(onUpload()));

	delete_btn = new ImageButton;
	delete_btn->setFixedSize(48, 48);
	delete_btn->setImages(":/Video_Editor/Resources/trash.png", ":/Video_Editor/Resources/trash_over.png", ":/Video_Editor/Resources/trash_press.png");
	delete_btn->setToolTip("Delete Seleted Video");
	connect(delete_btn, SIGNAL(clicked(bool)), this, SLOT(deleteVideoItem()));

	btn_layout->addWidget(upload_btn);
	btn_layout->addWidget(delete_btn);


	QHBoxLayout* btn_layout1 = new QHBoxLayout;

	boldborder_btn = new ImageButton;
	boldborder_btn->setToolTip("Choose Bold/Singlar Border");
	boldborder_btn->setImages(":/Video_Editor/Resources/boldborder.png", ":/Video_Editor/Resources/boldborder_hover.png", ":/Video_Editor/Resources/boldborder_hover.png");
	boldborder_btn->setFixedSize(48, 48);
	connect(boldborder_btn, SIGNAL(clicked(bool)), this, SLOT(changeBorderThin()));

	pickback_btn = new ImageButton;
	pickback_btn->setFixedSize(48, 48);
	pickback_btn->setImages(":/Video_Editor/Resources/colorpicker1.png", ":/Video_Editor/Resources/colorpicker1_hover", ":/Video_Editor/Resources/colorpicker1_hover.png");
	pickback_btn->setToolTip("Pick color of background");
	connect(pickback_btn, SIGNAL(clicked(bool)), this, SLOT(changeBackgroundColor()));

	btn_layout1->addWidget(boldborder_btn);
	btn_layout1->addWidget(pickback_btn);

	QHBoxLayout* btn_layout2 = new QHBoxLayout;

	shapeborder_btn = new ImageButton;
	shapeborder_btn->setToolTip("Choose Shape of Border");
	shapeborder_btn->setImages(":/Video_Editor/Resources/shapepicker.png", ":/Video_Editor/Resources/shapepicker_hover.png", ":/Video_Editor/Resources/shapepicker_hover.png");
	shapeborder_btn->setFixedSize(48, 48);
	connect(shapeborder_btn, SIGNAL(clicked(bool)), this, SLOT(changeBorderShape()));

	shapebordercam_btn = new ImageButton;
	shapebordercam_btn->setFixedSize(48, 48);
	shapebordercam_btn->setImages(":/Video_Editor/Resources/colorpicker.png", ":/Video_Editor/Resources/colorpicker_hover.png", ":/Video_Editor/Resources/colorpicker_hover.png");
	shapebordercam_btn->setToolTip("Pick color of background");
	connect(shapebordercam_btn, SIGNAL(clicked(bool)), this, SLOT(openColorPickerDlg()));

	btn_layout2->addWidget(shapeborder_btn);
	btn_layout2->addWidget(shapebordercam_btn);


	QVBoxLayout* submainLayout2 = new QVBoxLayout();
	submainLayout2->addWidget(video_listwidget);
	submainLayout2->addLayout(btn_layout2);
	submainLayout2->addLayout(btn_layout1);
	submainLayout2->addLayout(btn_layout);
	submainLayout2->setContentsMargins(0, 0, 0, 0);
	submainLayout2->setSpacing(4);
	submainLayout2->setStretch(0, 10);
	submainLayout2->setStretch(1, 2);
	submainLayout2->setStretch(2, 2);
	submainLayout2->setStretch(3, 2);
	submainwidget2->setLayout(submainLayout2);

	// Main UI
	QHBoxLayout* main_layout = new QHBoxLayout();
	main_layout->addWidget(submainWidget1);
	main_layout->addWidget(submainwidget2);
	main_layout->setStretch(0, 10);
	main_layout->setStretch(1, 3);
	main_layout->setContentsMargins(4, 4, 4, 4);
	main_layout->setSpacing(4);
	main_widget = new QWidget();
	main_widget->setStyleSheet("QWidget{background-color:grey}");
	main_widget->setLayout(main_layout);
	setCentralWidget(main_widget);
}
void Video_Editor::EndButtonListner() {

	camPrieview->setVisibleRecordLabel(false);
	stop();
	recordTimer->stop();
	record_frame_counter = 0;
	camTrimbar->fitSeekPlayItems(0);
	frame_counter = 0;
	video->m_startOffset = 0;
	////
	QString recfilepath = QDir().currentPath() + "/sound_temp/" + QString("resultRec.wav");
	recfilepath.replace("/", "\\\\");
	QString mcicmd = QString("save capture  \"%1\"").arg(recfilepath);
	mciSendStringW(mcicmd.toStdWString().c_str(), NULL, 0, 0);
	mciSendStringW(L"close capture  ", NULL, 0, 0);

	saveResultVideo();
	m_isRecordState = false;
	startBtn->setText("Start");

}

void Video_Editor::RecordListner() {
	if (video == NULL) return;
	if (saveBtn->text() == "Record") {
		mciSendStringW(L"open new Type waveaudio Alias capture", NULL, 0, 0);
		mciSendStringW(L"set capture time format ms bitspersample 16 channels 2 samplespersec 48000 bytespersec 192000 alignment 4", NULL, 0, 0);
		mciSendStringW(L"record capture", 0, 0, 0);
		saveBtn->setText("End");
		
		if (startBtn->text() == "Start") {
			play();
		}
		recordTimer->start(video->m_fps);
	}
	else {
		
		camPrieview->setVisibleRecordLabel(false);
		stop();
		recordTimer->stop();
		record_frame_counter = 0;
		camTrimbar->fitSeekPlayItems(0);
		frame_counter = 0;
		video->m_startOffset = 0;
		
		QString recfilepath = QDir().currentPath() + "/temp/" + QString("%1_recMic.wav").arg(video->m_fileName);
		recfilepath.replace("/", "\\\\");
		QString mcicmd = QString("save capture  \"%1\"").arg(recfilepath);
		mciSendStringW(mcicmd.toStdWString().c_str(), NULL, 0, 0);
		mciSendStringW(L"close capture  ", NULL, 0, 0);
		saveResultVideo();
		saveBtn->setText("Record");
	}
}
void Video_Editor::onUpload()
{
	if (m_isRecordState) {
		QMessageBox::warning(this, tr("Warning"), tr("Could not add and delete the files in Recording."));
		return;
	}
	QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Upload MP4 and JPEG, PNG files"), tr(""), tr("Media and Image Files (*.mp4 *.avi *.wmv *.jpg *.png)"));
	if (fileNames.length() < 1) return;
	for (int i = 0; i < fileNames.length(); i++)
	{
		QString path = fileNames[i];
		if (!isValidSuffix(path)) continue;

		if (isVideoFile(path)) {
			VideoInfo tmp = getInfomationOfVideo(path);
			VideoItem* video = new VideoItem();
			video->m_IsVideo = true;
			video->m_filePath = tmp.m_filePath;
			video->m_fileName = tmp.m_fileName;
			video->m_duration = tmp.m_duration;
			video->m_fps = tmp.m_fps;
			video->m_frameCount = tmp.m_frameCount;
			video->m_startTime = tmp.m_startTime;
			video->m_endTime = tmp.m_endTime;
			video->m_titleImg = tmp.m_titleImg;
			video->m_startOffset = 0;
			video->m_endOffset = 0;
			video->m_index = videoItem_list.length();
			videoItem_list.append(video);
			// the Function for convert Mp4 to Wav file..
			shadow->showMaximized();
			createWavFileFromVideo(video->m_filePath, video->m_fileName);
		}
		else {
			QFileInfo finfo(path);
			VideoItem* video = new VideoItem();
			QString tempfilepath = createScaledFromImage(path, finfo.baseName());
			video->m_IsVideo = false;
			video->m_filePath = tempfilepath;
			video->m_fileName = finfo.baseName();
			video->m_duration = 5000;
			video->m_titleImg = QPixmap(tempfilepath);
			video->m_fps = 29;
			video->m_IsFadeEffect = true;
			video->m_index = videoItem_list.length();
			videoItem_list.append(video);
		}
	}
	QTimer::singleShot(1000, this, SLOT(delay()));
}
void Video_Editor::changeBorderThin() {
	if (video == NULL) return;

	if (isVidBorderThin) {
		isVidBorderThin = false;
		boldborder_btn->setImages(":/Video_Editor/Resources/boldborder1.png", ":/Video_Editor/Resources/boldborder1_hover.png", ":/Video_Editor/Resources/boldborder1_hover.png");
	}
	else {
		isVidBorderThin = true;
		boldborder_btn->setImages(":/Video_Editor/Resources/boldborder.png", ":/Video_Editor/Resources/boldborder_hover.png", ":/Video_Editor/Resources/boldborder_hover.png");
	}
	Mat frame;
	if (video->m_IsVideo) {
		current_video.set(CV_CAP_PROP_POS_MSEC, video->m_startOffset);
		current_video >> frame;
	}
	else {
		frame = QImage2Mat(QImage(video->m_filePath));
	}
	camPrieview->setVideoPixmap(processImage(frame));
}
void Video_Editor::changeBackgroundColor() {

	if (video == NULL) return;
	QColor color = QColorDialog::getColor(Qt::black, this, "Pick a color", QColorDialog::DontUseNativeDialog);
	int R, G, B;
	color.getRgb(&R, &G, &B);
	backvalue = new Scalar(B, G, R);

	Mat frame;
	if (video->m_IsVideo) {
		current_video.set(CV_CAP_PROP_POS_MSEC, video->m_startOffset);
		current_video >> frame;
	}
	else {
		frame = QImage2Mat(QImage(video->m_filePath));
	}
	camPrieview->setVideoPixmap(processImage(frame));
}
void Video_Editor::changeBorderShape() {
	if (video == NULL) return;

	if (isVidBorderShape) {
		isVidBorderShape = false;
	}
	else {
		isVidBorderShape = true;
	}
	Mat frame;

	if (video->m_IsVideo) {
		current_video.set(CV_CAP_PROP_POS_MSEC, video->m_startOffset);
		current_video >> frame;
	}
	else {
		frame = QImage2Mat(QImage(video->m_filePath));
	}
	camPrieview->setVideoPixmap(processImage(frame));

}
QString Video_Editor::createScaledFromImage(QString filepath, QString filename) {
	QString imagefilepath = QDir().currentPath() + "/image_temp/" + QString("%1.png").arg(filename);
	QString cmdImageScaled = QString("ffmpeg -i \"%1\" -vf scale=1280:800 -y \"%2\"").arg(filepath).arg(imagefilepath);
	shadow->showMaximized();
	m_progressDlg->startProgress(cmdImageScaled);
	return imagefilepath;
}

void Video_Editor::play()
{
	if (video == NULL) return;
	if (!m_isRecordState) {
		
		mciSendStringW(L"open new Type waveaudio Alias capture", NULL, 0, 0);
		mciSendStringW(L"set capture time format ms bitspersample 16 channels 2 samplespersec 48000 bytespersec 192000 alignment 4", NULL, 0, 0);
		mciSendStringW(L"record capture", 0, 0, 0);		
		m_isRecordState = true;
		recordTimer->start(29);
	}

	if (playerState == 1)
	{
		pause();
	}
	else {
		if (current_video.isOpened() && video->m_IsVideo)
		{
			playerState = 1;
			int delay = 1000 / video->m_fps;
			timer->start(video->m_fps);
			startBtn->setText("Pause");
			int duration = video->m_startTime + video->m_startOffset;
			current_video.set(CV_CAP_PROP_POS_MSEC, duration);
			try {
				QString mciCmd = QString("seek wav1 to %1").arg(duration);
				mciSendString(mciCmd.toStdWString().c_str(), NULL, 0, 0);
				mciSendString(L"play wav1", NULL, 0, 0);
			}
			catch (Exception e) {
			}
		}
		else {
			startBtn->setText("NoPlay");
		}
	}
}
void Video_Editor::stop() {

	trimbar->setEnableControl(true);
	current_video.set(CV_CAP_PROP_POS_MSEC, video->m_startTime);
	current_video >> vidframe;
	vidFramePixmap = processImage(vidframe);

	if (!vidframe.empty())
	{
		camPrieview->setVideoPixmap(vidFramePixmap);
	}
	mciSendString(L"pause wav1", NULL, 0, 0);
	playerState = 0;
	frame_counter = 0;
	video->m_startOffset = 0;
	timer->stop();
	startBtn->setText("Play");
}
void Video_Editor::pause()
{
	trimbar->setEnableControl(true);
	playerState = 0;
	timer->stop();

	startBtn->setText("Play");
	mciSendString(L"pause wav1", NULL, 0, 0);
}

void Video_Editor::createVideoWriter(Mat frame, QString filename) {
	int fourcc = CV_FOURCC('F', 'M', 'P', '4');
	//'F','M','P','4'
	//'M','J','P','G'
	//'X','V','I','D'
	bool isColor = (frame.type() == CV_8UC3);
	double fps = video->m_fps;
	outputVidWriter.open(filename.toStdString(), fourcc, fps, frame.size(), isColor);

	if (!outputVidWriter.isOpened()) {
		QMessageBox::information(NULL, "", "Could not open the output video file for write.");
	}
}

void Video_Editor::selectVideo(int current)
{
	if (video != NULL && m_isRecordState) {
		stop();
	}
	
	m_CurrentIndex = current;
	if (m_CurrentIndex < 0 || m_CurrentIndex > videoItem_list.length() - 1) return;
	if (current_video.isOpened()) current_video.release();

	video = videoItem_list[m_CurrentIndex];

	if (!video->m_IsVideo) {
		vidframe = QImage2Mat(QImage(video->m_filePath));
		vidFramePixmap = this->processImage(vidframe);
		camPrieview->setVideoPixmap(vidFramePixmap);
		return;
	}

	if (videoItem_list[m_CurrentIndex]->m_IsVideo) {
		current_video.open(videoItem_list[m_CurrentIndex]->m_filePath.toStdString().c_str());
	}

	current_video.open(video->m_filePath.toStdString().c_str());
	trimbar->setEnableControl(true);

	if (current_video.isOpened())
	{
		current_video.set(CV_CAP_PROP_POS_MSEC, video->m_startOffset);
		current_video >> vidframe;
		vidFramePixmap = this->processImage(vidframe);
		camPrieview->setVideoPixmap(vidFramePixmap);
	}
	else {
		vidframe = QImage2Mat(video->m_titleImg.toImage());
		vidFramePixmap = video->m_titleImg.scaled(camPrieview->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
		camPrieview->setVideoPixmap(vidFramePixmap);
	}
	
	double total_duration = 0, start_time = 0, end_time = 0, start_offset = 0, end_offset = 0;
	total_duration = video->m_duration;
	start_time = video->m_startTime;
	start_offset = video->m_startOffset;
	end_offset = video->m_endOffset;

	qreal lseek = (start_time + start_offset) / total_duration;
	qreal rseek = (total_duration - end_offset) /total_duration;
	trimbar->setSeekItems(lseek,rseek);

	qreal duration = start_time + start_offset;

	QString pro = QTime::fromMSecsSinceStartOfDay(duration).toString();
	QString rest = QTime::fromMSecsSinceStartOfDay(total_duration - end_offset).toString();
	time_label->setText("<font color='white'>" + QString("%1 / %2").arg(pro).arg(rest) + "</font>");

	frame_counter = 0;
	QString wavfilepath = QDir().currentPath() + "/sound_temp/" + QString("%1.wav").arg(video->m_fileName);
	openWavFile(wavfilepath);
}
void Video_Editor::videoPlay()
{
	if (m_CurrentIndex < 0 || m_CurrentIndex > (videoItem_list.length()) ) return;

	if (video == NULL || !video->m_IsVideo) return;

	double total_duration = 0, start_time = 0, end_time = 0, start_offset = 0, end_offset = 0, fps = 0;
	total_duration = video->m_duration;
	start_time = video->m_startTime;
	start_offset = video->m_startOffset;
	end_offset = video->m_endOffset;
	fps = video->m_fps;

	qreal perFrame = double(frame_counter) * 1000 / fps;

	while (perFrame < (start_time + start_offset))
	{
		frame_counter++;
		perFrame = double(frame_counter) * 1000 / fps;
	}

	qreal duration = perFrame;
	video->m_startOffset = duration - start_time;
	trimbar->fitSeekPlayItems( duration / (total_duration));

	QString pro = QTime::fromMSecsSinceStartOfDay(duration).toString();
	QString rest = QTime::fromMSecsSinceStartOfDay(total_duration - end_offset).toString();
	time_label->setText("<font color='white'>" + QString("%1 / %2").arg(pro).arg(rest) + "</font>");


	if (duration > (total_duration - end_offset - 10))
	{
		stop();
		return;
	}
	
	current_video >> vidframe;

	if (!vidframe.empty())
	{
		frame_counter+=1;
		vidFramePixmap = processImage(vidframe);
		camPrieview->setVideoPixmap(vidFramePixmap);
	}else
	{
		stop();
		return;
	}
}

void Video_Editor::playSeekChange(qreal seek)
{
	if (video == NULL || !video->m_IsVideo) return;
	double total_duration = 0, start_time = 0, end_time = 0, start_offset = 0, end_offset = 0;
	total_duration = video->m_duration;
	start_time = video->m_startTime;
	end_offset = video->m_endOffset;

	int duration = total_duration * seek;

	if (duration < start_time)
	{
		return;
	}
	if (duration > (total_duration - end_offset - 10)) {
		return;
	}
	QString mciCmd = QString("seek wav1 to %1").arg(duration);
	int rc = mciSendString(mciCmd.toStdWString().c_str(), NULL, 0, 0);

	if (playerState == 1) {
		mciSendString(L"play wav1", NULL, 0, 0);
	}

	video->m_startOffset = duration - start_time;

	start_offset = video->m_startOffset;

	QString pro = QTime::fromMSecsSinceStartOfDay(duration).toString();
	QString rest = QTime::fromMSecsSinceStartOfDay(total_duration - end_offset).toString();

	trimbar->fitSeekPlayItems(duration / total_duration);
	time_label->setText("<font color='white'>" + QString("%1 / %2").arg(pro).arg(rest) + "</font>");

	current_video.set(CV_CAP_PROP_POS_MSEC, duration);
	current_video >> vidframe;
	vidFramePixmap = processImage(vidframe);

	if (!vidframe.empty())
	{
		camPrieview->setVideoPixmap(vidFramePixmap);
	}
	frame_counter = 0;
}

void Video_Editor::leftSeekChange(qreal seek)
{
	if (video == NULL || !video->m_IsVideo) return;
	int seek_speed = 50;
	pause();
	double total_duration = 0, start_time = 0, end_time = 0, start_offset = 0, end_offset = 0;
	total_duration = video->m_duration;
	start_time = video->m_startTime;
	end_offset = video->m_endOffset;
	
	double duration = total_duration * seek;
	
	if (duration < 0)
	{
		return;
	}
	
	video->m_startTime = duration;
	video->m_startOffset = 0;

	start_offset = video->m_startOffset;

	qreal duration1 = start_time + start_offset;

	QString pro = QTime::fromMSecsSinceStartOfDay(duration1).toString();
	QString rest = QTime::fromMSecsSinceStartOfDay(total_duration - end_offset).toString();

	time_label->setText("<font color='white'>" + QString("%1 / %2").arg(pro).arg(rest) + "</font>");

	if ((int)duration % seek_speed == 0) {

		current_video.set(CV_CAP_PROP_POS_MSEC, duration);
		current_video >> vidframe;
		vidFramePixmap = processImage(vidframe);

		if (!vidframe.empty())
		{
			camPrieview->setVideoPixmap(vidFramePixmap);
		}
	}
	frame_counter = 0;
}
void Video_Editor::rightSeekChange(qreal seek)
{
	if (video == NULL || !video->m_IsVideo) return;
	int seek_speed = 50;
	Mat frame;
	pause();
	double total_duration = 0, start_time = 0, end_time = 0, start_offset = 0, end_offset = 0;
	total_duration = video->m_duration;
	start_time = video->m_startTime;
	start_offset = video->m_startOffset;

	double duration = video->m_duration * seek;
	qreal offset; 
	if (duration > total_duration- 10)
	{
		offset = 0;
		return;
	}

	offset = video->m_duration - duration;
	video->m_endOffset = offset;
	video->m_startOffset = 0;

	qreal duration1 = start_time + start_offset;

	QString pro = QTime::fromMSecsSinceStartOfDay(duration1).toString();
	QString rest = QTime::fromMSecsSinceStartOfDay(total_duration - offset).toString();

	time_label->setText("<font color='white'>" + QString("%1 / %2").arg(pro).arg(rest) + "</font>");

	if ((int)duration % seek_speed == 0) {
		current_video.set(CV_CAP_PROP_POS_MSEC, duration);
		current_video >> frame;
		camPrieview->setVideoPixmap(processImage(frame));
	}
	frame_counter = 0;
}
QPixmap Video_Editor::processImage(Mat& frame) {
	
	double bortop;
	double borleft;
	double bactop;
	double backleft;

	QPixmap scaled_img;
	Mat frameProcessed1;
	Mat frameProcessed2;

	if (isVidBorderShape) {

		if (isVidBorderThin) {
			bortop = 0.018;
			borleft = 0.012;
			bactop = 0.1;
			backleft = 0.08;
		}
		else {
			bortop = 0.075;
			borleft = 0.045;
			bactop = 0.1 / 2.5;
			backleft = 0.08 / 2.5;
		}

		int top = (int)(bortop * frame.rows);
		int bottom = (int)(bortop * 0.9 * frame.rows);
		int left = (int)(borleft * frame.cols);
		int right = left;
		copyMakeBorder(frame, frameProcessed1, top, bottom, left, right, BORDER_CONSTANT, *__value);

		top = (int)(bactop * frame.rows);
		bottom = top;
		left = (int)(backleft * frame.cols);
		right = left;
		copyMakeBorder(frameProcessed1, frameProcessed2, top, bottom, left, right, BORDER_CONSTANT, *backvalue);
		QImage img = Mat2QImage(frameProcessed2);
		QPixmap pixmap = QPixmap::fromImage(img);
		scaled_img = pixmap.scaled(camPrieview->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	}
	else {
		int thickness;
		if (isVidBorderThin) {
			bortop = 0.018;
			borleft = 0.012;
			bactop = 0.1;
			backleft = 0.08;
			thickness = 10;		
		}
		else {
			bortop = 0.018;
			borleft = 0.012;
			bactop = 0.1;
			backleft = 0.08;
			thickness = 18;
		}
		QImage scrimg = Mat2QImage(frame);
		QPixmap scrpixmap = QPixmap::fromImage(scrimg);
		scaled_img = scrpixmap.scaled(camPrieview->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		Mat scrframe = QImage2Mat(scaled_img.toImage());

		int top = (int)(bactop * scrframe.rows);
		int bottom = top;
		int left = (int)(backleft * scrframe.cols);
		int right = left;

		copyMakeBorder(scrframe, frameProcessed1, top, bottom, left, right, BORDER_CONSTANT, *backvalue);

		rounded_rectangle1(frameProcessed1, Point(left, top), Point(frameProcessed1.cols - left, frameProcessed1.rows - top), *__value, thickness, 1, 5);

		if (!isVidBorderThin) {
			rounded_rectangle1(frameProcessed1, Point(left - left/4.6, top - top/3.6), Point(frameProcessed1.cols - left + left/4.6, frameProcessed1.rows - top + top/3.6), *__value, thickness, 1, 5);
		}

		QImage img = Mat2QImage(frameProcessed1);
		QPixmap pixmap = QPixmap::fromImage(img);
		scaled_img = pixmap.scaled(camPrieview->size(),  Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	}
	return scaled_img;
}

void Video_Editor::mergeSimpleVideoFiles(QString resultFileName, QString recVideoFileName)
{
	QString recfilepath = QDir().currentPath() + "/sound_temp/" + QString("resultRec.wav");

	QString mergeCmd = QString("ffmpeg -i \"%1\"  -i \"%2\" -map 0 -map 1:a -c:v copy -y \"%3\"").arg(recVideoFileName).arg(recfilepath).arg(resultFileName);

	m_progressDlg->startProgress(mergeCmd);

}

void Video_Editor::UpSpin()
{
		if (video == NULL) return;
		pause();
		double total_duration = 0, start_time = 0, end_time = 0, start_offset = 0, end_offset = 0, fps = 0;
		total_duration = video->m_duration;
		start_time = video->m_startTime;
		start_offset = video->m_startOffset;
		end_offset = video->m_endOffset;
		fps = video->m_fps;
		end_time = video->m_endTime;

		start_offset += 1000/fps;

		qreal duration = start_time + start_offset ;
		if (duration > (total_duration - end_offset - 10))
		{
			stop();
			return;
		}
		video->m_startOffset = start_offset;
		trimbar->fitSeekPlayItems(duration / total_duration - end_offset);

		QString pro = QTime::fromMSecsSinceStartOfDay(duration).toString();
		QString rest = QTime::fromMSecsSinceStartOfDay(total_duration - end_offset).toString();
		time_label->setText("<font color='white'>" + QString("%1 / %2").arg(pro).arg(rest) + "</font>");
		current_video.set(CV_CAP_PROP_POS_MSEC, duration);

		current_video.read(vidframe);
		vidFramePixmap = processImage(vidframe);
		camPrieview->setVideoPixmap(vidFramePixmap);

}
void Video_Editor::DownSpin() 
{
	if (video == NULL) return;
	pause();

	double total_duration = 0, start_time = 0, end_time = 0, start_offset = 0, end_offset = 0, fps = 0;
	total_duration = video->m_duration;
	start_time = video->m_startTime;
	start_offset = video->m_startOffset;
	end_offset = video->m_endOffset;
	fps = video->m_fps;
	playerState = 0;
	start_offset -= 1000/fps;

	if (start_offset < 0) start_offset = 0;

	qreal duration = start_time + start_offset;

	trimbar->fitSeekPlayItems(duration / total_duration - end_offset);

	QString pro = QTime::fromMSecsSinceStartOfDay(duration).toString();
	QString rest = QTime::fromMSecsSinceStartOfDay(total_duration - end_offset).toString();
	time_label->setText("<font color='white'>" + QString("%1 / %2").arg(pro).arg(rest) + "</font>");

	current_video.read(vidframe);
	vidFramePixmap = processImage(vidframe);
	camPrieview->setVideoPixmap(vidFramePixmap);
	video->m_startOffset = start_offset;
}
void Video_Editor::refreshVideoItems()
{
	int pix = 65;
	video_listwidget->clear();
	for (int i = 0; i < videoItem_list.length(); i++)
	{
		if (videoItem_list[i]->m_IsVideo) {

			QFileInfo info(videoItem_list[i]->m_filePath);
			QString itemTitle = videoItem_list[i]->m_fileName + "." + info.suffix();
			bool isFade = videoItem_list[i]->m_IsFadeEffect;

			QPixmap scaled_img = videoItem_list[i]->m_titleImg.scaled(QSize(pix, pix), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			if (scaled_img.isNull())
				scaled_img = QPixmap(pix, pix);
			video_listwidget->addVideoItem(scaled_img, videoItem_list[i]->m_filePath, itemTitle, i, false);
		}
		else {
			int duration = videoItem_list[i]->m_duration;
			QFileInfo info(videoItem_list[i]->m_filePath);
			QString itemTitle = videoItem_list[i]->m_fileName + "." + info.suffix();
			QPixmap scaled_img = videoItem_list[i]->m_titleImg.scaled(QSize(pix, pix), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			if (scaled_img.isNull())
				scaled_img = QPixmap(pix, pix);
			
			video_listwidget->addVideoItem(scaled_img, videoItem_list[i]->m_filePath, itemTitle, i, false);
		}
	}
	video_listwidget->setCurrentRow(m_CurrentIndex);
}

void Video_Editor::deleteVideoItem()
{
	if (m_CurrentIndex < 0 || m_CurrentIndex > videoItem_list.length())
	{
		QMessageBox::warning(this, tr("Warning"), tr("Select Item to delete"));
		return;
	}
	if (m_isRecordState) {
		QMessageBox::warning(this, tr("Warning"), tr("Could not add and delete the files in Recording."));
		return;
	}
	videoItem_list.removeAt(m_CurrentIndex);
	refreshVideoItems();
	if (m_CurrentIndex - 1 >= 0)
		selectVideo(m_CurrentIndex - 1);
	else
		camPrieview->setVideoPixmap(empty_pixmap);
}

void Video_Editor::setEnabledLoadDeleteBtn(bool isEnable) {
	upload_btn->setEnabled(isEnable);
	delete_btn->setEnabled(isEnable);
}
void Video_Editor::openColorPickerDlg() {
	if (!m_isRecordState) {

		if (video == NULL) {
			QPixmap* pixmap = new QPixmap(":/Video_Editor/Resources/white.png");
			QImage img = pixmap->toImage();
			vidframe = QImage2Mat(img);
		}

		my_progress_dialog = new ColorPickerDlg(&vidframe, this);
		connect(my_progress_dialog, &ColorPickerDlg::updatePreviewSignal, this, &Video_Editor::updateAllPreview);

		my_progress_dialog->show();
	}
	else {
		QMessageBox::information(this, "Alert!", "You can't change the color of borders when record.");
	}

 }
void Video_Editor::updateAllPreview() {

	__value = my_progress_dialog->cppDlg->getVidFrameColor();

	if (video != NULL) {
		updateVideoPreview();
	}
}