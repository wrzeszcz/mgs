#include "GeoWidgetDane.h"
//------------------------------------------------------------------------------------------
GeoWidgetDane::GeoWidgetDane(GeoModel *ptrModel, QWidget *parent):
    GeoWidget(ptrModel, parent)
{
    this->setAccessibleName("DANE");
    this->setWindowTitle("DANE");

    create_view();
    slot_update_dane();

    connect(tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(slot_selected(QModelIndex)));
    connect(parent,SIGNAL(signal_zmiana_danych()),this,SLOT(slot_update_dane()));
    connect(this, SIGNAL(signal_selected(wektor3d)),parent,SLOT(slot_zmiana_punktu(wektor3d)));
    connect(actZapiszDane,SIGNAL(triggered()),parent, SLOT(slot_zapis_dane()));
}
//------------------------------------------------------------------------------------------
GeoWidgetDane::~GeoWidgetDane()
{

}
//------------------------------------------------------------------------------------------
void GeoWidgetDane::create_view()
{
    tableView = new QTableView();
    itemModel = new QStandardItemModel();
    QStringList labels;
    labels << "X" << "Y" << "Z" << "Par 1" << "Par 2" << "Par 3";
    itemModel->setHorizontalHeaderLabels(labels);
    tableView->setModel(itemModel);
    boxLayout->addWidget(tableView);
    actZapiszDane = new QAction(QIcon(":/save"), tr("Zapisz dane"),this);
    toolBar->addAction(actZapiszDane);
}
//-----------------------------------------------------------------------------------------------
void GeoWidgetDane::slot_update_dane()
{
    itemModel->removeRows(0,itemModel->rowCount());

    if(gModel->ptr_dane())
    {
        dane = gModel->ptr_dane();
        for (GeoMapa::iterator it = dane->get_begin();it != dane->get_end(); ++it)
        {
            std::vector<double> wiersz = dane->get_rek(it);
            QList<QStandardItem*> listWiersz;
            for(int i=0;i<wiersz.size();++i)
            {
                QStandardItem *item = new QStandardItem(QString::number(wiersz[i],'f',4));
                item->setEditable(false);
                item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
                listWiersz << item;

            }
            itemModel->appendRow(listWiersz);
        }
    }

}
//---------------------------------------------------------------------------------------
void GeoWidgetDane::slot_selected(QModelIndex ind)
{
    QStandardItem *tmp = itemModel->itemFromIndex(ind);
    int r = tmp->row();
    wektor3d ret;
    tmp = itemModel->item(r,0);
    ret.x = tmp->text().toDouble();
    tmp = itemModel->item(r,1);
    ret.y = tmp->text().toDouble();
    tmp = itemModel->item(r,2);
    ret.z = tmp->text().toDouble();
    emit signal_selected(ret);
}
