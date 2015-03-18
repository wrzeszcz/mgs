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

#ifndef GEOWIDGET_H
#define GEOWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include "GeoModel.h"
///
/// \brief The GeoWidget class
///
class GeoWidget : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidget
    /// \param parent
    ///
    GeoWidget(QWidget *parent = 0);
    ///
    /// \brief GeoWidget
    /// \param ptrModel - wskażnik na model
    /// \param parent
    ///
    GeoWidget(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidget
    ///
    virtual ~GeoWidget();
    ///
    /// \brief set_model
    /// \param model
    ///
    void set_model(GeoModel *model){gModel = model;}
    ///
    /// \brief get_model
    /// \return
    ///
    GeoModel *get_model(){return gModel;}
    
public slots:
    ///
    /// \brief slot_update_dane
    ///
    virtual void slot_update_dane();
    ///
    /// \brief slot_update_view
    ///
    virtual void slot_update_view();
    ///
    /// \brief slot_update_model
    ///
    virtual void slot_update_model();

protected:
    ///
    /// \brief gModel
    ///
    GeoModel *gModel;
    ///
    /// \brief toolBar
    ///
    QToolBar *toolBar;
    ///
    /// \brief boxLayout
    ///
    QVBoxLayout *boxLayout;

private:
    void create_widget();
};

#endif // GEOWIDGET_H
