#ifndef GEOWIDGET2D_H
#define GEOWIDGET2D_H

#include "GeoWidget.h"
#include "GLWidget2D.h"
#include "globalne.h"

class QCheckBox;
class QSlider;

class GeoWidget2D : public GeoWidget
{
    Q_OBJECT
public:
    explicit GeoWidget2D(GeoModel *ptrModel, QWidget *parent = 0);
    ~GeoWidget2D();

protected:
    void create_toolbar();
    void create_slider();

signals:
    void signalUpdateView(Vset);

protected slots:
    void slot_update_dane();
    void slot_update_model();

    void slotZakres(int);
    void slotDane(int);
    void slotSiatka(int);
    void slotWezel(int);
    void slotZasoby(int);
    void slot_zoom_fit();
    void slot_zoom_in();
    void slot_zoom_out();
    void slot_slider_z(int);
    void slot_punkt(wektor3d);

private:
    GLWidget2D *wiev2d;

    QSlider   *sliderZ;
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

#endif // GEOWIDGET2D_H
