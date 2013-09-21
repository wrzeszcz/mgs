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

#ifndef GEOWIDGETRAPORT_H
#define GEOWIDGETRAPORT_H

#include "GeoWidget.h"
#include <QTextEdit>
#include <QAction>
///
/// \brief The GeoWidgetRaport class
///
class GeoWidgetRaport: public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidgetRaport
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidgetRaport(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidgetRaport
    ///
    virtual ~GeoWidgetRaport();
    ///
    /// \brief ptr_textEdit
    /// \return
    ///
    QTextEdit *ptr_textEdit(){return textEdit;}

protected slots:
    ///
    /// \brief slot_update_dane
    ///
    void slot_update_dane();
    ///
    /// \brief slot_update_model
    ///
    void slot_update_model();
    ///
    /// \brief slot_create_report
    ///
    void slot_create_report();

private:
    ///
    /// \brief create_text_edit
    ///
    void create_text_edit();
    ///
    /// \brief textEdit
    ///
    QTextEdit *textEdit;
    ///
    /// \brief actZapiszRaport
    ///
    QAction *actZapiszRaport;
    ///
    /// \brief actCreateRaport
    ///
    QAction *actCreateRaport;
};

#endif // GEOWIDGETRAPORT_H
