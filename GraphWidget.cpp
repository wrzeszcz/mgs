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

#include "GraphWidget.h"
#include <QPainter>
#include <QPainterPath>
#include "GeoVariogramModel.h"
//------------------------------------------------------------------------------
GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent),   
    vMargins(QPoint(60,20)),
    hMargins(QPoint(40,40))
{
    function_set = Set_interpolacja();
}
//------------------------------------------------------------------------------
void GraphWidget::draw_funkction(Set_interpolacja par)
{
    GeoVariogramModel funk(par.vario,
                           par.nuget_c0,
                           par.sill_c1,
                           par.range_a);

    pkt_funkc.clear();

    for(int i=0; i<(this->width()-60);++i)
    {
        double h = i / skalax();
        double v = funk.licz_vario(h);
        pkt_funkc.push_back(QPointF(h,v));
    }
}
//------------------------------------------------------------------------------
void GraphWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::white);
    p.setPen(pen);

    p.drawRect(hMargins.x(),vMargins.y(),this->width()-60,this->height()-60);
    p.drawText(this->width()/2,this->height()-5, "h");
    p.drawText(5,15, "γ(h)");
    if (!pkt_vario.size())return;

    draw_funkction(function_set);

    QPointF pk= pkt_funkc[0];
    QPointF pkt1(x_scale(pk.x()),y_scale(pk.y()));

    pen.setWidth(2);
    pen.setColor(Qt::magenta);
    pen.setJoinStyle(Qt::RoundJoin);
    p.setPen(pen);

    for(unsigned i=0;i<pkt_funkc.size();++i)
    {
       pk = pkt_funkc[i];
       QPointF pkt2(x_scale(pk.x()),y_scale(pk.y()));
       p.drawLine(pkt1,pkt2);
       pkt1=pkt2;
    }

    pen.setWidth(2);
    pen.setColor(Qt::yellow);
    p.setPen(pen);

    for(unsigned i=0; i<pkt_vario.size();++i)
    {
        wektor3d w = pkt_vario[i];
        QPoint pkt(x_scale(w.x),y_scale(w.y));
        p.drawEllipse(pkt,3,3);
    }

    draw_ox();
    draw_oy();
    p.end();
}
//------------------------------------------------------------------------------
void GraphWidget::mouseMoveEvent(QMouseEvent *e)
{
    mouse_poz = e->pos();
}
//------------------------------------------------------------------------------
void GraphWidget::draw_ox()
{
    QPainter p(this);
    p.setPen(Qt::red);
    int hor = this->width()-60;
    for(int i=0; i<hor; i+=30)
    {
        int a = i+40;
        QPoint pkt(a,this->height()-25);
        p.drawText(pkt,QString::number(int(i/skalax())));

    }

}
//------------------------------------------------------------------------------
void GraphWidget::draw_oy()
{
    int wer = this->height()-60;
    QPainter p(this);
    p.setPen(Qt::red);
    for(int i=0; i<wer; i+=30)
    {
        int a = wer+20-i;
        QPoint pkt(2,a);
        p.drawText(pkt,QString::number((i/skalay()),'f',3));
    }
}
//------------------------------------------------------------------------------
double GraphWidget::skalax()
{
    int hor = this->width()-60;
    double max;
    if(pkt_vario.size())
    {
        max = (std::max_element(pkt_vario.begin(),pkt_vario.end(),por_x))->x;
    }
    else return 1;
    return hor/max;
}
//------------------------------------------------------------------------------
double GraphWidget::skalay()
{
    int wer = this->height()-60;
    double max;
    if(pkt_vario.size())
    {
        max = (std::max_element(pkt_vario.begin(),pkt_vario.end(),por_y))->y;
    }
    else return 1;
    return wer/max;
}
//------------------------------------------------------------------------------
float GraphWidget::x_scale(double X)
{
    return float(X*skalax()+40);
}
//------------------------------------------------------------------------------
float GraphWidget::y_scale(double Y)
{
    int wer = this->height();
    return float( wer-Y*skalay()-40);
}
//------------------------------------------------------------------------------
