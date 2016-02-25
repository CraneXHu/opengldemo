#ifndef APPFRAME_H
#define APPFRAME_H
#include "graphicsview.h"
#include <qmainwindow.h>

namespace magiccube{
class Drawer;
class AppFrame : public QMainWindow
{
	Q_OBJECT
public:
	AppFrame();
	~AppFrame();

	void init();

protected:
	void resizeEvent(QResizeEvent * event);

protected:
	GraphicsView *m_pGraphicsView;
	Drawer *m_pDrawer;
};
}
#endif //APPFRAME_H