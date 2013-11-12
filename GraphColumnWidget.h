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

#ifndef GRAPHCOLUMNWIDGET_H
#define GRAPHCOLUMNWIDGET_H

#include <QWidget>
#include "globalne.h"
#include <QMouseEvent>
#include <QSize>

///
/// \brief The GraphColumnWidget class
///
class GraphColumnWidget : public QWidget
{
public:
    ///
    /// \brief GraphColumnWidget
    /// \param parent
    ///
    explicit GraphColumnWidget(QWidget *parent = 0);
    ///
    /// \brief set_data
    /// \param data
    ///
    void set_data(std::vector<geo3d> &data);

protected:
    ///
    /// \brief paintEvent
    /// \param e
    ///
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    ///
    /// \brief dane
    ///
    std::vector<geo3d> dane;
    ///
    /// \brief max_masa
    ///
    double max_masa;
    ///
    /// \brief border
    ///
    QSize border;
    ///
    QSize area;
};

#endif // GRAPHCOLUMNWIDGET_H
