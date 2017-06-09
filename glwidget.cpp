//#include <GL/glew.h>
#include "glwidget.h"
#include "math.h"
#include <QMouseEvent>
#include <QTimer>



GLWidget::GLWidget(QWidget *parent):
    QGLWidget(parent)
{
    this->R = 1;
    this->RotX = 0;
    this->RotY = 0;
    this->W = 0;
    this->H = 0;
    this->D = 0;
    this->NumbTriang = 0;
}

void GLWidget::initializeGL()
{
    glClearColor(0.8, 0.8, 0.8, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTranslatef(this->width()/2, this->height()/2, -500 );
    glRotatef(RotX, 1, 0, 0);
    glRotatef(RotY, 0, 1, 0);
    glTranslatef( -this->width()/2, -this->height()/2, 500 );

    drawParall(this->width()/2,this->height()/2,-500, W, H, D);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, 0, 1000);

    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    RotX = 0;
    RotY = 0;
    R += ((double)(event->angleDelta()).y())/2000;
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    pressPos = event->pos();
}

void GLWidget::setProportions(int w, int h, int d)
{
    this->W = w;
    this->H = h;
    this->D = d;
}

int GLWidget::getNumbTriangles()
{
    return this->NumbTriang;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    RotX = ((int)(event->y()-pressPos.y()))/5;
    RotY = ((int)(event->x()-pressPos.x()))/5;
    pressPos = event->pos();
    updateGL();
}

void GLWidget::drawParall(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat Width, GLfloat Height, GLfloat Depth)
{
      GLfloat halfWidth = Width * R * 0.5;
      GLfloat halfHeight= Height * R * 0.5;
      GLfloat halfDepth = Depth * R * 0.5;
      glColor3f(0,0,1);

      GLfloat vertices[] =
       {
           // front face
           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top right
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth, // bottom right

           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth, // bottom right
           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth, // bottom left

           // back face
           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // top left
           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // top right
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right

           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // top left
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right
           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom left

           // left face
           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // top right
           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right

           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right
           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth, // bottom left

           // right face
           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // top right
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right

           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth, // bottom left

           // top face
           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // top right
           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // bottom right

           centerPosX - halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // top left
           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ - halfDepth, // bottom right
           centerPosX + halfWidth, centerPosY + halfHeight, centerPosZ + halfDepth, // bottom left

           // bottom face
           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth, // top left
           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // top right
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right

           centerPosX - halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth, // top left
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ - halfDepth, // bottom right
           centerPosX + halfWidth, centerPosY - halfHeight, centerPosZ + halfDepth  // bottom left
       };

       this->NumbTriang=12;
       glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
       glEnableClientState( GL_VERTEX_ARRAY );
       glVertexPointer( 3, GL_FLOAT, 0, vertices );

       glDrawArrays( GL_TRIANGLES, 0, 36 );

       glDisableClientState( GL_VERTEX_ARRAY );
}
