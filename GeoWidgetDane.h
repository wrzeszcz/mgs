#ifndef GEOWIDGETDANE_H
#define GEOWIDGETDANE_H

#include "GeoWidget.h"
#include <QStandardItemModel>
class QAction;
class QTableView;
///
/// \brief The GeoWidgetDane class
///
class GeoWidgetDane:public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidgetDane
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidgetDane(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidgetDane
    ///
    virtual ~GeoWidgetDane();

protected slots:
    ///
    /// \brief slot_update_dane
    ///
    void slot_update_dane();
    ///
    /// \brief slot_selected
    /// \param ind
    ///
    void slot_selected(QModelIndex ind);

signals:
    ///
    /// \brief signal_selected
    ///
    void signal_selected(wektor3d);

private:
    ///
    /// \brief create_view
    ///
    void create_view();
    ///
    /// \brief dane
    ///
    GeoDat *dane;
    ///
    /// \brief itemModel
    ///
    QStandardItemModel *itemModel;
    ///
    /// \brief tableView
    ///
    QTableView *tableView;
    ///
    /// \brief actZapiszDane
    ///
    QAction *actZapiszDane;
};

#endif // GEOWIDGETDANE_H
