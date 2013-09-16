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
