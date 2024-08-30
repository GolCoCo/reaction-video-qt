#pragma once
#include <qdialog.h>
#include "qicon.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "imagebutton.h"
#include <qlabel.h>
#include "CameraPreiview.h"
#include "ColorPickerPreviewDlg.h"
#include "Global.h"
#include "common.h"

class ColorPickerDlg :	public QDialog
{
	Q_OBJECT
public:
	ColorPickerDlg(Mat* vidFrame, QWidget* parent = 0);

	~ColorPickerDlg();
	void hideEvent(QHideEvent* event);
	void initUI();
	void connectSignSlot();

private:
	ImageButton* colorbtn1;
	ImageButton* colorbtn2;
	ImageButton* colorbtn3;
	ImageButton* colorbtn4;
	ImageButton* colorbtn5;
	ImageButton* colorbtn6;
	ImageButton* colorbtn7;
	QPushButton* okbtn;
	QPushButton* cancelbtn;
	CameraPreiview* frameLabel;
	QWidget* mainDlg;
	bool isShowColorPickDlg;

public:

	Mat* _camframe;
	Mat* _vidframe;
	ColorPickerPreviewDlg* cppDlg;
	double camB;
	double camG;
	double camR;

public slots:

	void colorBtn1Slot();
	void colorBtn2Slot();
	void colorBtn3Slot();
	void colorBtn4Slot();
	void colorBtn5Slot();
	void colorBtn6Slot();
	void colorBtn7Slot();
signals:
	void updatePreviewSignal();
};
