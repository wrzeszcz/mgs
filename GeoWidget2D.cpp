#include "GeoWidget2D.h"
#include <QAction>
#include <QCheckBox>
#include <QSlider>
#include <QDebug>

//------------------------------------------------------------------------------
GeoWidget2D::GeoWidget2D(GeoModel *ptrModel, QWidget *parent):
    GeoWidget(ptrModel, parent)
{
    this->setAccessibleName("MAPA");
    this->setWindowTitle("MAPA");
    wiev2d = new GLWidget2D(gModel,widok,this);
    boxLayout->addWidget(wiev2d);
    create_toolbar();
    create_slider();

    connect(parent,SIGNAL(signal_zmiana_danych()),this,SLOT(slot_update_dane()));
    connect(parent,SIGNAL(signal_zmiana_modelu()),this,SLOT(slot_update_model()));
    connect(this,SIGNAL(signalUpdateView(Vset)),wiev2d,SLOT(slot_set_widok(Vset)));
    connect(parent,SIGNAL(signal_zmiana_punktu(wektor3d)),this,SLOT(slot_punkt(wektor3d)));
}
 //-----------------------------------------------------------------------------
GeoWidget2D::~GeoWidget2D()
{

}
//------------------------------------------------------------------------------
void GeoWidget2D::slot_update_dane()
{
    wiev2d->update_model();
    int z = gModel->ptr_mset()->grid.z;
    if (!z) z=1;
    sliderZ->setRange(0,z-1);
    wiev2d->repaint();
}
//------------------------------------------------------------------------------
void GeoWidget2D::slot_update_model()
{
     wiev2d->repaint();
}
//------------------------------------------------------------------------------
void GeoWidget2D::slotZakres(int i)
{
    widok.zakres=i;
    emit signalUpdateView(widok);
}
//------------------------------------------------------------------------------
void GeoWidget2D::slotDane(int i)
{
    widok.error_map=i;
    emit signalUpdateView(widok);
}
//------------------------------------------------------------------------------
void GeoWidget2D::slotSiatka(int i)
{
    widok.siatka=i;
    emit signalUpdateView(widok);
}
//------------------------------------------------------------------------------
void GeoWidget2D::slotWezel(int i)
{
    widok.wezel=i;
    emit signalUpdateView(widok);
}
//------------------------------------------------------------------------------
void GeoWidget2D::slotZasoby(int i)
{
    widok.zasoby=i;
    emit signalUpdateView(widok);
}
//------------------------------------------------------------------------------
void GeoWidget2D::slot_zoom_fit()
{
    wiev2d->set_scale(0.9);
    wiev2d->set_dx(0.0);
    wiev2d->set_dy(0.0);
    wiev2d->repaint();
}
//------------------------------------------------------------------------------
void GeoWidget2D::slot_zoom_in()
{
    float nscale = wiev2d->get_scale() * 0.9;
    wiev2d->set_scale(nscale);
    wiev2d->repaint();
}
//------------------------------------------------------------------------------
void GeoWidget2D::slot_zoom_out()
{
    float nscale = wiev2d->get_scale() * 1.1;
    wiev2d->set_scale(nscale);
    wiev2d->repaint();
}
//------------------------------------------------------------------------------
void GeoWidget2D::slot_slider_z(int z)
{
    wiev2d->setZ(z);
}
//------------------------------------------------------------------------------
void GeoWidget2D::slot_punkt(wektor3d p)
{
    wiev2d->slot_point(p);
}
//------------------------------------------------------------------------------
void GeoWidget2D::create_toolbar()
{
    cbZakres = new QCheckBox("ZAKRES", this);
    cbZakres->setChecked(widok.zakres);
    toolBar->addWidget(cbZakres);
    connect (cbZakres,SIGNAL(stateChanged(int)),this,SLOT(slotZakres(int)));
    cbDane = new QCheckBox("BŁĄD", this);
    cbDane->setChecked(widok.error_map);
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
    toolBar->addWidget(cbZasoby);
    connect (cbZasoby,SIGNAL(stateChanged(int)),this,SLOT(slotZasoby(int)));
    act_zoom_fit = new QAction(QIcon(":/zoomfit"), tr("Zoom to fit"),this);
    toolBar->addAction(act_zoom_fit);
    connect(act_zoom_fit,SIGNAL(triggered()),this,SLOT(slot_zoom_fit()));
    act_zoom_plus = new QAction(QIcon(":/zoomplus"), tr("Powiększ"),this);
    connect(act_zoom_plus,SIGNAL(triggered()),this,SLOT(slot_zoom_out()));
    toolBar->addAction(act_zoom_plus);
    act_zoom_minus = new QAction(QIcon(":/zoomminus"), tr("Pommniejsz"),this);
    connect(act_zoom_minus,SIGNAL(triggered()),this,SLOT(slot_zoom_in()));
    toolBar->addAction(act_zoom_minus);
    act_zoom_select = new QAction(QIcon(":/zoomselect"), tr("Powiększ do zaznaczenia"),this);
    toolBar->addAction(act_zoom_select);
}
//------------------------------------------------------------------------------
void GeoWidget2D::create_slider()
{
    sliderZ = new QSlider(this);
    int z = gModel->ptr_mset()->grid.z;
    if (!z) z=1;
    sliderZ->setRange(0,z-1);
    sliderZ->setOrientation(Qt::Horizontal);
    connect(sliderZ,SIGNAL(valueChanged(int)),this,SLOT(slot_slider_z(int)));
    boxLayout->addWidget(sliderZ);
}
//------------------------------------------------------------------------------
