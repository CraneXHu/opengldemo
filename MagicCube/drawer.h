#ifndef DRAWER_H
#define DRAWER_H
#include <qgl.h>

struct Direction
{
	float x;
	float y;
};

namespace magiccube{
class Drawer : public QGLWidget
{
	Q_OBJECT
	friend class AppFrame;
public:
	Drawer(QWidget *parent = 0);
	~Drawer();

	void drawCube();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width,int height);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

protected:
	QPoint m_iFirstPos;
	QPoint m_iLastPos;
	int m_iMouseKeyFlag;
	GLfloat m_fScale;
	GLdouble m_dModelViewMatrix[16];
	GLdouble m_dProjectionMatrix[16];	
	Direction m_fTranslation;
	Direction m_fRotationAngle;
};
}
#endif //DRAWER_H