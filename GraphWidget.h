#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include "globalne.h"
#include <QMouseEvent>

class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = 0);

    void set_pkt_vario(std::vector<wektor3d> &pkt){pkt_vario = pkt;}
    void clear_pkt_vario(){pkt_vario.clear();}

    void set_function(Set_interpolacja set){function_set = set;}
    void draw_funkction(Set_interpolacja par);

protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

private:
    double skalax();
    double skalay();
    float x_scale(double X);
    float y_scale(double Y);

    void draw_ox();
    void draw_oy();
    W3d_comp_x por_x;
    W3d_comp_y por_y;

    QPoint mouse_poz;

    Set_interpolacja function_set;

    std::vector<wektor3d> pkt_vario;
    std::vector<QPointF> pkt_funkc;
};

#endif // GRAPHWIDGET_H
