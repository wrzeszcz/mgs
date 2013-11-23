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

#include "GLWidget3D.h"
#include <GL/glu.h>
#include <QDebug>
//------------------------------------------------------------------------------
GLWidget3D::GLWidget3D(GeoModel *_model, Vset _widok, QWidget *parent):
    GLWidget(_model,_widok,parent)
{
    rotX=0.0;
    rotY=0.0;
    rotZ=0.0;
    mouse_pos = QPoint(0,0);
    zoom = 90.0;
    wczytajObiekty();
}
//------------------------------------------------------------------------------
GLWidget3D::~GLWidget3D()
{

}
//------------------------------------------------------------------------------
void GLWidget3D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int side = qMax(win_size.width(),win_size.height());
    int dal = qMax(sett->wym.x, sett->wym.y);

    glViewport( (win_size.width() - side) / 2,
                (win_size.height() - side) / 2, side, side );

    if(widok.perspektywa)
    {
        gluPerspective(zoom,1,5,dal*4);
    }
    else
    {
        glOrtho(-sett->wym.x,sett->wym.x,-sett->wym.y,sett->wym.y,5,500);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glTranslatef(0.0,0.0,-dal*1.5);
        //obroty
        glRotatef(rotX,1.0,0.0,0.0);
        glRotatef(rotY,0.0,1.0,0.0);
        glRotatef(rotZ,0.0,0.0,1.0);
        //rysowanie obiektów
        //rysowanie danych
        if (widok.dane) paint_dane();
        //rysowanie modelu
        if (widok.wezel || widok.siatka || widok.zasoby) paint_model();
        //rysowanie wybranego pkt
        glColor3f(0.0,1.0,0.0);
        glPointSize(10);
        paintPkt(curPoint-sett->wym/2);
        //rysowanie ramki
        if(widok.zakres)  paint_zakres();
        //rysowanie osi w innym view porcie
        paintAxis();
        paintScale();
    glFlush();
    glPopMatrix();
}
//------------------------------------------------------------------------------
void GLWidget3D::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x()-mouse_pos.x();
    int dy = event->y()-mouse_pos.y();
    if(event->buttons()&Qt::LeftButton)
    {
        rotX += 1*dy;
        rotY += 1*dx;
        updateGL();
    }
    else if (event->buttons()&Qt::RightButton)
    {
        rotX += 1*dy;
        rotZ += 1*dx;
        updateGL();
    }
    mouse_pos= event->pos();
}
//------------------------------------------------------------------------------
void GLWidget3D::wheelEvent(QWheelEvent *event)
{
    int d = event->delta()/120;
    zoom+=d;
    resizeGL(this->width(),this->height());
    updateGL();
}
//------------------------------------------------------------------------------
void GLWidget3D::point(wektor3d p)
{
    curPoint = p-sett->start;
    updateGL();
}
//------------------------------------------------------------------------------
void GLWidget3D::wczytajObiekty()
{
    if(!model )return;
    sett = model->ptr_mset();
    v_pkt3dane.clear();
    model->get_xyz_dane(v_pkt3dane,true);
}
//------------------------------------------------------------------------------
void GLWidget3D::paint_model()
{
    for(int a=0; a<cube->getSize().x;++a)
        for(int b=0; b<cube->getSize().y;++b)
            for(int c=0; c<cube->getSize().z;++c)
            {

                if(widok.wezel)
                {
                    glColor3f(1.0,0.0,0.0);
                    glPointSize(2.5);
                    paintPkt(cube2w(wektor3d(a,b,c),*sett));
                }
                if(widok.siatka)
                {
                    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                    glColor3f(0.5,0.5,0.5);
                    glLineWidth(0.5);
                    paintBlok(cube2w(wektor3d(a,b,c),*sett),sett->sp,-1.0);
                }
                if(widok.zasoby && c<=z)
                {
                    if (cube->getRek(a,b,c).x > sett->cutoff && test_otoczenia(a,b,c))
                    {
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        glPolygonOffset(-1.0,-1.0);
                        glColor3f(0.0f,0.5f,0.5f);
                        glEnable(GL_POLYGON_OFFSET_LINE);
                        paintBlok(cube2w(wektor3d(a,b,c),*sett),sett->sp,cube->getRek(a,b,c).x);
                        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                        glColor3f(0,0.5,0.5);
                        glLineWidth(1.0f);
                        paintBlok(cube2w(wektor3d(a,b,c),*sett),sett->sp,-1);
                        glDisable(GL_POLYGON_OFFSET_LINE);
                    }
                }
            }
}
//------------------------------------------------------------------------------
void GLWidget3D::paint_dane()
{
    glColor3f(1.0,1.0,1.0);
    glPointSize(2);
    paintPkt(v_pkt3dane);
}
//------------------------------------------------------------------------------
void GLWidget3D::paint_zakres()
{
    double x = sett->wym.x/2;
    double y = sett->wym.y/2;
    double z = sett->wym.z/2;

    glColor3f(1.0,1.0,1.0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(-x,-y,-z);
    glVertex3f(x,-y,-z);

    glVertex3f(-x,-y,-z);
    glVertex3f(-x,y,-z);

    glVertex3f(-x,y,-z);
    glVertex3f(x,y,-z);

    glVertex3f(x,-y,-z);
    glVertex3f(x,y,-z);

    glVertex3f(-x,y,-z);
    glVertex3f(-x,y,z);

    glVertex3f(x,-y,-z);
    glVertex3f(x,-y,z);

    glVertex3f(x,y,-z);
    glVertex3f(x,y,z);

    glVertex3f(x,y,z);
    glVertex3f(-x,y,z);

    glVertex3f(-x,y,z);
    glVertex3f(-x,-y,z);

    glVertex3f(-x,-y,z);
    glVertex3f(-x,-y,-z);

    glVertex3f(-x,-y,z);
    glVertex3f(x,-y,z);

    glVertex3f(x,-y,z);
    glVertex3f(x,y,z);

    glEnd();
}
//------------------------------------------------------------------------------
void GLWidget3D::paintPkt(wektor3d pkt)
{
    glBegin(GL_POINTS);
    glVertex3f(pkt.x,pkt.y,pkt.z);
    glEnd() ;
}
//------------------------------------------------------------------------------
void GLWidget3D::paintPkt(std::vector<wektor3d> &pkt3)
{
    v_it = pkt3.begin();
    glBegin(GL_POINTS);
        for(; v_it != pkt3.end(); ++v_it)
        {
            glVertex3f(v_it->x,v_it->y,v_it->z);
        }
    glEnd() ;
}
//------------------------------------------------------------------------------
void GLWidget3D::paintBlok(wektor3d srod, double bok, float color)
{
    if(color>=0)
    {
        QColor c = calcKolor(sett->cutoff*0.95, cube->get_max().x, color);
        glColor3f(c.redF(),c.greenF(),c.blueF());
    }
        wektor3d p = srod-wektor3d(bok/2,bok/2,bok/2);

        glBegin(GL_QUADS);

            glVertex3f (p.x, p.y, p.z);
            glVertex3f (p.x+bok, p.y, p.z);
            glVertex3f (p.x+bok, p.y+bok, p.z);
            glVertex3f (p.x, p.y+bok, p.z);

            glVertex3f (p.x, p.y, p.z+bok);
            glVertex3f (p.x+bok, p.y, p.z+bok);
            glVertex3f (p.x+bok, p.y+bok, p.z+bok);
            glVertex3f (p.x, p.y+bok, p.z+bok);

            glVertex3f (p.x, p.y, p.z);
            glVertex3f (p.x, p.y,  p.z+bok);
            glVertex3f (p.x+bok, p.y, p.z+bok);
            glVertex3f (p.x+bok, p.y,  p.z);

            glVertex3f (p.x, p.y+bok, p.z);
            glVertex3f (p.x, p.y+bok,  p.z+bok);
            glVertex3f (p.x+bok, p.y+bok, p.z+bok);
            glVertex3f (p.x+bok, p.y+bok, p.z );

            glVertex3f (p.x, p.y, p.z);
            glVertex3f (p.x, p.y+bok, p.z);
            glVertex3f (p.x, p.y+bok, p.z+bok);
            glVertex3f (p.x,  p.y, p.z+bok);

            glVertex3f (p.x+bok, p.y, p.z);
            glVertex3f (p.x+bok, p.y+bok,p.z);
            glVertex3f (p.x+bok, p.y+bok,p.z+bok);
            glVertex3f (p.x+bok, p.y, p.z+bok);

        glEnd();
}
//------------------------------------------------------------------------------
void GLWidget3D::paintAxis()
{
    glPushMatrix();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(10,10,70,70);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(rotX,1.0,0.0,0.0);
    glRotatef(rotY,0.0,1.0,0.0);
    glRotatef(rotZ,0.0,0.0,1.0);

    glBegin(GL_LINES);

    glColor3f(1.0,0.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(1.0,0.0,0.0);

    glColor3f(0.0,1.0,0.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1.0,0.0);

    glColor3f(0.0,0.0,1.0);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,0.0,1.0);

    glEnd() ;
    glPopMatrix();
}
//------------------------------------------------------------------------------
bool GLWidget3D::test_otoczenia(int a, int b, int c)
{
    if (a==0 || b==0 || c==0) return true;

    if (a==cube->size_x()-1 ||
        b==cube->size_y()-1 ||
        c==cube->size_z()-1 ||
        c==z   ) return true;

    if( cube->getRek(a-1,b,c).x > sett->cutoff &&
        cube->getRek(a+1,b,c).x > sett->cutoff &&
        cube->getRek(a,b-1,c).x > sett->cutoff &&
        cube->getRek(a,b+1,c).x > sett->cutoff &&
        cube->getRek(a,b,c-1).x > sett->cutoff &&
        cube->getRek(a,b,c+1).x > sett->cutoff    ) return false;
    else return true;
}
//-----------------------------------------------------------------------------
