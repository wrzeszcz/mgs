#ifndef PROSET_H
#define PROSET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QGroupBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>
#include "globalne.h"

///
/// \brief The GProSet class
///
class GProSet : public QWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GProSet
    /// \param parent
    ///
    explicit GProSet(QWidget *parent = 0);
    ///
    /// \brief GProSet
    /// \param ustawienia
    /// \param parent
    ///
    explicit GProSet(Mset  *ustawienia, QWidget *parent = 0);
    ///
    /// \brief setUstaw
    /// \param s
    ///
    void setUstaw(Mset *s){ustaw = s;slotUpdateSet();}
    ///
    /// \brief setZasoby
    /// \param z
    ///
    void setZasoby(wektor3d z);

signals:
    ///
    /// \brief signalZasoby
    ///
    void signalZasoby();
    ///
    /// \brief signalInterpol
    ///
    void signalInterpol();
    ///
    /// \brief signalUpdateModel
    ///
    void signalUpdateModel();
    
public slots:
    ///
    /// \brief slotUpdateSet
    ///
    void slotUpdateSet();
    ///
    /// \brief slotModel
    ///
    void slotModel();
    ///
    /// \brief slotCutOff
    /// \param d
    ///
    void slotCutOff(double d);
    ///
    /// \brief slotDimX
    /// \param i
    ///
    void slotDimX(int i);
    ///
    /// \brief slotDimY
    /// \param i
    ///
    void slotDimY(int i);
    ///
    /// \brief slotDimZ
    /// \param i
    ///
    void slotDimZ(int i);
    ///
    /// \brief slotDimS
    /// \param d
    ///
    void slotDimS(double d);
    ///
    /// \brief slotPoczX
    /// \param d
    ///
    void slotPoczX(double d);
    ///
    /// \brief slotPoczY
    /// \param d
    ///
    void slotPoczY(double d);
    ///
    /// \brief slotPoczZ
    /// \param d
    ///
    void slotPoczZ(double d);
    ///
    /// \brief slotGestosc
    /// \param d
    ///
    void slotGestosc(double d);

private:
    ///
    /// \brief ustaw
    ///
    Mset *ustaw;

    ///
    /// \brief zmiana_modelu
    ///
    void zmiana_modelu();
    ///
    /// \brief createLayout
    ///
    void createLayout();
    ///
    /// \brief createLayoutModel
    ///
    void createLayoutModel();
    ///
    /// \brief createLayoutZasoby
    ///
    void createLayoutZasoby();

    ///
    /// \brief layoutModel
    ///
    QGridLayout *layoutModel;
    ///
    /// \brief layoutZasoby
    ///
    QGridLayout *layoutZasoby;

    //obiekty model
    ///
    /// \brief sbDimX
    ///
    QSpinBox *sbDimX;
    ///
    /// \brief sbDimY
    ///
    QSpinBox *sbDimY;
    ///
    /// \brief sbDimZ
    ///
    QSpinBox *sbDimZ;
    ///
    /// \brief sbSpac
    ///
    QDoubleSpinBox *sbSpac;
    ///
    /// \brief sbPoczX
    ///
    QDoubleSpinBox *sbPoczX;
    ///
    /// \brief sbPoczY
    ///
    QDoubleSpinBox *sbPoczY;
    ///
    /// \brief sbPoczZ
    ///
    QDoubleSpinBox *sbPoczZ;
    ///
    /// \brief laBloki
    ///
    QLabel *laBloki;
    ///
    /// \brief laObjetosc
    ///
    QLabel *laObjetosc;
    ///
    /// \brief laMasa
    ///
    QLabel *laMasa;
    ///
    /// \brief sbGestosc
    ///
    QDoubleSpinBox *sbGestosc;

    //obiekty zasoby
    ///
    /// \brief labelCutOff
    ///
    QLabel *labelCutOff;
    ///
    /// \brief sbCutOff
    ///
    QDoubleSpinBox *sbCutOff;
    ///
    /// \brief laZasoby
    ///
    QLabel *laZasoby;
    ///
    /// \brief laZasobyBloki
    ///
    QLabel *laZasobyBloki;
    ///
    /// \brief laZasobyObjetosc
    ///
    QLabel *laZasobyObjetosc;
    ///
    /// \brief laZasobyMasa
    ///
    QLabel *laZasobyMasa;

    ///
    /// \brief policzBloki
    /// \return
    ///
    int policzBloki(){return ustaw->grid.x*ustaw->grid.y*ustaw->grid.z;}
    ///
    /// \brief policzObjet
    /// \param bloki
    /// \return
    ///
    double policzObjet(int bloki){return bloki*ustaw->sp*ustaw->sp*ustaw->sp;}
    ///
    /// \brief policz_masa
    /// \param bloki
    /// \return
    ///
    double policz_masa(int bloki){return policzObjet(bloki)*ustaw->gestosc;}
    ///
    /// \brief zasoby3d
    ///
    wektor3d zasoby3d;
};

#endif // PROSET_H
