/*******************************************************************************
**  Copyright (C) 2013  Marek Wrzeszcz
**  mail: marek.wrzeszcz@hotmail.com
**
**  This file is part of the MGEOSTAT.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "GLWidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    model(NULL)
{

}

GLWidget::GLWidget(GeoModel *_model, Vset _widok, QWidget *parent):
    QGLWidget(parent),
    model(_model),
    widok(_widok)
{
    update_model();
}

void GLWidget::update_model()
{
    cube = model->ptr_cube();
    dane = model->ptr_dane();
    sett = model->ptr_mset();
}

void GLWidget::set_rot(float x, float y, float z)
{
    rotX = x; rotY = y; rotZ = z;
    updateGL();
}

void GLWidget::initializeGL()
{
    glClearColor(0.0,0.0,0.0,0.0);  // kolor tła - bufor koloru
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
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
    Q_UNUSED(event);
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    Q_UNUSED(event);
}

void GLWidget::drawString(float x, float y, QColor rgb, int fontSize, QString text)
{
    glColor3f(rgb.redF(), rgb.greenF(), rgb.blueF());
    renderText(x,y,0, text, QFont("Helvetica [Cronyx]", fontSize, QFont::Bold));
}

QColor GLWidget::calcKolor(const double &minv, const double &maxv, const double &value)
{
    double k = (value - minv) / (maxv - minv);
    QColor c = kolor.get_kolor(k);
    return c;
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
