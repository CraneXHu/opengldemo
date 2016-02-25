#include "appframe.h"
#include "gloabledefine.h"
#include "drawer.h"
#include <qmainwindow.h>
#include <qgraphicsview.h>

MAGICCUBE_NAMESPACE_BEGIN
AppFrame::AppFrame()
{
	m_pDrawer = new Drawer(this);
}

AppFrame::~AppFrame()
{
	delete m_pDrawer;
}

void AppFrame::init()
{
	setCentralWidget(m_pDrawer);
}

void AppFrame::resizeEvent(QResizeEvent * event)
{
	m_pDrawer->resizeGL(width(),height());
}
MAGICCUBE_NAMESPACE_END
