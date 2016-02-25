#include "graphicsview.h"
#include "drawer.h"
#include "gloabledefine.h"
#include <qpainter.h>
#include <qevent.h>

MAGICCUBE_NAMESPACE_BEGIN
GraphicsView::GraphicsView(QWidget *parent):QGraphicsView(parent)
{
	setWindowTitle(tr("Magic Cube"));
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::resizeEvent(QResizeEvent *event)
{
	if (scene())
	{
		scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
	}
	QGraphicsView::resizeEvent(event);
}

MAGICCUBE_NAMESPACE_END