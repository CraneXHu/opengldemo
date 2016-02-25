#include "drawer.h"
#include "gloableenum.h"
#include <glext.h>
#include <glut.h>
#include <qevent.h>
#include <math.h>

MAGICCUBE_NAMESPACE_BEGIN
GLfloat ambient_light[] = {0.5,0.5,0.5,1.0};
GLfloat diffuse_light[] = {0.5,0.5,0.5,1.0};
GLfloat specular_light[] = {0.5,0.5,0.5,1.0};
GLfloat light_position[] = {-20.0,50.0,100.0,0};
GLfloat fog_color[] = {0.5,0.5,0.5,1.0};

typedef int gint;
typedef float gfloat;
gfloat glVertexArray[8][3] = {{-1.0,-1.0,1.0},{-1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,-1.0,1.0},{-1.0,-1.0,-1.0},{-1.0,1.0,-1.0},{1.0,1.0,-1.0},{1.0,-1.0,-1.0}};
gint   glVertexIndex[6][4] = {{4,5,6,7},{1,2,6,5},{0,1,5,4},{0,3,2,1},{0,4,7,3},{2,3,7,6}};
gfloat glNormal[6][3] = {{0,0,-1},{0,1,0},{-1,0,0},{0,0,1},{0,-1,0},{1,0,0}};
gfloat glcolor[6][3] = {1,0,0,0,1,0,0,0,1,1,1,0,1,0,1,0,1,1};

Drawer::Drawer(QWidget *parent):QGLWidget(parent)
{
	m_fScale = 1.0f;
	m_fTranslation.x = 0;
	m_fTranslation.y = 0;
	m_fRotationAngle.x = 0;
	m_fRotationAngle.y = 0;
	for(int i = 0; i < 16; i++)
	{
		if (i%5 == 0)
		{
			m_dModelViewMatrix[i] = 1;
			m_dProjectionMatrix[i] = 1;
		}
		else
		{
			m_dModelViewMatrix[i] = 0;
			m_dProjectionMatrix[i] = 0;
		}
	}
}

Drawer::~Drawer()
{

}

void Drawer::initializeGL()
{
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambient_light);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse_light);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular_light);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void Drawer::resizeGL(int width,int height)
{
	resize(width,height);
	glViewport(0,0,width,height);
}

void Drawer::paintGL()
{
	glClearColor(0.5,0.5,0.5,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	drawCube();
}

void Drawer::drawCube()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3*width()/height()-m_fTranslation.x, 3*width()/height()-m_fTranslation.x, -3+m_fTranslation.y, 3+m_fTranslation.y, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(m_fScale,m_fScale,m_fScale);
	glRotated(m_fRotationAngle.y,1.0,0.0,0.0);
	glRotated(m_fRotationAngle.x,0.0,1.0,0.0);
	glMultMatrixd(m_dModelViewMatrix);
	glGetDoublev(GL_MODELVIEW_MATRIX,m_dModelViewMatrix);
	//	glGetDoublev(GL_PROJECTION_MATRIX,m_dProjectionMatrix);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	//	glColor3f(0.8,0.7,0);

	glBegin(GL_QUADS);
	for (int i = 0; i < 6; i++)
	{
		glNormal3fv(glNormal[i]);
		glColor3f(1.0,0.0,0.0);
		glVertex3fv(glVertexArray[glVertexIndex[i][0]]);
		glNormal3fv(glNormal[i]);
		glColor3f(0.0,1.0,0.0);
		glVertex3fv(glVertexArray[glVertexIndex[i][1]]);
		glNormal3fv(glNormal[i]);
		glColor3f(0.0,0.0,1.0);
		glVertex3fv(glVertexArray[glVertexIndex[i][2]]);
		glNormal3fv(glNormal[i]);
		glColor3f(1.0,1.0,1.0);
		glVertex3fv(glVertexArray[glVertexIndex[i][3]]);
	}
	glEnd();
	glFlush();
}

void Drawer::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_iMouseKeyFlag = LeftMouseButton;
	}
	if (event->button() == Qt::RightButton)
	{
		m_iMouseKeyFlag = RightMouseButton;
	}
	m_iFirstPos = event->pos();
	m_iLastPos = event->pos();
}

void Drawer::mouseMoveEvent(QMouseEvent *event)
{
	if (m_iMouseKeyFlag == LeftMouseButton )
	{
		m_iFirstPos = m_iLastPos;
		m_iLastPos = event->pos();
		m_fRotationAngle.x = 180*(m_iLastPos.x()-m_iFirstPos.x())/PI/RFactor;
		m_fRotationAngle.y = 180*(m_iLastPos.y()-m_iFirstPos.y())/PI/RFactor;
	}
	if (m_iMouseKeyFlag == RightMouseButton)
	{
		m_iFirstPos = m_iLastPos;
		m_iLastPos = event->pos();
		m_fTranslation.x += (m_iLastPos.x()-m_iFirstPos.x())/TFactor;
		m_fTranslation.y += (m_iLastPos.y()-m_iFirstPos.y())/TFactor;
	}
	updateGL();
}

void Drawer::mouseReleaseEvent(QMouseEvent *event)
{
	m_fRotationAngle.x = 0;
	m_fRotationAngle.y = 0;
}

void Drawer::wheelEvent(QWheelEvent *event)
{
	double numDegrees = -event->delta()/8.0;
	double numSteps = numDegrees / 1500.0;
	m_fScale -= numSteps;
	updateGL();
}

MAGICCUBE_NAMESPACE_END
