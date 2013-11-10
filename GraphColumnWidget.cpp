#include "GraphColumnWidget.h"
#include <QPainter>
#include "Gradient.h"

GraphColumnWidget::GraphColumnWidget(QWidget *parent):
    QWidget(parent),
    max_masa(0),
    border(QSize(10,10))
{

}

void GraphColumnWidget::set_data(std::vector<geo3d> &data)
{
    dane = data;
    max_masa = 0.0;
    for(unsigned int i=0; i<dane.size(); ++i)
    {
        if(dane[i].dat.y > max_masa) max_masa=dane[i].dat.y;
    }
}

void GraphColumnWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);


    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing,true);
    QPen pen;

    pen.setWidth(1);
    pen.setColor(Qt::white);
    p.setPen(pen);

    int kl =  dane.size();

    Gradient gr;

    for(int i = 0; i < kl; ++i)
    {
        double f = dane[i].dat.y/max_masa;
        QColor c = gr.get_kolor(f);
        int h = f * area.height();
        int x = (area.width() / kl) ;
        int y = height()-border.height()/2 -h;
        QRect r1(x*i+ border.width()/2, y, x, h);
        p.drawRect(r1);
        p.fillRect(r1,QBrush(c));
    }

    p.end();
}

void GraphColumnWidget::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    area = QSize(this->width()-border.width(),this->height()-border.height());
}
