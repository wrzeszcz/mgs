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

#include "GProAnaliza.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QDebug>

GProAnaliza::GProAnaliza(GeoZasoby *zasoby, GeoModel *model, QWidget *parent):
    QDialog(parent),
    geoZasoby(zasoby),
    geoModel(model),
    klasy(geoModel->ptr_mset()->klasy_zas)
{
    this->setModal(true);

    this->setWindowTitle(tr("DOBIERZ KLASY ANALIZY ZASOBÓW"));
    this->resize(500,400);
    butBox = new QDialogButtonBox((QDialogButtonBox::Ok | QDialogButtonBox::Cancel), Qt::Horizontal,this);
    connect(butBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(butBox, SIGNAL(rejected()), this, SLOT(reject()));


    createLayout();
    update_all();
    //slot_table();


}

GProAnaliza::~GProAnaliza()
{

}

void GProAnaliza::slot_klasy(int i)
{
    klasy = i;
    slot_table();
}

void GProAnaliza::slot_table()
{
    itemModel->removeRows(0,itemModel->rowCount());
    geoZasoby->set_klasy(klasy);
    analiza = geoZasoby->analiza_zasoby();
    graph->set_data(analiza);
    graph->repaint();
    qDebug()<<analiza.size();

    QStandardItem *item = 0;
    std::vector<geo3d>::iterator it = analiza.begin();
    for(; it != analiza.end(); ++it)
    {
        QList<QStandardItem*> listWiersz;
        item = new QStandardItem(QString::number(it->xyz.y,'f',3));
        item->setTextAlignment(Qt::AlignRight);
        listWiersz << item;
        item = new QStandardItem(QString::number(it->xyz.z,'f',3));
        item->setTextAlignment(Qt::AlignRight);
        listWiersz << item;
        item = new QStandardItem(QString::number(it->dat.x,'f',0));
        item->setTextAlignment(Qt::AlignRight);
        listWiersz << item;
        item = new QStandardItem(QString::number(it->dat.y,'f',4));
        item->setTextAlignment(Qt::AlignRight);
        listWiersz << item;
        item = new QStandardItem(QString::number(it->dat.z,'f',3));
        item->setTextAlignment(Qt::AlignRight);
        listWiersz << item;
        itemModel->appendRow(listWiersz);
    }
    tableView->resizeColumnsToContents() ;
}

void GProAnaliza::createLayout()
{
    mainLayout = new QVBoxLayout();
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    all_grup = new QGroupBox();
    createLayoutAll();

    createTableView();



    graph = new GraphColumnWidget();
    QPalette p(palette());
    p.setColor(QPalette::Background, Qt::black);
    graph->setAutoFillBackground(true);
    graph->setPalette(p);
    //graph->resize(100,500);

    QGroupBox *formGroupBox = new QGroupBox(tr("WYKRES"));
    QFormLayout *layout = new QFormLayout;
    layout->addRow(new QLabel(tr("Line 1:")),graph);
    formGroupBox->setLayout(layout);

    layoutAll->setRowMinimumHeight(2,150);
    layoutAll->addWidget(graph,2,0, 4, 2);
    layoutAll->setColumnStretch(0,20);


    all_grup->setLayout(layoutAll);
    mainLayout->addWidget(all_grup);

    //mainLayout->addWidget(formGroupBox);



    mainLayout->addWidget(tableView);
    mainLayout->addWidget(butBox);

    setLayout(mainLayout);
}

void GProAnaliza::createLayoutAll()
{
    layoutAll = new QGridLayout(this);
    lab_klasy = new QLabel("ILOŚĆ PRZEDZIAŁÓW", this);
    lab_klasy->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    layoutAll->addWidget(lab_klasy,1,0);
    sb_klasy = new QSpinBox(this);
    sb_klasy->setRange(1,1000);
    sb_klasy->setAlignment(Qt::AlignRight);
    connect(sb_klasy, SIGNAL(valueChanged(int)), this, SLOT(slot_klasy(int)));
    layoutAll->addWidget(sb_klasy,1,1);
}

void GProAnaliza::createTableView()
{
    tableView = new QTableView();
    itemModel = new QStandardItemModel();
    QStringList labels;
    labels << "MIN" << "MAX" << "BLOKI" << "MASA SKŁADNIKA" << "MASA CAŁKOWITA";
    itemModel->setHorizontalHeaderLabels(labels);
    tableView->setModel(itemModel);
}

void GProAnaliza::update_all()
{
    sb_klasy->setValue(klasy);
}
