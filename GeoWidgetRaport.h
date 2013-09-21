#ifndef GEOWIDGETRAPORT_H
#define GEOWIDGETRAPORT_H

#include "GeoWidget.h"
#include <QTextEdit>
#include <QAction>
///
/// \brief The GeoWidgetRaport class
///
class GeoWidgetRaport: public GeoWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GeoWidgetRaport
    /// \param ptrModel
    /// \param parent
    ///
    GeoWidgetRaport(GeoModel *ptrModel, QWidget *parent = 0);
    ///
    /// \brief ~GeoWidgetRaport
    ///
    virtual ~GeoWidgetRaport();
    ///
    /// \brief ptr_textEdit
    /// \return
    ///
    QTextEdit *ptr_textEdit(){return textEdit;}

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
    /// \brief slot_create_report
    ///
    void slot_create_report();

private:
    ///
    /// \brief create_text_edit
    ///
    void create_text_edit();
    ///
    /// \brief textEdit
    ///
    QTextEdit *textEdit;
    ///
    /// \brief actZapiszRaport
    ///
    QAction *actZapiszRaport;
    ///
    /// \brief actCreateRaport
    ///
    QAction *actCreateRaport;
};

#endif // GEOWIDGETRAPORT_H
