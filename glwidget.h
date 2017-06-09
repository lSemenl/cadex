#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>


class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void setProportions(int w, int h, int d);
    int getNumbTriangles();


private:
    double R;
    int RotX;
    int RotY;
    int W,H,D;
    int NumbTriang;
    QPoint pressPos;

    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void drawParall(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat Width, GLfloat Height, GLfloat Depth);
};

#endif // GLWIDGET_H
