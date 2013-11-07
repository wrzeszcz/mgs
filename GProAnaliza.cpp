#include "GProAnaliza.h"

GProAnaliza::GProAnaliza(GeoZasoby *zasoby, QWidget *parent):
    QDialog(parent),
    geoZasoby(zasoby)
{
    this->setModal(true);
}

GProAnaliza::~GProAnaliza()
{

}

void GProAnaliza::createLayout()
{

}
