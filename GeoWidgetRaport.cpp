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

#include "GeoWidgetRaport.h"
//------------------------------------------------------------------------------
GeoWidgetRaport::GeoWidgetRaport(GeoModel *ptrModel, QWidget *parent):
    GeoWidget(ptrModel, parent)
{
    this->setAccessibleName("RAPORT");
    this->setWindowTitle("RAPORT");

    create_text_edit();
    slot_update_model();

    connect(parent,SIGNAL(signal_zmiana_modelu()),
            this,SLOT(slot_update_model()));
    connect(parent,SIGNAL(signal_zmiana_danych()),
            this,SLOT(slot_update_dane()));
    connect(actZapiszRaport,SIGNAL(triggered()),
            parent, SLOT(slot_zapis_raport()));
    connect(actCreateRaport,SIGNAL(triggered()),
            this, SLOT(slot_create_report()));
}
//------------------------------------------------------------------------------
GeoWidgetRaport::~GeoWidgetRaport()
{
}
//------------------------------------------------------------------------------
void GeoWidgetRaport::slot_update_dane()
{
    textEdit->clear();
    textEdit->append(QString::fromStdString(gModel->raport_get()));
}
//------------------------------------------------------------------------------
void GeoWidgetRaport::slot_update_model()
{
    textEdit->clear();
    textEdit->append(QString::fromStdString(gModel->raport_get()));
}
//------------------------------------------------------------------------------
void GeoWidgetRaport::slot_create_report()
{
    textEdit->clear();
    //to do
}
//------------------------------------------------------------------------------
void GeoWidgetRaport::create_text_edit()
{
    textEdit = new QTextEdit();
    boxLayout->addWidget(textEdit);
    actZapiszRaport= new QAction(QIcon(":/save"), tr("Zapisz raport"),this);
    actCreateRaport= new QAction(QIcon(":/raport"),tr("Przygotuj raport"),this);
    toolBar->addAction(actZapiszRaport);
    toolBar->addAction(actCreateRaport);
}
//------------------------------------------------------------------------------
