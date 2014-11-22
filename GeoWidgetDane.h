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
#include <QAbstractTableModel>
#include <QDebug>

class QAction;
class QTableView;

class DatModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DatModel(QObject *parent, GeoDat *dat):QAbstractTableModel(parent), dane(dat) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const
    {
        return dane->get_size();
    }
    int columnCount(const QModelIndex &parent = QModelIndex()) const
    {
        return 6;
    }
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const
    {
        int row = index.row();
        int col = index.column();

        geo3d record = dane->getRek(row);;

        if (role == Qt::DisplayRole)
           {
            switch (col) {
                case 0:
                    return record.xyz.x;
                    break;
                case 1:
                    return record.xyz.y;
                    break;
                case 2:
                    return record.xyz.z;
                    break;
                case 3:
                    return record.dat.x;
                    break;
                case 4:
                    return record.dat.y;
                    break;
                case 5:
                    return record.dat.z;
                    break;
                default:
                    break;
            }
           }
        return QVariant();
    }
private:
    GeoDat *dane;
};

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
    ///
    /// \brief datModel
    ///
    DatModel *datModel;
};

#endif // GEOWIDGETDANE_H
