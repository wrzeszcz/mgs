#ifndef GEOWIDGET3D_H
#define GEOWIDGET3D_H

#include "GeoWidget.h"
#include "GLWidget3D.h"
#include "globalne.h"

class QCheckBox;

class GeoWidget3D: public GeoWidget
{
    Q_OBJECT
public:
    GeoWidget3D(GeoModel *ptrModel, QWidget *parent = 0);
    ~GeoWidget3D();
protected:
    void create_toolbar();

signals:
    void signalUpdateView(Vset);

protected slots:
    void slot_update_dane();
    void slot_update_model();
    void slot_update_view();
    void slotZakres(int);
    void slotDane(int);
    void slotSiatka(int);
    void slotWezel(int);
    void slotZasoby(int);
    void slot_zoom_fit();
    void slot_punkt(wektor3d);

private:


    GLWidget3D *wiev3d;

    QCheckBox *cbZakres;
    QCheckBox *cbDane;
    QCheckBox *cbSiatka;
    QCheckBox *cbWezel;
    QCheckBox *cbZasoby;
    QCheckBox *cbPerspektywa;
    QAction *act_zoom_fit;
    QAction *act_zoom_plus;
    QAction *act_zoom_minus;
    QAction *act_zoom_select;
    Vset widok;
};

#endif // GEOWIDGET3D_H
