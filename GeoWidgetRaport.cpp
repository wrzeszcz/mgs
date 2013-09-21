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
