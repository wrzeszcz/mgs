#ifndef GEOWIDGET2D_H
#define GEOWIDGET2D_H

#include "GeoWidget.h"
#include "GLWidget2D.h"
#include "globalne.h"

class QCheckBox;
class QSlider;
///
/// \brief The GeoWidget2D class
///
class GeoWidget2D : public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidget2D
    /// \param ptrModel
    /// \param parent
    ///
    explicit GeoWidget2D(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidget2D
    ///
    virtual ~GeoWidget2D();

protected:
    ///
    /// \brief create_toolbar
    ///
    void create_toolbar();
    ///
    /// \brief create_slider
    ///
    void create_slider();

signals:
    ///
    /// \brief signalUpdateView
    ///
    void signalUpdateView(Vset);

protected slots:
    ///
    /// \brief slot_update_dane
    ///
    void slot_update_dane();
    ///
    /// \brief slot_update_model
    ///
    void slot_update_model();
    ///
    /// \brief slotZakres
    /// \param i
    ///
    void slotZakres(int i);
    ///
    /// \brief slotDane
    /// \param i
    ///
    void slotDane(int i);
    ///
    /// \brief slotSiatka
    /// \param i
    ///
    void slotSiatka(int i);
    ///
    /// \brief slotWezel
    /// \param i
    ///
    void slotWezel(int i);
    ///
    /// \brief slotZasoby
    /// \param i
    ///
    void slotZasoby(int i);
    ///
    /// \brief slot_zoom_fit
    ///
    void slot_zoom_fit();
    ///
    /// \brief slot_zoom_in
    ///
    void slot_zoom_in();
    ///
    /// \brief slot_zoom_out
    ///
    void slot_zoom_out();
    ///
    /// \brief slot_slider_z
    /// \param i
    ///
    void slot_slider_z(int i);
    ///
    /// \brief slot_punkt
    ///
    void slot_punkt(wektor3d);

private:
    ///
    /// \brief wiev2d
    ///
    GLWidget2D *wiev2d;
    ///
    /// \brief sliderZ
    ///
    QSlider   *sliderZ;
    ///
    /// \brief cbZakres
    ///
    QCheckBox *cbZakres;
    ///
    /// \brief cbDane
    ///
    QCheckBox *cbDane;
    ///
    /// \brief cbSiatka
    ///
    QCheckBox *cbSiatka;
    ///
    /// \brief cbWezel
    ///
    QCheckBox *cbWezel;
    ///
    /// \brief cbZasoby
    ///
    QCheckBox *cbZasoby;
    ///
    /// \brief cbPerspektywa
    ///
    QCheckBox *cbPerspektywa;
    ///
    /// \brief act_zoom_fit
    ///
    QAction *act_zoom_fit;
    ///
    /// \brief act_zoom_plus
    ///
    QAction *act_zoom_plus;
    ///
    /// \brief act_zoom_minus
    ///
    QAction *act_zoom_minus;
    ///
    /// \brief act_zoom_select
    ///
    QAction *act_zoom_select;
    ///
    /// \brief widok
    ///
    Vset widok;
};

#endif // GEOWIDGET2D_H
