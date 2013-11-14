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

#include "GeoWidget3D.h"
#include <QAction>
#include <QCheckBox>
#include <QSlider>

GeoWidget3D::GeoWidget3D(GeoModel *ptrModel, QWidget *parent):
     GeoWidget(ptrModel, parent)
{
    this->setAccessibleName("WIDOK 3D");
    this->setWindowTitle("WIDOK 3D");

   wiev3d = new GLWidget3D(gModel,widok,this);
   boxLayout->addWidget(wiev3d);

    create_toolbar();
    create_slider();

    connect(parent,SIGNAL(signal_zmiana_danych()),this,SLOT(slot_update_dane()));
    connect(parent,SIGNAL(signal_zmiana_modelu()),this,SLOT(slot_update_model()));
    connect(this,SIGNAL(signalUpdateView(Vset)),wiev3d,SLOT(slot_set_widok(Vset)));
    connect(parent,SIGNAL(signal_zmiana_punktu(wektor3d)),this,SLOT(slot_punkt(wektor3d)));
}

GeoWidget3D::~GeoWidget3D()
{

}
//------------------------------------------------------------------------------
void GeoWidget3D::create_toolbar()
{
    cbZakres = new QCheckBox("ZAKRES", this);
    cbZakres->setChecked(widok.zakres);
    toolBar->addWidget(cbZakres);
    connect (cbZakres,SIGNAL(stateChanged(int)),this,SLOT(slotZakres(int)));
    cbDane = new QCheckBox("DANE", this);
    cbDane->setChecked(widok.dane);
    toolBar->addWidget(cbDane);
    connect (cbDane,SIGNAL(stateChanged(int)),this,SLOT(slotDane(int)));
    cbSiatka = new QCheckBox("SIATKA", this);
    cbSiatka->setChecked(widok.siatka);
    toolBar->addWidget(cbSiatka);
    connect (cbSiatka,SIGNAL(stateChanged(int)),this,SLOT(slotSiatka(int)));
    cbWezel = new QCheckBox("WĘZŁY", this);
    cbWezel->setChecked(widok.wezel);
    toolBar->addWidget(cbWezel);
    connect (cbWezel,SIGNAL(stateChanged(int)),this,SLOT(slotWezel(int)));

    cbZasoby = new QCheckBox("ZASOBY", this);
    cbZasoby->setChecked(widok.zasoby);
    connect (cbZasoby,SIGNAL(stateChanged(int)),this,SLOT(slotZasoby(int)));
    toolBar->addWidget(cbZasoby);

    //cbPerspektywa = new QCheckBox("PERSPEKTYWA");
    //cbPerspektywa->setChecked(widok.perspektywa);
    //connect(cbPerspektywa,SIGNAL(stateChanged(int)),this,SLOT(slotPerspektywa(int)));

    act_zoom_fit = new QAction(QIcon(":/zoomfit"), tr("Zoom to fit"),this);
    toolBar->addAction(act_zoom_fit);
    connect(act_zoom_fit,SIGNAL(triggered()),this,SLOT(slot_zoom_fit()));

    act_zoom_plus = new QAction(QIcon(":/zoomplus"), tr("Powiększ"),this);
    connect(act_zoom_plus,SIGNAL(triggered()),this,SLOT(slot_zoom_in()));
    toolBar->addAction(act_zoom_plus);

    act_zoom_minus = new QAction(QIcon(":/zoomminus"), tr("Pommniejsz"),this);
    connect(act_zoom_minus,SIGNAL(triggered()),this,SLOT(slot_zoom_out()));
    toolBar->addAction(act_zoom_minus);

    act_zoom_select = new QAction(QIcon(":/rot_reset"), tr("Resutuj obrót"),this);
    connect(act_zoom_select,SIGNAL(triggered()),this,SLOT(slot_reset_view()));
    toolBar->addAction(act_zoom_select);
}

void GeoWidget3D::create_slider()
{
    sliderZ = new QSlider(this);
    int z = gModel->ptr_mset()->grid.z;
    if (!z) z=1;
    sliderZ->setRange(0,z-1);
    sliderZ->setOrientation(Qt::Horizontal);

    connect(sliderZ,SIGNAL(valueChanged(int)),this,SLOT(slot_slider_z(int)));
    sliderZ->setValue(sliderZ->maximum());
    boxLayout->addWidget(sliderZ);
}

void GeoWidget3D::slot_update_dane()
{
    wiev3d->wczytajObiekty();
    wiev3d->update_model();
    wiev3d->repaint();
}

void GeoWidget3D::slot_update_model()
{
    wiev3d->repaint();
}

void GeoWidget3D::slot_update_view()
{

}

void GeoWidget3D::slotZakres(int i)
{
    widok.zakres=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotDane(int i)
{
    widok.dane=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotSiatka(int i)
{
    widok.siatka=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotWezel(int i)
{
    widok.wezel=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotZasoby(int i)
{
    widok.zasoby=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slot_zoom_fit()
{
    wiev3d->set_zoom(75);
    wiev3d->repaint();
}

void GeoWidget3D::slot_reset_view()
{
    wiev3d->set_rot(0.0,0.0,0.0);
}

void GeoWidget3D::slot_punkt(wektor3d p)
{
    wiev3d->point(p);  
}

void GeoWidget3D::slot_zoom_in()
{
    float zoom = wiev3d->get_zoom() * 0.9;
    wiev3d->set_zoom(zoom);
    wiev3d->repaint();
}
void GeoWidget3D::slot_zoom_out()
{
    float zoom = wiev3d->get_zoom() * 1.1;
    wiev3d->set_zoom(zoom);
    wiev3d->repaint();
}

void GeoWidget3D::slot_slider_z(int i)
{
    wiev3d->setZ(i);
    wiev3d->repaint();
}
