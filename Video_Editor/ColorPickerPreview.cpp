#include "ColorPickerPreview.h"
ColorPickerPreview::ColorPickerPreview(QWidget* parent)
	: QWidget(parent) {

	InitUI();
}

ColorPickerPreview::~ColorPickerPreview() {

}
void ColorPickerPreview::InitUI() {
	previewLabel = new QLabel();
	previewLabel->setStyleSheet("QLabel{background-color:black;}");
	QHBoxLayout* previewLayout = new QHBoxLayout();
	previewLayout->setContentsMargins(2, 2, 2, 2);
	previewLayout->addWidget(previewLabel);
	setLayout(previewLayout);
}
void ColorPickerPreview::updatePreview(QPixmap imagePx) {
	previewLabel->setPixmap(imagePx);
}