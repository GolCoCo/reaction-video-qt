#include "video_editor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Video_Editor w;
	w.setWindowModality(Qt::NonModal);
	w.setWindowIcon(QIcon(":/Video_Editor/Resources/icon.png"));
	w.setMaximumSize(900, 920);
    w.setMaximumSize(900, 920);
	w.move(200, 100);
	w.setWindowTitle("Reaction VideoTool 2.0");
	w.show();
	a.setStyle("fusion");
	return a.exec();
}
