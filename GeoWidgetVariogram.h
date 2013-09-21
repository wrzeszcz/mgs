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

#ifndef GEOWIDGETVARIOGRAM_H
#define GEOWIDGETVARIOGRAM_H

#include "GeoVariogram.h"
#include "GeoVariogramModel.h"
#include "GeoWidget.h"
#include "globalne.h"
#include "GraphWidget.h"

#include <QAction>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
///
/// \brief The GeoWidgetVariogram class
///
class GeoWidgetVariogram: public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidgetVariogram
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidgetVariogram(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidgetVariogram
    ///
    virtual ~GeoWidgetVariogram();

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

protected slots:
    ///
    /// \brief slot_update_dane
    ///
    void slot_update_dane();
    ///
    /// \brief slot_vario
    /// \param v
    ///
    void slot_vario(int v);
    ///
    /// \brief slot_nugget
    ///
    void slot_nugget(QString d);
    ///
    /// \brief slot_sill
    /// \param d
    ///
    void slot_sill(QString d);
    ///
    /// \brief slot_range
    /// \param d
    ///
    void slot_range(QString d);
    ///
    /// \brief slot_klasa
    /// \param d
    ///
    void slot_klasa(QString d);
    ///
    /// \brief slot_kopuj_do
    ///
    void slot_kopuj_do();
    ///
    /// \brief slot_przelicz
    ///
    void slot_przelicz();

private:
    ///
    /// \brief create
    ///
    void create();
    ///
    /// \brief update_edit
    ///
    void update_edit();
    ///
    /// \brief graph
    ///
    GraphWidget *graph;
    ///
    /// \brief curVar
    ///
    GeoVariogram *curVar;
    ///
    /// \brief mousePoz
    ///
    QPoint mousePoz;
    ///
    /// \brief actZapiszVariogram
    ///
    QAction *actZapiszVariogram;
    ///
    /// \brief actCopyToSet
    ///
    QAction *actCopyToSet;
    ///
    /// \brief act_przelicz
    ///
    QAction *act_przelicz;
    ///
    /// \brief cur_set_vario
    ///
    Set_interpolacja cur_set_vario;
    ///
    /// \brief le_nugget
    ///
    QLineEdit *le_nugget;
    ///
    /// \brief le_sill
    ///
    QLineEdit *le_sill;
    ///
    /// \brief le_range
    ///
    QLineEdit *le_range;
    ///
    /// \brief le_klasa
    ///
    QLineEdit *le_klasa;
    ///
    /// \brief combo_vario
    ///
    QComboBox *combo_vario;
    ///
    /// \brief lab_nug
    ///
    QLabel *lab_nug;
    ///
    /// \brief lab_sil
    ///
    QLabel *lab_sil;
    ///
    /// \brief lab_ran
    ///
    QLabel *lab_ran;
    ///
    /// \brief lab_kla
    ///
    QLabel *lab_kla;
};

#endif // GEOWIDGETVARIOGRAM_H
