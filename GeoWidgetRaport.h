#ifndef GEOWIDGETRAPORT_H
#define GEOWIDGETRAPORT_H

#include "GeoWidget.h"
#include <QTextEdit>
#include <QAction>

class GeoWidgetRaport: public GeoWidget
{
    Q_OBJECT
public:
    GeoWidgetRaport(GeoModel *ptrModel, QWidget *parent = 0);
    ~GeoWidgetRaport();

    QTextEdit *ptr_textEdit(){return textEdit;}

protected slots:
    void slot_update_dane();
    void slot_update_model();


private:
    void create_text_edit();

    QTextEdit *textEdit;

    QAction *actZapiszRaport;

};

#endif // GEOWIDGETRAPORT_H
