#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <qgraphicsview.h>

namespace magiccube{
class Drawer;
class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	GraphicsView(QWidget *parent = 0);
	~GraphicsView();

protected:
	void resizeEvent(QResizeEvent *event);

protected:
	Drawer *m_pDrawer;
};
}
#endif //GRAPHICSVIEW