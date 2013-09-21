#ifndef GEOWIDGET_H
#define GEOWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include "GeoModel.h"
///
/// \brief The GeoWidget class
///
class GeoWidget : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidget
    /// \param parent
    ///
    GeoWidget(QWidget *parent = 0);
    ///
    /// \brief GeoWidget
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidget(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidget
    ///
    virtual ~GeoWidget();
    ///
    /// \brief set_model
    /// \param model
    ///
    void set_model(GeoModel *model){gModel = model;}
    ///
    /// \brief get_model
    /// \return
    ///
    GeoModel *get_model(){return gModel;}
    
public slots:
    ///
    /// \brief slot_update_dane
    ///
    virtual void slot_update_dane();
    ///
    /// \brief slot_update_view
    ///
    virtual void slot_update_view();
    ///
    /// \brief slot_update_model
    ///
    virtual void slot_update_model();

protected:
    ///
    /// \brief gModel
    ///
    GeoModel *gModel;
    ///
    /// \brief toolBar
    ///
    QToolBar *toolBar;
    ///
    /// \brief boxLayout
    ///
    QVBoxLayout *boxLayout;

private:
    void create_widget();
};

#endif // GEOWIDGET_H
