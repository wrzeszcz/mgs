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

#ifndef GEOWIDGETDANE_H
#define GEOWIDGETDANE_H

#include "GeoWidget.h"
#include <QStandardItemModel>
class QAction;
class QTableView;
///
/// \brief The GeoWidgetDane class
///
class GeoWidgetDane:public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidgetDane
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidgetDane(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidgetDane
    ///
    virtual ~GeoWidgetDane();

protected slots:
    ///
    /// \brief slot_update_dane
    ///
    void slot_update_dane();
    ///
    /// \brief slot_selected
    /// \param ind
    ///
    void slot_selected(QModelIndex ind);

signals:
    ///
    /// \brief signal_selected
    ///
    void signal_selected(wektor3d);

private:
    ///
    /// \brief create_view
    ///
    void create_view();
    ///
    /// \brief dane
    ///
    GeoDat *dane;
    ///
    /// \brief itemModel
    ///
    QStandardItemModel *itemModel;
    ///
    /// \brief tableView
    ///
    QTableView *tableView;
    ///
    /// \brief actZapiszDane
    ///
    QAction *actZapiszDane;
};

#endif // GEOWIDGETDANE_H
