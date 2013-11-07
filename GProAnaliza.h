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

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include "globalne.h"
#include "GeoZasoby.h"
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
    /// \param parent
    ///
    GProAnaliza(GeoZasoby *zasoby, QWidget *parent = 0);
    ///
    /// \brief ~GProAnaliza
    ///
    virtual ~GProAnaliza();

private:
    void createLayout();
    GeoZasoby *geoZasoby;
};

#endif // GPROANALIZA_H
