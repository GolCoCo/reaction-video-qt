#include "ColorPickerDlg.h"

ColorPickerDlg::ColorPickerDlg(Mat* vidFrame, QWidget* parent) : QDialog(parent) {
	setWindowFlags(Qt::Dialog);
	setFixedSize(560, 55);
	setWindowIcon(QIcon(":/Video_Editor/Resources/icon.png"));
	setWindowTitle("Color Picker for Frames");
	mainDlg = parent;
	initUI();
	connectSignSlot();
	cppDlg = new ColorPickerPreviewDlg(vidFrame, this);
	isShowColorPickDlg = false;
}
ColorPickerDlg::~ColorPickerDlg() {

}

void ColorPickerDlg::hideEvent(QHideEvent* event) {
	cppDlg->hide();
	if (isShowColorPickDlg) {
		emit updatePreviewSignal();
	}
}

void ColorPickerDlg::initUI()
{

	QVBoxLayout* mainLayout = new QVBoxLayout();
	QWidget* pickerWidget = new QWidget();
	QHBoxLayout* pickerLayout = new QHBoxLayout();
	pickerWidget->setStyleSheet("QWidget{background-color:rgb(44,44,44);}");
	colorbtn1 = new ImageButton;
	colorbtn1->setFixedSize(60, 40);
	colorbtn1->setImages(":/Video_Editor/Resources/colorbtn1.png", ":/Video_Editor/Resources/colorbtn1_hover", ":/Video_Editor/Resources/colorbtn1_hover.png");
	colorbtn2 = new ImageButton;
	colorbtn2->setFixedSize(60, 40);
	colorbtn2->setImages(":/Video_Editor/Resources/colorbtn2.png", ":/Video_Editor/Resources/colorbtn2_hover", ":/Video_Editor/Resources/colorbtn2_hover.png");
	colorbtn3 = new ImageButton;
	colorbtn3->setFixedSize(60, 40);
	colorbtn3->setImages(":/Video_Editor/Resources/colorbtn3.png", ":/Video_Editor/Resources/colorbtn3_hover", ":/Video_Editor/Resources/colorbtn3_hover.png");
	colorbtn4 = new ImageButton;
	colorbtn4->setFixedSize(60, 40);
	colorbtn4->setImages(":/Video_Editor/Resources/colorbtn4.png", ":/Video_Editor/Resources/colorbtn4_hover", ":/Video_Editor/Resources/colorbtn4_hover.png");
	colorbtn5 = new ImageButton;
	colorbtn5->setFixedSize(60, 40);
	colorbtn5->setImages(":/Video_Editor/Resources/colorbtn5.png", ":/Video_Editor/Resources/colorbtn5_hover", ":/Video_Editor/Resources/colorbtn5_hover.png");
	colorbtn6 = new ImageButton;
	colorbtn6->setFixedSize(60, 40);
	colorbtn6->setImages(":/Video_Editor/Resources/colorbtn6.png", ":/Video_Editor/Resources/colorbtn6_hover", ":/Video_Editor/Resources/colorbtn6_hover.png");
	colorbtn7 = new ImageButton;
	colorbtn7->setFixedSize(60, 40);
	colorbtn7->setImages(":/Video_Editor/Resources/colorbtn7.png", ":/Video_Editor/Resources/colorbtn7_hover", ":/Video_Editor/Resources/colorbtn7_hover.png");
	
	pickerLayout->setContentsMargins(2, 2, 2, 2);
	pickerLayout->setSpacing(2);
	pickerLayout->addWidget(colorbtn1);
	pickerLayout->addWidget(colorbtn2);
	pickerLayout->addWidget(colorbtn3);
	pickerLayout->addWidget(colorbtn4);
	pickerLayout->addWidget(colorbtn5);
	pickerLayout->addWidget(colorbtn6);
	pickerLayout->addWidget(colorbtn7);
	pickerWidget->setLayout(pickerLayout);

	mainLayout->setContentsMargins(4, 4, 4, 4);
	mainLayout->addWidget(pickerWidget);
	setLayout(mainLayout);
}
void ColorPickerDlg::connectSignSlot() {
	connect(colorbtn1, SIGNAL(clicked(bool)), this, SLOT(colorBtn1Slot()));
	connect(colorbtn2, SIGNAL(clicked(bool)), this, SLOT(colorBtn2Slot()));
	connect(colorbtn3, SIGNAL(clicked(bool)), this, SLOT(colorBtn3Slot()));
	connect(colorbtn4, SIGNAL(clicked(bool)), this, SLOT(colorBtn4Slot()));
	connect(colorbtn5, SIGNAL(clicked(bool)), this, SLOT(colorBtn5Slot()));
	connect(colorbtn6, SIGNAL(clicked(bool)), this, SLOT(colorBtn6Slot()));
	connect(colorbtn7, SIGNAL(clicked(bool)), this, SLOT(colorBtn7Slot()));
}

void ColorPickerDlg::colorBtn1Slot() {
	if (cppDlg->isHidden()) {
		cppDlg->show();
	}
	isShowColorPickDlg = true;
	Scalar* red =  new Scalar(0, 0, 121);
	cppDlg->setVidFrameColors(red);
	cppDlg->updateFramePreview();
}
void ColorPickerDlg::colorBtn2Slot() {

	if (cppDlg->isHidden()) {
		cppDlg->show();
	}
	isShowColorPickDlg = true;
	Scalar* green = new Scalar(146, 49, 46);
	cppDlg->setVidFrameColors(green);
	cppDlg->updateFramePreview();
}
void ColorPickerDlg::colorBtn3Slot() {
	if (cppDlg->isHidden()) {
		cppDlg->show();
	}
	isShowColorPickDlg = true;
	Scalar* brown = new Scalar(64, 128, 255);

	cppDlg->setVidFrameColors(brown);
	cppDlg->updateFramePreview();
}
void ColorPickerDlg::colorBtn4Slot() {
	if (cppDlg->isHidden()) {
		cppDlg->show();
	}
	isShowColorPickDlg = true;
	Scalar* fuchsia = new Scalar(246, 207, 109);
	cppDlg->setVidFrameColors(fuchsia);
	cppDlg->updateFramePreview();
}
void ColorPickerDlg::colorBtn5Slot() {
	if (cppDlg->isHidden()) {
		cppDlg->show();
	}
	isShowColorPickDlg = true;
	Scalar* yellow = new Scalar(113, 52, 0);
	cppDlg->setVidFrameColors(yellow);
	cppDlg->updateFramePreview();

}
void ColorPickerDlg::colorBtn6Slot() {
	if (cppDlg->isHidden()) {
		cppDlg->show();
	}
	isShowColorPickDlg = true;
	Scalar* grey = new Scalar(35, 14, 230);
	cppDlg->setVidFrameColors(grey);
	cppDlg->updateFramePreview();
}
void ColorPickerDlg::colorBtn7Slot() {
	if (cppDlg->isHidden()) {
		cppDlg->show();
	}
	isShowColorPickDlg = true;
	Scalar* black = new Scalar(157, 152, 245);
	cppDlg->setVidFrameColors(black);
	cppDlg->updateFramePreview();
}