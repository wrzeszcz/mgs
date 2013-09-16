#ifndef GPRODIALOG_H
#define GPRODIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QGroupBox>
#include <QComboBox>
#include "globalne.h"
#include <QSpinBox>
//------------------------------------------------------------------------------
class GeoDoubleSpin: public QDoubleSpinBox
{
public:
    GeoDoubleSpin(double min, double max, int dec, double step, QWidget *parent=0):
        QDoubleSpinBox(parent)
    {
        this->setRange(min,max);
        this->setDecimals(dec);
        this->setSingleStep(step);
        this->setAlignment(Qt::AlignRight);
    }
};
//------------------------------------------------------------------------------
class GProDialog : public QDialog
{
    Q_OBJECT
public:
    GProDialog(Set_interpolacja, METODA, QWidget *parent = 0);
    Set_interpolacja get_set_interp();
    ~GProDialog();
signals:
    
public slots:
    void slot_promien(double);
    void slot_vario(int);
    void slot_nugget(double);
    void slot_sill(double);
    void slot_range(double);
    void slot_potega(double);
    void slot_min_otocz(int);
    void slot_max_otocz(int);

private:
    void update_all();

    void createLayout();
    void createLayoutAll();
    void createLayoutKri();
    void createLayoutInv();

    QVBoxLayout *mainLayout;

    QGroupBox *all_grup;
    QGroupBox *kri_grup;
    QGroupBox *inv_grup;

    QGridLayout *layoutAll;
    QGridLayout *layoutKri;
    QGridLayout *layoutInv;

    GeoDoubleSpin *sb_promien;
    GeoDoubleSpin *sb_nugget;
    GeoDoubleSpin *sb_sill;
    GeoDoubleSpin *sb_range;
    GeoDoubleSpin *sb_potega;
    QSpinBox *sb_min_otocz;
    QSpinBox *sb_max_otocz;

    QComboBox *combo_vario;

    QLabel *lab_pro;
    QLabel *lab_nug;
    QLabel *lab_sil;
    QLabel *lab_ran;
    QLabel *lab_met;
    QLabel *lab_pot;
    QLabel *lab_min;
    QLabel *lab_max;

    QDialogButtonBox *butBox;
    Set_interpolacja set_in;
    METODA metoda; 
};

#endif // GPRODIALOG_H
