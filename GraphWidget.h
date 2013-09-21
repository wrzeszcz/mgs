#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include "globalne.h"
#include <QMouseEvent>
///
/// \brief The GraphWidget class
///
class GraphWidget : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GraphWidget
    /// \param parent
    ///
    explicit GraphWidget(QWidget *parent = 0);
    ///
    /// \brief set_pkt_vario
    /// \param pkt
    ///
    void set_pkt_vario(std::vector<wektor3d> &pkt){pkt_vario = pkt;}
    ///
    /// \brief clear_pkt_vario
    ///
    void clear_pkt_vario(){pkt_vario.clear();}
    ///
    /// \brief set_function
    /// \param set
    ///
    void set_function(Set_interpolacja set){function_set = set;}
    ///
    /// \brief draw_funkction
    /// \param par
    ///
    void draw_funkction(Set_interpolacja par);

protected:
    ///
    /// \brief paintEvent
    /// \param e
    ///
    void paintEvent(QPaintEvent *e);
    ///
    /// \brief mouseMoveEvent
    /// \param e
    ///
    void mouseMoveEvent(QMouseEvent *e);

private:
    ///
    /// \brief skalax
    /// \return
    ///
    double skalax();
    ///
    /// \brief skalay
    /// \return
    ///
    double skalay();
    ///
    /// \brief x_scale
    /// \param X
    /// \return
    ///
    float x_scale(double X);
    ///
    /// \brief y_scale
    /// \param Y
    /// \return
    ///
    float y_scale(double Y);
    ///
    /// \brief draw_ox
    ///
    void draw_ox();
    ///
    /// \brief draw_oy
    ///
    void draw_oy();
    ///
    /// \brief por_x
    ///
    W3d_comp_x por_x;
    ///
    /// \brief por_y
    ///
    W3d_comp_y por_y;
    ///
    /// \brief mouse_poz
    ///
    QPoint mouse_poz;
    ///
    /// \brief function_set
    ///
    Set_interpolacja function_set;
    ///
    /// \brief pkt_vario
    ///
    std::vector<wektor3d> pkt_vario;
    ///
    /// \brief pkt_funkc
    ///
    std::vector<QPointF> pkt_funkc;
};

#endif // GRAPHWIDGET_H
