#ifndef GEOWIDGETDANE_H
#define GEOWIDGETDANE_H

#include "GeoWidget.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QAction>

class GeoWidgetDane:public GeoWidget
{
    Q_OBJECT
public:
    GeoWidgetDane(GeoModel *ptrModel, QWidget *parent = 0);
    ~GeoWidgetDane();
protected slots:
    void slot_update_dane();
    void slot_selected(QModelIndex ind);
signals:
    void signal_selected(wektor3d);

private:
    void create_view();

    GeoDat *dane;
    QStandardItemModel *itemModel;
    QTableView *tableView;

    QAction *actZapiszDane;
};

#endif // GEOWIDGETDANE_H
