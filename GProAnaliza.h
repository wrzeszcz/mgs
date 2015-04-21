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

#ifndef GPROANALIZA_H
#define GPROANALIZA_H

#include <QStandardItemModel>
#include <QFormLayout>
#include "globalne.h"
#include "GeoZasoby.h"
#include "GProDialog.h"
#include "GraphColumnWidget.h"

class QTableView;
//------------------------------------------------------------------------------
///
/// \brief The GProAnaliza class
///
class GProAnaliza : public QDialog
{
    Q_OBJECT
public:
    ///
    /// \brief GProAnaliza
    /// \param zasoby
    /// \param model
    /// \param parent
    ///
    GProAnaliza(GeoZasoby *zasoby,GeoModel *model, QWidget *parent = 0);
    ///
    /// \brief ~GProAnaliza
    ///
    virtual ~GProAnaliza();

    int get_klasy(){return klasy;}

private slots:
    void slot_klasy(int);
    void slot_table();

private:  
    void createLayout();
    void createLayoutAll();
    void createTableView();
    void update_all();
    GeoZasoby *geoZasoby;
    GeoModel  *geoModel;


    std::vector<geo3d> analiza;
    int klasy;
    GraphColumnWidget *graph;

    QDialogButtonBox *butBox;
    QVBoxLayout *mainLayout;
    QGroupBox *all_grup;
    QGridLayout *layoutAll;

    QLabel *lab_klasy;
    QSpinBox *sb_klasy;

    QStandardItemModel *itemModel;
    QTableView *tableView;
};

#endif // GPROANALIZA_H
