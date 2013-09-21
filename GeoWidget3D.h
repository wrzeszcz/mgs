#ifndef GEOWIDGET3D_H
#define GEOWIDGET3D_H

#include "GeoWidget.h"
#include "GLWidget3D.h"
#include "globalne.h"

class QCheckBox;
///
/// \brief The GeoWidget3D class
///
class GeoWidget3D: public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidget3D
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidget3D(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidget3D
    ///
    virtual ~GeoWidget3D();

protected:
    ///
    /// \brief create_toolbar
    ///
    void create_toolbar();

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
    /// \brief slot_update_view
    ///
    void slot_update_view();
    ///
    /// \brief slotZakres
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
    /// \brief slot_punkt
    ///
    void slot_punkt(wektor3d);

private:
    ///
    /// \brief wiev3d
    ///
    GLWidget3D *wiev3d;
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

#endif // GEOWIDGET3D_H
