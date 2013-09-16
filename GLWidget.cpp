#include "GLWidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    model = NULL;
}

GLWidget::GLWidget(GeoModel *_model, Vset _widok, QWidget *parent):
    model(_model),
    widok(_widok),
    QGLWidget(parent)
{
    update_model();
}

void GLWidget::update_model()
{
    cube = model->ptr_cube();
    dane = model->ptr_dane();
    sett = model->ptr_mset();
}

void GLWidget::initializeGL()
{
    glClearColor(0.0,0.0,0.0,0.0);  // kolor tła - bufor koloru
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    //--------------------------------------------------------------------------
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
//    glEnable(GL_POINT_SMOOTH);
//    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//    glEnable(GL_LINE_SMOOTH);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//    glEnable(GL_POLYGON_SMOOTH);
//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    //--------------------------------------------------------------------------
}

void GLWidget::resizeGL(int width, int height)
{
    win_size.setWidth(width);
    win_size.setHeight(height);
}

void GLWidget::paintGL()
{

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mouse_pos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

}

void GLWidget::wheelEvent(QWheelEvent *event)
{

}

void GLWidget::slot_set_widok(Vset w)
{
    widok = w;
    updateGL();
}

void GLWidget::slot_point(wektor3d p)
{
    curPoint=p;
    updateGL();
}

void GLWidget::wczytajObiekty()
{

}

void GLWidget::paint_model_siatka()
{

}

void GLWidget::paint_model_wezly()
{

}

void GLWidget::paint_model_zasoby()
{

}

void GLWidget::paint_model()
{

}

void GLWidget::paint_dane()
{

}

void GLWidget::paint_zakres()
{

}
