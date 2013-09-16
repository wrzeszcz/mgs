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


class GProSet : public QWidget
{
    Q_OBJECT
public:
    explicit GProSet(QWidget *parent = 0);
    explicit GProSet(Mset  *ustawienia, QWidget *parent = 0);

    void setUstaw(Mset *s){ustaw = s;slotUpdateSet();}
    void setZasoby(wektor3d z);

signals:
    void signalZasoby();
    void signalInterpol();
    void signalUpdateModel();
    
public slots:
    void slotUpdateSet();
    void slotModel();
    void slotCutOff(double);

    void slotDimX(int);
    void slotDimY(int);
    void slotDimZ(int);
    void slotDimS(double);
    void slotPoczX(double);
    void slotPoczY(double);
    void slotPoczZ(double);
    void slotGestosc(double);

private:
    Mset *ustaw;

    void zmiana_modelu();
    void createLayout();
    void createLayoutModel();
    void createLayoutZasoby();

    QString s;

    QGridLayout *layoutModel;
    QGridLayout *layoutZasoby;

    //obiekty model
    QSpinBox *sbDimX;
    QSpinBox *sbDimY;
    QSpinBox *sbDimZ;
    QDoubleSpinBox *sbSpac;
    QDoubleSpinBox *sbPoczX;
    QDoubleSpinBox *sbPoczY;
    QDoubleSpinBox *sbPoczZ;
    QLabel *laBloki;
    QLabel *laObjetosc;
    QLabel *laMasa;
    QDoubleSpinBox *sbGestosc;

    //obiekty zasoby
    QLabel *labelCutOff;
    QDoubleSpinBox *sbCutOff;

    QLabel *laZasoby;
    QLabel *laZasobyBloki;
    QLabel *laZasobyObjetosc;
    QLabel *laZasobyMasa;

    int policzBloki(){return ustaw->grid.x*ustaw->grid.y*ustaw->grid.z;}
    double policzObjet(int bloki){return bloki*ustaw->sp*ustaw->sp*ustaw->sp;}
    double policz_masa(int bloki){return policzObjet(bloki)*ustaw->gestosc;}
    wektor3d zasoby3d;
};

#endif // PROSET_H
