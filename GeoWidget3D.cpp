#include "GeoWidget3D.h"
#include <QAction>
#include <QCheckBox>

GeoWidget3D::GeoWidget3D(GeoModel *ptrModel, QWidget *parent):
     GeoWidget(ptrModel, parent)
{
    this->setAccessibleName("WIDOK 3D");
    this->setWindowTitle("WIDOK 3D");

   wiev3d = new GLWidget3D(gModel,widok,this);
   boxLayout->addWidget(wiev3d);

    create_toolbar();
    connect(parent,SIGNAL(signal_zmiana_danych()),this,SLOT(slot_update_dane()));
    connect(parent,SIGNAL(signal_zmiana_modelu()),this,SLOT(slot_update_model()));
    connect(this,SIGNAL(signalUpdateView(Vset)),wiev3d,SLOT(slot_set_widok(Vset)));
    connect(parent,SIGNAL(signal_zmiana_punktu(wektor3d)),this,SLOT(slot_punkt(wektor3d)));
}

GeoWidget3D::~GeoWidget3D()
{

}

void GeoWidget3D::create_toolbar()
{
    cbZakres = new QCheckBox("ZAKRES", this);
    cbZakres->setChecked(widok.zakres);
    toolBar->addWidget(cbZakres);
    connect (cbZakres,SIGNAL(stateChanged(int)),this,SLOT(slotZakres(int)));
    cbDane = new QCheckBox("DANE", this);
    cbDane->setChecked(widok.dane);
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
    //cbPerspektywa = new QCheckBox("PERSPEKTYWA");
    //cbPerspektywa->setChecked(widok.perspektywa);
    //connect(cbPerspektywa,SIGNAL(stateChanged(int)),this,SLOT(slotPerspektywa(int)));
    act_zoom_fit = new QAction(QIcon(":/zoomfit"), tr("Zoom to fit"),this);
    toolBar->addAction(act_zoom_fit);
    connect(act_zoom_fit,SIGNAL(triggered()),this,SLOT(slot_zoom_fit()));
    act_zoom_plus = new QAction(QIcon(":/zoomplus"), tr("Powiększ"),this);
    toolBar->addAction(act_zoom_plus);
    act_zoom_minus = new QAction(QIcon(":/zoomminus"), tr("Pommniejsz"),this);
    toolBar->addAction(act_zoom_minus);
    act_zoom_select = new QAction(QIcon(":/zoomselect"), tr("Powiększ do zaznaczenia"),this);
    toolBar->addAction(act_zoom_select);

}

void GeoWidget3D::slot_update_dane()
{
    wiev3d->wczytajObiekty();
    wiev3d->update_model();
    wiev3d->repaint();
}

void GeoWidget3D::slot_update_model()
{
    wiev3d->repaint();
}

void GeoWidget3D::slot_update_view()
{

}

void GeoWidget3D::slotZakres(int i)
{
    widok.zakres=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotDane(int i)
{
    widok.dane=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotSiatka(int i)
{
    widok.siatka=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotWezel(int i)
{
    widok.wezel=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slotZasoby(int i)
{
    widok.zasoby=i;
    emit signalUpdateView(widok);
}

void GeoWidget3D::slot_zoom_fit()
{
    wiev3d->set_zoom(75);
    wiev3d->repaint();
}

void GeoWidget3D::slot_punkt(wektor3d p)
{
    wiev3d->point(p);

}
