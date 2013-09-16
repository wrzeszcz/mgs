#include "GeoWidget.h"

GeoWidget::GeoWidget(QWidget *parent) :
    QWidget(parent)
{
    gModel = NULL;
    create_widget();
}

GeoWidget::GeoWidget(GeoModel *ptrModel, QWidget *parent):
    gModel(ptrModel),
    QWidget(parent)
{
    create_widget();
}
GeoWidget::~GeoWidget()
{

}

void GeoWidget::slot_update_dane()
{

}

void GeoWidget::slot_update_view()
{

}

void GeoWidget::slot_update_model()
{

}

void GeoWidget::create_widget()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    toolBar = new QToolBar("tools");
    boxLayout = new QVBoxLayout(this);
    boxLayout->setContentsMargins(0,0,0,0);
    boxLayout->setSpacing(0);
    boxLayout->addWidget(toolBar);
}
