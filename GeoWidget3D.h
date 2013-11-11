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

#ifndef GEOWIDGET3D_H
#define GEOWIDGET3D_H

#include "GeoWidget.h"
#include "GLWidget3D.h"
#include "globalne.h"

class QCheckBox;
///
/// \brief The GeoWidget3D class
///
class GeoWidget3D: public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidget3D
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidget3D(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidget3D
    ///
    virtual ~GeoWidget3D();

protected:
    ///
    /// \brief create_toolbar
    ///
    void create_toolbar();

signals:
    ///
    /// \brief signalUpdateView
    ///
    void signalUpdateView(Vset);

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
    /// \brief slot_update_view
    ///
    void slot_update_view();
    ///
    /// \brief slotZakres
    ///
    void slotZakres(int i);
    ///
    /// \brief slotDane
    /// \param i
    ///
    void slotDane(int i);
    ///
    /// \brief slotSiatka
    /// \param i
    ///
    void slotSiatka(int i);
    ///
    /// \brief slotWezel
    /// \param i
    ///
    void slotWezel(int i);
    ///
    /// \brief slotZasoby
    /// \param i
    ///
    void slotZasoby(int i);
    ///
    /// \brief slot_zoom_fit
    ///
    void slot_zoom_fit();
    ///
    /// \brief slot_reset_view
    /// \return
    ///
    void slot_reset_view();
    ///
    /// \brief slot_punkt
    ///
    void slot_punkt(wektor3d);
    ///
    /// \brief slot_zoom_in
    ///
    void slot_zoom_in();
    ///
    /// \brief slot_zoom_out
    ///
    void slot_zoom_out();

private:
    ///
    /// \brief wiev3d
    ///
    GLWidget3D *wiev3d;
    ///
    /// \brief cbZakres
    ///
    QCheckBox *cbZakres;
    ///
    /// \brief cbDane
    ///
    QCheckBox *cbDane;
    ///
    /// \brief cbSiatka
    ///
    QCheckBox *cbSiatka;
    ///
    /// \brief cbWezel
    ///
    QCheckBox *cbWezel;
    ///
    /// \brief cbZasoby
    ///
    QCheckBox *cbZasoby;
    ///
    /// \brief cbPerspektywa
    ///
    QCheckBox *cbPerspektywa;
    ///
    /// \brief act_zoom_fit
    ///
    QAction *act_zoom_fit;
    ///
    /// \brief act_zoom_plus
    ///
    QAction *act_zoom_plus;
    ///
    /// \brief act_zoom_minus
    ///
    QAction *act_zoom_minus;
    ///
    /// \brief act_zoom_select
    ///
    QAction *act_zoom_select;
    ///
    /// \brief widok
    ///
    Vset widok;
};

#endif // GEOWIDGET3D_H
