#pragma once
#include <qdialog.h>
#include "qicon.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "imagebutton.h"
#include <qlabel.h>
#include "CameraPreiview.h"
#include <ColorPickerPreview.h>

class ColorPickerPreviewDlg : public QDialog
{
	Q_OBJECT
public:
	ColorPickerPreviewDlg(Mat* vidFrame, QWidget* parent = 0);
	~ColorPickerPreviewDlg();
	void setVidFrameColors(Scalar* value);
	Scalar* getVidFrameColor();
	void initUI();
	void updateFramePreview();
	QPixmap processImage(Mat& frame);
	void mousePressEvent(QMouseEvent* event);

private:
	ColorPickerPreview* frameLabel;
	QLabel* previewLabel;

	Mat* _vidframe;
	Mat* _camframe;
	Scalar* value;
	Scalar* camvalue;

public slots:
	//void show();

};
