#include <qapplication.h>
#include "appframe.h"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);
	magiccube::AppFrame frame;
	frame.showMaximized();
	app.exec();
	return 0;
}