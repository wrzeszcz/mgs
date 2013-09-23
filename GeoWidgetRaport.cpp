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
#include <QScrollBar>
#include <QDateTime>
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
    reload_report();
}
//------------------------------------------------------------------------------
void GeoWidgetRaport::slot_update_model()
{
    reload_report();
}
//------------------------------------------------------------------------------
void GeoWidgetRaport::slot_create_report()
{
    gModel->raport_clear();
    Mset *ms = gModel->ptr_mset();
    gModel->raport_add
        (
            "MGEOSTAT 0.1 2013 marek.wrzeszcz@hotmail.com\n"
            "RAPORT =========================================================\n"
            + QDateTime::currentDateTime().toString().toStdString() + "\n\n"
            "DANE WEJŚCIOWE =================================================\n"
            "dane: "+ ms->name + "\n"
            "wiersze: " + cos2str(gModel->ptr_dane()->get_size()) + "\n"
            "początek xyz:\t"+ cos2str(ms->start) + "\n"
            "końcowe xyz:\t"+ cos2str(gModel->ptr_dane()->get_max_zakres())+"\n"
            "min wartość:\t"+ cos2str(gModel->ptr_dane()->get_min_value())+"\n"
            "max wartość:\t"+ cos2str(gModel->ptr_dane()->get_max_value())+"\n\n"
            "MODEL ==========================================================\n"
            "wymiary modelu: \t"+ cos2str(ms->grid) + "\n"
            "rozmiar bloku : \t"+ cos2str(ms->sp) + "\n"
            "początek xyz:\t"+ cos2str(ms->start) + "\n"
            "wymiary xyz:\t"+ cos2str(ms->get_wymiary()) + "\n"
            "ilość bloków: \t"+ cos2str(ms->get_bloki()) + "\n"
            "objętość modelu: \t"+ cos2str(ms->get_objetosc()) + "\n"
            "gęstość przestrzenna: \t"+ cos2str(ms->gestosc) + "\n"
            "masa modelu: \t"+ cos2str(ms->get_masa()) + "\n"
            "min wartość: \t"+cos2str(ms->min_val)+"\n"
            "max wartość: \t"+cos2str(ms->max_val)+"\n\n"
            "ZASOBY =========================================================\n"
            "cut-off: \t"+ cos2str(ms->cutoff) + "\n"
            "zasoby: \t"+ cos2str(gModel->policzZasoby()) + "\n"

                + gModel->analizaZasobyReport(10) +"\n"
            "min wartość: "+cos2str(ms->min_val)+"\n"
            "max wartość: "+cos2str(ms->max_val)+"\n"
        );
    reload_report();
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
void GeoWidgetRaport::reload_report()
{
    textEdit -> clear();
    textEdit -> append(QString::fromStdString(gModel->raport_get()));
    textEdit -> moveCursor (QTextCursor::Start) ;
    textEdit -> ensureCursorVisible() ;
}
//------------------------------------------------------------------------------
