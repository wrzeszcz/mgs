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

#include "GeoWidgetVariogram.h"
#include <QSpinBox>
#include <QFuture>
#include <QtConcurrentRun>
#include <boost/bind.hpp>
#include <QDebug>
//------------------------------------------------------------------------------
GeoWidgetVariogram::GeoWidgetVariogram(GeoModel *ptrModel, QWidget *parent):
    GeoWidget(ptrModel, parent)
{
    this->setAccessibleName("VARIOGRAM");
    this->setWindowTitle("SEMIWARIOGRAM");
    create();

    slot_update_dane();

    connect(parent,SIGNAL(signal_zmiana_danych()),
            this,SLOT(slot_update_dane()));
    connect(actZapiszVariogram,SIGNAL(triggered()),
            parent, SLOT(slot_zapis_variogram()));
     connect(this,SIGNAL(signal_recalc()),
            parent,SLOT(slot_variogram()));
}
//------------------------------------------------------------------------------
GeoWidgetVariogram::~GeoWidgetVariogram()
{
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::mouseMoveEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_update_dane()
{
   if(gModel->ptr_vario())
   {
        graph->set_pkt_vario(gModel->ptr_vario()->get_klasy());
        graph->set_function(gModel->get_iset());
   }
   else graph->clear_pkt_vario();
   cur_set_vario = gModel->get_iset();
   update_edit();
   graph->repaint();
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_vario(int v)
{
    //fi(v==0)cur_set_vario.vario = EXPONENTIAL;
    //else if (v==1)cur_set_vario.vario = SPHERICAL;
    cur_set_vario.vario = (variogram)v;
    qDebug() << cur_set_vario.vario;
    graph->set_function(cur_set_vario);
    graph->repaint();
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_nugget(QString d)
{
    cur_set_vario.nuget_c0 = d.toDouble();
    graph->set_function(cur_set_vario);
    graph->repaint();
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_sill(QString d)
{
    cur_set_vario.sill_c1 = d.toDouble();
    graph->set_function(cur_set_vario);
    graph->repaint();
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_range(QString d)
{
    cur_set_vario.range_a = d.toDouble();
    graph->set_function(cur_set_vario);
    graph->repaint();
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_klasa(QString d)
{
    cur_set_vario.set_variogram.x = d.toDouble();
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_kopuj_do()
{
    gModel->set_iset(cur_set_vario);
}
//------------------------------------------------------------------------------
void GeoWidgetVariogram::slot_przelicz()
{
    gModel->set_iset(cur_set_vario);
    emit signal_recalc();
    slot_update_dane();
    graph->repaint();
}

void GeoWidgetVariogram::slot_ile_klas(int i)
{
    cur_set_vario.set_variogram.y = i;
}

void GeoWidgetVariogram::slot_min_klas(int i)
{
    cur_set_vario.set_variogram.z = i;
}
//-----------------------------------------------------------------------------
void GeoWidgetVariogram::create()
{
    graph = new GraphWidget(this);
    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::black);
    graph->setAutoFillBackground(true);
    graph->setPalette(p);
    boxLayout->addWidget(graph);

    actZapiszVariogram = new QAction(QIcon(":/save"), tr("Zapisz dane"),this);

    QDoubleValidator *dv = new QDoubleValidator(0.0,1000000.0,4);

    combo_vario = new QComboBox();
    combo_vario->addItem("EXPONENTIAL",EXPONENTIAL);  
    combo_vario->addItem("SPHERICAL",SPHERICAL);
    combo_vario->addItem("GAUSSIAN",GAUSSIAN);
    combo_vario->addItem("LINEAR",LINEAR);
    combo_vario->addItem("POVER",POVER);
    connect(combo_vario,SIGNAL(currentIndexChanged(int)),
            this,SLOT(slot_vario(int)));
    toolBar->addWidget(combo_vario);

    lab_nug = new QLabel(" c0:");
    lab_nug->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    le_nugget = new QLineEdit();
    le_nugget->setAlignment(Qt::AlignRight);
    le_nugget->setMaxLength(9);
    le_nugget->setValidator(dv);
    connect(le_nugget,SIGNAL(textChanged(QString)),
            this,SLOT(slot_nugget(QString)));
    toolBar->addWidget(lab_nug);
    toolBar->addWidget(le_nugget);

    lab_sil = new QLabel(" c1:");
    lab_sil->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    le_sill = new QLineEdit();
    le_sill->setAlignment(Qt::AlignRight);
    le_sill->setMaxLength(9);
    le_sill->setValidator(dv);
    connect(le_sill,SIGNAL(textChanged(QString)),
            this,SLOT(slot_sill(QString)));
    toolBar->addWidget(lab_sil);
    toolBar->addWidget(le_sill);

    lab_ran = new QLabel(" a:");
    lab_ran->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    le_range = new QLineEdit();
    le_range->setAlignment(Qt::AlignRight);
    le_range->setMaxLength(9);
    le_range->setValidator(dv);
    connect(le_range,SIGNAL(textChanged(QString)),
            this,SLOT(slot_range(QString)));
    toolBar->addWidget(lab_ran);
    toolBar->addWidget(le_range);

    toolBar->addSeparator();

    lab_kla = new QLabel(" rozmiar klasy:");
    lab_kla->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    le_klasa = new QLineEdit();
    le_klasa->setAlignment(Qt::AlignRight);
    le_klasa->setMaxLength(9);
    le_klasa->setValidator(dv);
    connect(le_klasa,SIGNAL(textChanged(QString)),
            this,SLOT(slot_klasa(QString)));
    toolBar->addWidget(lab_kla);
    toolBar->addWidget(le_klasa);

    lab_kla_ile = new QLabel("ilość:");
    lab_kla_ile->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sb_kla_ile = new QSpinBox(this);
    sb_kla_ile->setRange(1,1000);
    sb_kla_ile->setAlignment(Qt::AlignRight);

    connect(sb_kla_ile,SIGNAL(valueChanged(int)),this,SLOT(slot_ile_klas(int)));

    toolBar->addWidget(lab_kla_ile);
    toolBar->addWidget(sb_kla_ile);

    lab_kla_min = new QLabel("min par:");
    lab_kla_min->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sb_kla_min = new QSpinBox(this);
    sb_kla_min->setRange(1,1000);
    sb_kla_min->setAlignment(Qt::AlignRight);

    connect(sb_kla_min,SIGNAL(valueChanged(int)),this,SLOT(slot_min_klas(int)));

    toolBar->addWidget(lab_kla_min);
    toolBar->addWidget(sb_kla_min);

    actCopyToSet=new QAction(QIcon(":/copy"), tr("Kopiuj do ustwień"),this);
    connect(actCopyToSet,SIGNAL(triggered()),this,SLOT(slot_kopuj_do()));

    act_przelicz=new QAction(QIcon(":/calc"), tr("Przelicz"),this);
    connect(act_przelicz,SIGNAL(triggered()),this,SLOT(slot_przelicz()));

    toolBar->addAction(act_przelicz);
    toolBar->addAction(actCopyToSet);
    toolBar->addAction(actZapiszVariogram);
}
//-----------------------------------------------------------------------------
void GeoWidgetVariogram::update_edit()
{
    le_nugget ->setText(QString::number(cur_set_vario.nuget_c0,'f',3));
    le_sill   ->setText(QString::number(cur_set_vario.sill_c1 ,'f',3));
    le_range  ->setText(QString::number(cur_set_vario.range_a ,'f',3));
    le_klasa  ->setText(QString::number(cur_set_vario.set_variogram.x,'f',3));
    sb_kla_ile->setValue(cur_set_vario.set_variogram.y);
    sb_kla_min->setValue(cur_set_vario.set_variogram.z);

    switch (cur_set_vario.vario)
    {
        case EXPONENTIAL:
        case SPHERICAL:
        case GAUSSIAN:
        case LINEAR:
        case POVER:combo_vario->setCurrentIndex((int)cur_set_vario.vario);break;
        default:combo_vario->setCurrentIndex(0);break;
    }

}
//-----------------------------------------------------------------------------


