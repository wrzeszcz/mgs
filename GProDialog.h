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

#ifndef GPRODIALOG_H
#define GPRODIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include "globalne.h"
#include <QSpinBox>
//------------------------------------------------------------------------------
///
/// \brief The GeoDoubleSpin class
///
class GeoDoubleSpin: public QDoubleSpinBox
{
public:
    ///
    /// \brief GeoDoubleSpin
    /// \param min
    /// \param max
    /// \param dec
    /// \param step
    /// \param parent
    ///
    GeoDoubleSpin(double min,double max,int dec,double step, QWidget *parent=0):
        QDoubleSpinBox(parent)
    {
        this->setRange(min,max);
        this->setDecimals(dec);
        this->setSingleStep(step);
        this->setAlignment(Qt::AlignRight);
    }
};
//------------------------------------------------------------------------------
///
/// \brief The GProDialog class
///
class GProDialog : public QDialog
{
    Q_OBJECT
public:
    ///
    /// \brief GProDialog
    /// \param parent
    ///
    GProDialog(Set_interpolacja, METODA, QWidget *parent = 0);
    ///
    /// \brief ~GProDialog
    ///
    virtual ~GProDialog();
    ///
    /// \brief get_set_interp
    /// \return
    ///
    Set_interpolacja get_set_interp();
    
public slots:
    ///
    /// \brief slot_promien
    /// \param d
    ///
    void slot_promien(double d);
    ///
    /// \brief slot_vario
    /// \param v
    ///
    void slot_vario(int v);
    ///
    /// \brief slot_nugget
    /// \param d
    ///
    void slot_nugget(double d);
    ///
    /// \brief slot_sill
    /// \param d
    ///
    void slot_sill(double d);
    ///
    /// \brief slot_range
    /// \param d
    ///
    void slot_range(double d);
    ///
    /// \brief slot_potega
    /// \param d
    ///
    void slot_potega(double d);
    ///
    /// \brief slot_min_otocz
    /// \param i
    ///
    void slot_min_otocz(int i);
    ///
    /// \brief slot_max_otocz
    /// \param i
    ///
    void slot_max_otocz(int i);

private:
    ///
    /// \brief update_all
    ///
    void update_all();
    ///
    /// \brief createLayout
    ///
    void createLayout();
    ///
    /// \brief createLayoutAll
    ///
    void createLayoutAll();
    ///
    /// \brief createLayoutKri
    ///
    void createLayoutKri();
    ///
    /// \brief createLayoutInv
    ///
    void createLayoutInv();

    ///
    /// \brief mainLayout
    ///
    QVBoxLayout *mainLayout;
    ///
    /// \brief all_grup
    ///
    QGroupBox *all_grup;
    ///
    /// \brief kri_grup
    ///
    QGroupBox *kri_grup;
    ///
    /// \brief inv_grup
    ///
    QGroupBox *inv_grup;

    ///
    /// \brief layoutAll
    ///
    QGridLayout *layoutAll;
    ///
    /// \brief layoutKri
    ///
    QGridLayout *layoutKri;
    ///
    /// \brief layoutInv
    ///
    QGridLayout *layoutInv;

    ///
    /// \brief sb_promien
    ///
    GeoDoubleSpin *sb_promien;
    ///
    /// \brief sb_nugget
    ///
    GeoDoubleSpin *sb_nugget;
    ///
    /// \brief sb_sill
    ///
    GeoDoubleSpin *sb_sill;
    ///
    /// \brief sb_range
    ///
    GeoDoubleSpin *sb_range;
    ///
    /// \brief sb_potega
    ///
    GeoDoubleSpin *sb_potega;
    ///
    /// \brief sb_min_otocz
    ///
    QSpinBox *sb_min_otocz;
    ///
    /// \brief sb_max_otocz
    ///
    QSpinBox *sb_max_otocz;
    ///
    /// \brief combo_vario
    ///
    QComboBox *combo_vario;
    ///
    /// \brief lab_pro
    ///
    QLabel *lab_pro;
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
    /// \brief lab_met
    ///
    QLabel *lab_met;
    ///
    /// \brief lab_pot
    ///
    QLabel *lab_pot;
    ///
    /// \brief lab_min
    ///
    QLabel *lab_min;
    ///
    /// \brief lab_max
    ///
    QLabel *lab_max;
    ///
    /// \brief butBox
    ///
    QDialogButtonBox *butBox;
    ///
    /// \brief set_in
    ///
    Set_interpolacja set_in;
    ///
    /// \brief metoda
    ///
    METODA metoda; 
};

#endif // GPRODIALOG_H
