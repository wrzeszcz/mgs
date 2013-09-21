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

#include "GProDialog.h"
//-----------------------------------------------------------------------------------------
GProDialog::GProDialog(Set_interpolacja s,METODA m, QWidget *parent):   
    QDialog(parent),
    mainLayout(0),
    set_in(s),
    metoda(m)
{
    this->setModal(true);
    butBox = new QDialogButtonBox((QDialogButtonBox::Ok | QDialogButtonBox::Cancel), Qt::Horizontal,this);
    connect(butBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(butBox, SIGNAL(rejected()), this, SLOT(reject()));

    createLayout();
    update_all();

    if(metoda == OKRIGING)
    {
        setWindowTitle(tr("KRIGING"));
        this->resize(400,550);
    }
    else setWindowTitle(tr("ODWROTNE ODLEGŁOŚCI"));
}
//-----------------------------------------------------------------------------------------
void GProDialog::createLayout()
{
    mainLayout = new QVBoxLayout();
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    all_grup = new QGroupBox();
    createLayoutAll();
    all_grup->setLayout(layoutAll);
    mainLayout->addWidget(all_grup);
    mainLayout->addWidget(butBox);

    if(metoda==OKRIGING)
    {
        QLabel *img = new QLabel(this);
        img->setScaledContents(true);
        img->setPixmap(QPixmap(":/vario_img"));
        mainLayout->addWidget(img);
    }
    setLayout(mainLayout);
}
//-----------------------------------------------------------------------------------------
void GProDialog::createLayoutAll()
{
    layoutAll = new QGridLayout(this);

    lab_pro = new QLabel("otoczenie (promień) r",this);
    lab_pro->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    sb_promien = new GeoDoubleSpin(0.000,999999.000,4,1.0,this);
    connect(sb_promien,SIGNAL(valueChanged(double)),this,SLOT(slot_promien(double)));
    layoutAll->addWidget(lab_pro,0,0);
    layoutAll->addWidget(sb_promien,0,1);

    if(metoda == OKRIGING)
    {
        lab_met = new QLabel("SEMIWARIOGRAM",this);
        lab_met->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        layoutAll->addWidget(lab_met,1,0);

        combo_vario = new QComboBox(this);
        combo_vario->addItem("WYKŁADNICZY",EXPONENTIAL);
        combo_vario->addItem("SFERYCZNY",SPHERICAL);
        combo_vario->addItem("GAUSOWSKI",GAUSSIAN);
        connect(combo_vario,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_vario(int)));
        layoutAll->addWidget(combo_vario,1,1);

        lab_nug = new QLabel("efekt samorodka (nugget) c0",this);
        lab_nug->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sb_nugget = new GeoDoubleSpin(0.000,999999.000,4,0.0001,this);
        connect(sb_nugget,SIGNAL(valueChanged(double)),this,SLOT(slot_nugget(double)));
        layoutAll->addWidget(lab_nug,2,0);
        layoutAll->addWidget(sb_nugget,2,1);

        lab_sil = new QLabel("próg nasycenia (sill) c1",this);
        lab_sil->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sb_sill = new GeoDoubleSpin(0.000,999999.000,4,0.0001,this);
        connect(sb_sill,SIGNAL(valueChanged(double)),this,SLOT(slot_sill(double)));
        layoutAll->addWidget(lab_sil,3,0);
        layoutAll->addWidget(sb_sill,3,1);

        lab_ran = new QLabel("zasięg korelacji (range) a",this);
        lab_ran->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sb_range = new GeoDoubleSpin(0.000,999999.000,4,0.0001,this);
        connect(sb_range,SIGNAL(valueChanged(double)),this,SLOT(slot_range(double)));
        layoutAll->addWidget(lab_ran,4,0);
        layoutAll->addWidget(sb_range,4,1);

        lab_min = new QLabel("min w otoczeniu",this);
        lab_min->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sb_min_otocz = new QSpinBox(this);
        sb_min_otocz->setRange(1,1000);
        sb_min_otocz->setAlignment(Qt::AlignRight);
        connect(sb_min_otocz,SIGNAL(valueChanged(int)),this,SLOT(slot_min_otocz(int)));
        layoutAll->addWidget(lab_min,5,0);
         layoutAll->addWidget(sb_min_otocz,5,1);

        lab_max = new QLabel("max w otoczeniu",this);
        sb_max_otocz = new QSpinBox(this);
        sb_max_otocz->setRange(1,1000);
        sb_max_otocz->setAlignment(Qt::AlignRight);
        lab_max->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        connect(sb_max_otocz,SIGNAL(valueChanged(int)),this,SLOT(slot_max_otocz(int)));
        layoutAll->addWidget(lab_max,6,0);
        layoutAll->addWidget(sb_max_otocz,6,1);
    }
    else if (metoda == INVDIST)
    {
        lab_pot = new QLabel("potęga", this);
        lab_pot->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        sb_potega = new GeoDoubleSpin(0.000,999999.000,4,1.0,this);
        connect(sb_potega,SIGNAL(valueChanged(double)),this,SLOT(slot_potega(double)));
        layoutAll->addWidget(lab_pot,1,0);
        layoutAll->addWidget(sb_potega,1,1);
    }
}
//-----------------------------------------------------------------------------------------
Set_interpolacja GProDialog::get_set_interp()
{
    return set_in;
}

GProDialog::~GProDialog()
{
    if(mainLayout)delete mainLayout;
}
//-----------------------------------------------------------------------------------------
void GProDialog::slot_promien(double d)
{
    set_in.promien = d;
}
//-----------------------------------------------------------------------------------------
void GProDialog::slot_nugget(double d)
{
    set_in.nuget_c0 = d;
}
//-----------------------------------------------------------------------------------------
void GProDialog::slot_sill(double d)
{
    set_in.sill_c1 = d;
}
//-----------------------------------------------------------------------------------------
void GProDialog::slot_range(double d)
{
    set_in.range_a = d;
}
//-----------------------------------------------------------------------------------------
void GProDialog::slot_potega(double d)
{
    set_in.potega = d;
}

void GProDialog::slot_min_otocz(int i)
{
    if(i > set_in.max_ilosc)
    {
        set_in.min_ilosc = set_in.max_ilosc;
        sb_min_otocz->setValue(set_in.min_ilosc);
    }
    else set_in.min_ilosc = i;
}

void GProDialog::slot_max_otocz(int i)
{
    if(i <= set_in.min_ilosc)
    {
        set_in.max_ilosc = set_in.min_ilosc;
        sb_max_otocz->setValue(set_in.max_ilosc);
    }
    else set_in.max_ilosc = i;
}
//-----------------------------------------------------------------------------------------
void GProDialog::slot_vario(int v)
{
     if(v==0)set_in.vario=EXPONENTIAL;
     else if (v==1)set_in.vario=SPHERICAL;
     else set_in.vario=GAUSSIAN;
}
//-----------------------------------------------------------------------------------------
void  GProDialog::update_all()
{
    sb_promien->setValue(set_in.promien );
    if (metoda == OKRIGING)
    {
        sb_nugget ->setValue(set_in.nuget_c0);
        sb_sill   ->setValue(set_in.sill_c1 );
        sb_range  ->setValue(set_in.range_a );
        combo_vario->setCurrentIndex(set_in.vario);
        sb_min_otocz->setValue(set_in.min_ilosc);
        sb_max_otocz->setValue(set_in.max_ilosc);
    }
    else if (metoda==INVDIST)
    {
       sb_potega->setValue(set_in.potega);
    }
}
//-----------------------------------------------------------------------------------------
