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
    ///
    /// \brief vMargins
    ///
    QPoint vMargins;
    ///
    /// \brief hMargins
    ///
    QPoint hMargins;
};

#endif // GRAPHWIDGET_H
