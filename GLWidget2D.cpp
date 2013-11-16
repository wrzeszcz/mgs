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

#include "GLWidget2D.h"
#include <QPainter>
#include <QDebug>
#include <cmath>
//------------------------------------------------------------------------------
GLWidget2D::GLWidget2D(GeoModel *_model, Vset _widok, QWidget *parent):
    GLWidget(_model,_widok,parent), Z(0)
{
    scale = 0.8;
    dx = dy = 0.0;
    mouse_pos = QPoint(0,0);
    model_size = QSize(sett->wym.x+sett->sp,sett->wym.y+sett->sp);
    setAutoFillBackground(false);

    setMouseTracking(true);
}
//------------------------------------------------------------------------------
GLWidget2D::~GLWidget2D()
{

}
//------------------------------------------------------------------------------
void GLWidget2D::paintGL()
{
    //glEnable(GL_BLEND);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int max_size = qMax(win_size.width(),win_size.height());
    int x = (win_size.width()-max_size)/2;
    int y = (win_size.height()-max_size)/2;
    glViewport(x, y,  max_size, max_size);
    glOrtho (   -model_size.width() /2, model_size.width()   /2,
                      -model_size.height()/2, model_size.height() /2,-1,1);

    //-------------------------------------------------------------------------

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

        //glTranslatef(0.375,0.375,0);

        glTranslatef(dx/5.0, dy/5.0, 1.0);
        glScalef(scale,scale,1);

        glColor3f(0.0,1.0,0.0);
        paintPkt(curPoint-sett->wym/2,5);

        //drawString(0,0, Qt::red, 20, QString::number(mouse_pos.x()));

        glLineWidth(2);
        if(widok.zakres)
        {
            paint_zakres();
        }

        if(widok.wezel || widok.siatka || widok.zasoby || widok.tlo)
        {
            paint_model();
        }

        paintScale();

        RenderString(0,0,80,50, Qt::red, QString::number(Z));


    glFlush();
    glPopMatrix();



}
//------------------------------------------------------------------------------
void GLWidget2D::mouseMoveEvent(QMouseEvent *event)
{
    int dex = event->x() - mouse_pos.x();
    int dey = event->y() - mouse_pos.y();
    if(event->buttons() & Qt::LeftButton)
    {
        dx += dex;
        dy -= dey;
    }
    else if (event->buttons() & Qt::RightButton)
    {

    }
    mouse_pos = event->pos();
    updateGL();
}
//------------------------------------------------------------------------------
void GLWidget2D::wheelEvent(QWheelEvent *event)
{
    float delta = event->delta()/3600.0;
    scale += delta;
    updateGL();
}
//------------------------------------------------------------------------------
void GLWidget2D::slot_point(wektor3d p)
{
    curPoint = p-sett->start;
    updateGL();
}
//------------------------------------------------------------------------------
void GLWidget2D::wczytajObiekty()
{

}
//------------------------------------------------------------------------------
void GLWidget2D::paint_model()
{
    for(int a=0; a<cube->getSize().x;++a)
        for(int b=0; b<cube->getSize().y;++b)
            {
                if(widok.wezel)
                {
                    glColor3f(1,0,0);
                    paintPkt(cube2w(wektor3d(a,b,0),*sett),3);
                }
                if(widok.zasoby)
                {
                    if (cube->getRek(a,b,Z).x > sett->cutoff)
                    {
                        glColor3f(0.1,0.1,0.1);
                        paintBlok(cube2w(wektor3d(a,b,0),*sett),sett->sp);
                    }
                }
                if(widok.siatka)
                {
                    glColor3f(0.5,0.5,0.5);
                    paintBlok(cube2w(wektor3d(a,b,0),*sett),sett->sp);
                }

                if(widok.tlo)
                {
                    if(!widok.error_map)
                     paintBlok(cube2w(wektor3d(a,b,0),*sett),sett->sp,cube->getRek(a,b,Z).x);
                    else
                     paintBlok(cube2w(wektor3d(a,b,0),*sett),sett->sp,cube->getRek(a,b,Z).y);
                }
                //tymczasowo wyłączone
                if(0 && a < cube->size_x()-1 && b < cube->size_y()-1)
                {
                paintQuad ( geo3d(cube2w(wektor3d(a,b,Z),*sett), cube->getRek(a,b,Z)),
                            geo3d(cube2w(wektor3d(a+1,b,Z),*sett), cube->getRek(a+1,b,Z)),
                            geo3d(cube2w(wektor3d(a+1,b+1,Z),*sett), cube->getRek(a+1,b+1,Z)),
                            geo3d(cube2w(wektor3d(a,b+1,Z),*sett), cube->getRek(a,b+1,Z))
                            );
                }
            }
}
//------------------------------------------------------------------------------
void GLWidget2D::paint_dane()
{

}
//------------------------------------------------------------------------------
void GLWidget2D::paint_zakres()
{
    double x = sett->wym.x/2;
    double y = sett->wym.y/2;
    glColor3f(1.0,1.0,1.0);
    glLineWidth(2);
    glBegin(GL_LINES);
        glVertex2f(-x,-y);
        glVertex2f(x,-y);

        glVertex2f(x,-y);
        glVertex2f(x,y);

        glVertex2f(x,y);
        glVertex2f(-x,y);

        glVertex2f(-x,y);
        glVertex2f(-x,-y);
        glEnd();
}
//------------------------------------------------------------------------------
void GLWidget2D::paint_mapa()
{

}
//------------------------------------------------------------------------------
void GLWidget2D::RenderString(int x,int y,int w,int h,QColor rgb,QString text)
{
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    glViewport(x,y,w,h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(rgb.redF(), rgb.greenF(), rgb.blueF());
    renderText(0,0,0, text, QFont("Helvetica [Cronyx]", 16, QFont::Bold));

    glPopMatrix();
}
//------------------------------------------------------------------------------
void GLWidget2D::paintPkt(wektor3d pkt, float roz)
{
    glPointSize(roz);
    glBegin(GL_POINTS);
        glVertex2f(pkt.x,pkt.y);
    glEnd();
}
//------------------------------------------------------------------------------
void GLWidget2D::paintBlok(wektor3d srod, double bok, float color)
{
    wektor3d min = cube->get_min();
    wektor3d max = cube->get_max();
    QColor c;
    if(min.x!=-NULLDAT && color != NULLDAT)
    {
        if(!widok.error_map)
        {
            c = calcKolor(min.x, max.x, color);
        }
        else
        {
            c = calcKolor(min.y, max.y, color);
        }
    }
    wektor3d p = srod-wektor3d(bok/2,bok/2,bok/2);
    glColor3f(c.redF(),c.greenF(),c.blueF());
    glBegin(GL_QUADS);
        glVertex2f (p.x,p.y);
        glVertex2f (p.x+bok,p.y);
        glVertex2f (p.x+bok,p.y+bok);
        glVertex2f (p.x,p.y+bok);
    glEnd();
}
//------------------------------------------------------------------------------
void GLWidget2D::paintBlok(wektor3d srod, double bok)
{
    wektor3d p = srod-wektor3d(bok/2,bok/2,bok/2);
    glLineWidth(1.0);
    glBegin(GL_LINES);
        glVertex2f (p.x,p.y);
        glVertex2f (p.x+bok,p.y);

        glVertex2f (p.x+bok,p.y);
        glVertex2f (p.x+bok,p.y+bok);

        glVertex2f (p.x+bok,p.y+bok);
        glVertex2f (p.x,p.y+bok);

        glVertex2f (p.x,p.y+bok);
        glVertex2f (p.x,p.y);
     glEnd();
}
//------------------------------------------------------------------------------
void GLWidget2D::paintQuad(geo3d a, geo3d b, geo3d c, geo3d d)
{

    double min = cube->get_min().x;
    double max = cube->get_max().x;
    if(max == NULLDAT || min == -NULLDAT) return;
    QColor k;

    glBegin(GL_QUADS);
        k = calcKolor(min, max, a.dat.x);
        glColor3f(k.redF(),k.greenF(),k.blueF());
        glVertex2f (a.xyz.x, a.xyz.y);
        k = calcKolor(min, max, b.dat.x);
        glColor3f(k.redF(),k.greenF(),k.blueF());
        glVertex2f (b.xyz.x, b.xyz.y);
        k = calcKolor(min, max, c.dat.x);
        glColor3f(k.redF(),k.greenF(),k.blueF());
        glVertex2f (c.xyz.x, c.xyz.y);
        k = calcKolor(min, max, d.dat.x);
        glColor3f(k.redF(),k.greenF(),k.blueF());
        glVertex2f (d.xyz.x, d.xyz.y);
    glEnd();

}
//------------------------------------------------------------------------------
void GLWidget2D::paintScale()
{
    double x = sett->wym.x/2 + 20;
    double y = sett->wym.y;//2;
    //float v ;
    int i;
    float f1,f2;

    float f = 1.0/8.0;
    //wektor3d maks = cube->get_max();
    //wektor3d mini = cube->get_min();

    for(i=0; i<8; ++i)
    {
        f1=f*i;
        f2=f*(i+1);
        QColor c1= kolor.get_kolor(f1);
        QColor c2= kolor.get_kolor(f2);
        f1*=y;f1-=y/2;
        f2*=y;f2-=y/2;
        //v = f1*(maks.x - mini.x)+ mini.x;
        //if(maks.x!= NULLDAT)
            //drawString(-x+7,f1,Qt::white,10, QString::number(v,'f',2));
        glBegin(GL_QUADS);
            glColor3f(c1.redF(),c1.greenF(),c1.blueF());
            glVertex2f(-x,f1);
            glVertex2f(-x+5,f1);
            glColor3f(c2.redF(),c2.greenF(),c2.blueF());
            glVertex2f(-x+5,f2);
            glVertex2f(-x,f2);
        glEnd() ;
    }

}
//------------------------------------------------------------------------------

