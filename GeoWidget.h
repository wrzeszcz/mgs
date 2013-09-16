#ifndef GEOWIDGET_H
#define GEOWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include "GeoModel.h"

class GeoWidget : public QWidget
{
    Q_OBJECT
public:
    GeoWidget(QWidget *parent = 0);
    GeoWidget(GeoModel *ptrModel, QWidget *parent = 0);

    virtual ~GeoWidget();

    void set_model(GeoModel *model){gModel = model;}
    GeoModel *get_model(){return gModel;}
    
signals:
    
public slots:
    virtual void slot_update_dane();
    virtual void slot_update_view();
    virtual void slot_update_model();

protected:
    GeoModel *gModel;
    QToolBar *toolBar;
    QVBoxLayout *boxLayout;

private:
    void create_widget();
};

#endif // GEOWIDGET_H
