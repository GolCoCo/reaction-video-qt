#pragma once
#include <QLabel>
#include <QtWidgets>
#include <QFrame>
#include <QtWidgets/QMainWindow>
#include <QMultiMedia>
#include "Global.h"
#include <common.h>
#include <qwidget.h>
class ColorPickerPreview :	public QWidget
{
	Q_OBJECT

public:
	explicit ColorPickerPreview(QWidget* parent = 0);

	~ColorPickerPreview();
	void InitUI();
	void updatePreview(QPixmap imageMat);
public:
	QLabel* previewLabel;

};

