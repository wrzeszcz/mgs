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

#include "GProTree.h"

GProTree::GProTree(QTreeView *parent) : QTreeView(parent)
{

   model = new QStandardItemModel ;
   QStandardItem *rootNode = model->invisibleRootItem();
   this->setHeaderHidden(true);

   modRoot =  new QStandardItem(QIcon(":/box"),"MODEL");
   modRoot -> setEditable(false);
   varItem =  new QStandardItem(QIcon(":/vario"),"VARIOGRAM");
   varItem -> setEditable(false);
   datItem =  new QStandardItem(QIcon(":/data"),"DANE");
   datItem -> setEditable(false);
   mapItem =  new QStandardItem(QIcon(":/map"),"MAPA");
   mapItem -> setEditable(false);
   modItem =  new QStandardItem(QIcon(":/model"),"WIDOK 3D");
   modItem -> setEditable(false);
   rapItem =  new QStandardItem(QIcon(":/raport"),"RAPORT");
   rapItem -> setEditable(false);

   rootNode->appendRow(modRoot);
   modRoot ->appendRow(datItem);
   modRoot ->appendRow(mapItem);
   modRoot ->appendRow(varItem);
   modRoot ->appendRow(modItem);
   modRoot ->appendRow(rapItem);
   setModel(model);
   expandAll();

   connect(this, SIGNAL(clicked(QModelIndex)),this, SLOT(slot_clicked(QModelIndex)));
}
void GProTree::slot_clicked(QModelIndex ind)
{
    QStandardItem *tmp = model->itemFromIndex(ind);
    emit signal_open_win(tmp->text());
}
