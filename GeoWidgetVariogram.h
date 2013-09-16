#ifndef GEOWIDGETVARIOGRAM_H
#define GEOWIDGETVARIOGRAM_H

#include "GeoVariogram.h"
#include "GeoVariogramModel.h"
#include "GeoWidget.h"
#include "globalne.h"
#include <QAction>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include "GraphWidget.h"

class GeoWidgetVariogram: public GeoWidget
{
    Q_OBJECT
public:
    GeoWidgetVariogram(GeoModel *ptrModel, QWidget *parent = 0);
     ~GeoWidgetVariogram();

protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
protected slots:
    void slot_update_dane();
    void slot_vario(int);
    void slot_nugget(QString);
    void slot_sill(QString);
    void slot_range(QString);
    void slot_klasa(QString);
    void slot_kopuj_do();
    void slot_przelicz();
signals:

private:
    void create();
    void update_edit();

    GraphWidget *graph;
    GeoVariogram *curVar;
    //QList<QPointF> vpkty;
    QPoint mousePoz;
    QAction *actZapiszVariogram;
    QAction *actCopyToSet;
    QAction *act_przelicz;
    Set_interpolacja cur_set_vario;
    //std::vector<wektor3d> pkt;

    QLineEdit *le_nugget;
    QLineEdit *le_sill;
    QLineEdit *le_range;
    QLineEdit *le_klasa;

    QComboBox *combo_vario;

    QLabel *lab_nug;
    QLabel *lab_sil;
    QLabel *lab_ran;
    QLabel *lab_kla;
};

#endif // GEOWIDGETVARIOGRAM_H
