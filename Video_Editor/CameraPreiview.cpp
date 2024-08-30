#include "CameraPreiview.h"

CameraPreiview::CameraPreiview(QSize videoS, QWidget* parent)
	: QFrame(parent)
{

	m_width = videoS.width();
	m_height = videoS.height();

	this->setFixedSize(m_width, m_height);
	this->setStyleSheet("QFrame{background-color:rgba(0, 0, 0, 0);}");
    this->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    videoPreview = new QLabel(this);

    videoPreview->setFixedSize(m_width, m_height);
    videoPreview->setAcceptDrops(false);
    videoPreview->setToolTip("video");
    videoPreview->setStyleSheet("QLabel{background-color:rgba(0, 0, 0, 1);}");

    record = new QLabel(this);
    record->setFixedSize(120, 54);
    QPixmap recordImg = QPixmap(":/Video_Editor/Resources/media-record1.png").scaled(QSize(120, 54), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    record->setPixmap(recordImg);
    record->move(13, 13);
    record->setVisible(false);
	isDoubleClick = true;
}

void CameraPreiview::setVisibleRecordLabel(bool isvisible) {
    record->setVisible(isvisible);
}

void CameraPreiview::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (isDoubleClick) {
		QLabel* child = static_cast<QLabel*>(childAt(event->pos()));

		if (child->toolTip() == "video") {
			emit doulbleclicked();
		}
	}
}

CameraPreiview::~CameraPreiview()
{
}
void CameraPreiview::setVideoPixmap(QPixmap pixmap) {
    videoPreview->setPixmap(pixmap);
}

