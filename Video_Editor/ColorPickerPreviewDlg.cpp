#include "ColorPickerPreviewDlg.h"

ColorPickerPreviewDlg::ColorPickerPreviewDlg(Mat* vidFrame, QWidget* parent) :QDialog(parent) {
	setWindowFlags(Qt::Dialog| Qt::FramelessWindowHint);
	_vidframe = vidFrame;
	initUI();
}
ColorPickerPreviewDlg::~ColorPickerPreviewDlg() {

}
void ColorPickerPreviewDlg::setVidFrameColors(Scalar* value) {
	this->value = value;

}

Scalar* ColorPickerPreviewDlg::getVidFrameColor() {
	return this->value;
}

void ColorPickerPreviewDlg::initUI() {
	setFixedSize(600, 400);
	move(100, 50);
	setStyleSheet("QDialog{background-color:grey;}");
	previewLabel = new QLabel();
	previewLabel->setToolTip("preview");
	previewLabel->setStyleSheet("QLabel{background-color:white;}");
	QHBoxLayout* previewLayout = new QHBoxLayout();
	previewLayout->setContentsMargins(2, 2, 2, 2);
	previewLayout->addWidget(previewLabel);
	setLayout(previewLayout);
}
void ColorPickerPreviewDlg::updateFramePreview() {

	QPixmap back = processImage(*_vidframe);
	previewLabel->setPixmap(back);
}

QPixmap ColorPickerPreviewDlg::processImage(Mat& frame) {

	double bortop;
	double borleft;
	double bactop;
	double backleft;

	QPixmap scaled_img;
	Mat frameProcessed1;
	Mat frameProcessed2;
	bortop = 0.03;
	borleft = 0.022;
	bactop = 0.1;
	backleft = 0.08;

	int top = (int)(bortop * frame.rows);
	int bottom = (int)(bortop * 0.9 * frame.rows);
	int left = (int)(borleft * frame.cols);
	int right = left;
	copyMakeBorder(frame, frameProcessed1, top, bottom, left, right, BORDER_CONSTANT, *value);

	top = (int)(bactop * frame.rows);
	bottom = top;
	left = (int)(backleft * frame.cols);
	right = left;
	Scalar* backvalue = new Scalar(255, 255, 255);
	copyMakeBorder(frameProcessed1, frameProcessed2, top, bottom, left, right, BORDER_CONSTANT, *backvalue);
	QImage img = Mat2QImage(frameProcessed2);
	QPixmap pixmap = QPixmap::fromImage(img);
	scaled_img = pixmap.scaled(QSize(600, 400), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
	return scaled_img;
}

void ColorPickerPreviewDlg::mousePressEvent(QMouseEvent* event)
{
	int posx = event->pos().x();
	int posy = event->pos().y();
	QLabel* child = static_cast<QLabel*>(childAt(event->pos()));
	if (child->toolTip() == "preview") {
		QColor color = QColorDialog::getColor(Qt::red, this, "Pick a color of video's border.", QColorDialog::DontUseNativeDialog);
		int R, G, B;
		color.getRgb(&R, &G, &B);
		value = new Scalar(B, G, R);
		updateFramePreview();
	}
	else {
		return;
	}	
}