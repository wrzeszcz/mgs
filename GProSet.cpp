#include "GProSet.h"
//--------------------------------------------------------------------
GProSet::GProSet(QWidget *parent) :  QWidget(parent)
{
    ustaw = new Mset();
    createLayout();
    slotUpdateSet();
}
//--------------------------------------------------------------------
GProSet::GProSet(Mset  *ustawienia, QWidget *parent):
    QWidget(parent),
    ustaw(ustawienia)
{
    createLayout();
    slotUpdateSet();
}
//--------------------------------------------------------------------
void GProSet::createLayout()
{
    QVBoxLayout   *mainLayout = new QVBoxLayout;
    QGroupBox  *modelGroupBox = new QGroupBox(tr("MODEL"));
    QGroupBox *zasobyGroupBox = new QGroupBox(tr("ZASOBY"));

    createLayoutModel();
    modelGroupBox->setLayout(layoutModel);
    createLayoutZasoby();
    zasobyGroupBox->setLayout(layoutZasoby);

    mainLayout->addWidget(modelGroupBox);
    mainLayout->addWidget(zasobyGroupBox);
    this->setLayout(mainLayout);
}
//--------------------------------------------------------------------
void GProSet::createLayoutModel()
{
    sbDimX = new QSpinBox(this);
    sbDimX->setAlignment(Qt::AlignRight);
    sbDimX->setRange(0,1000);
    connect(sbDimX,SIGNAL(valueChanged(int)),this,SLOT(slotDimX(int)));

    sbDimY = new QSpinBox(this);
    sbDimY->setAlignment(Qt::AlignRight);
    sbDimY->setRange(0,1000);
    connect(sbDimY,SIGNAL(valueChanged(int)),this,SLOT(slotDimY(int)));

    sbDimZ = new QSpinBox(this);
    sbDimZ->setAlignment(Qt::AlignRight);
    sbDimZ->setRange(0,1000);
    connect(sbDimZ,SIGNAL(valueChanged(int)),this,SLOT(slotDimZ(int)));

    sbSpac = new QDoubleSpinBox(this);
    sbSpac->setAlignment(Qt::AlignRight);
    sbSpac->setDecimals(3);
    sbSpac->setRange(0.000,999999.000);
    connect(sbSpac,SIGNAL(valueChanged(double)),this,SLOT(slotDimS(double)));

    sbPoczX = new QDoubleSpinBox(this);
    sbPoczX->setAlignment(Qt::AlignRight);
    sbPoczX->setDecimals(3);
    sbPoczX->setRange(-999999.000,999999.000);
    connect(sbPoczX,SIGNAL(valueChanged(double)),this,SLOT(slotPoczX(double)));

    sbPoczY = new QDoubleSpinBox(this);
    sbPoczY->setAlignment(Qt::AlignRight);
    sbPoczY->setDecimals(3);
    sbPoczY->setRange(-999999.000,999999.000);
    connect(sbPoczY,SIGNAL(valueChanged(double)),this,SLOT(slotPoczY(double)));

    sbPoczZ = new QDoubleSpinBox(this);
    sbPoczZ->setAlignment(Qt::AlignRight);
    sbPoczZ->setDecimals(3);
    sbPoczZ->setRange(-999999.000,999999.000);
    connect(sbPoczZ,SIGNAL(valueChanged(double)),this,SLOT(slotPoczZ(double)));

    sbGestosc = new QDoubleSpinBox(this);
    sbGestosc->setAlignment(Qt::AlignRight);
    sbGestosc->setDecimals(3);
    sbGestosc->setRange(0.000,999999.000);
    connect(sbGestosc,SIGNAL(valueChanged(double)),this,SLOT(slotGestosc(double)));

    laBloki=new QLabel();
    laBloki->setAlignment(Qt::AlignRight);
    laObjetosc = new QLabel();
    laObjetosc->setAlignment(Qt::AlignRight);
    laMasa = new QLabel();
    laMasa->setAlignment(Qt::AlignRight);

    layoutModel = new QGridLayout();
    layoutModel->addWidget(new QLabel("BLOKI X",this),0,0);
    layoutModel->addWidget(sbDimX,0,1);
    layoutModel->addWidget(new QLabel("BLOKI Y",this),1,0);
    layoutModel->addWidget(sbDimY,1,1);
    layoutModel->addWidget(new QLabel("BLOKI Z",this),2,0);
    layoutModel->addWidget(sbDimZ,2,1);
    layoutModel->addWidget(new QLabel("ROZMIAR",this),3,0);
    layoutModel->addWidget(sbSpac,3,1);
    layoutModel->addWidget(new QLabel("POCZ X",this),4,0);
    layoutModel->addWidget(sbPoczX,4,1);
    layoutModel->addWidget(new QLabel("POCZ Y",this),5,0);
    layoutModel->addWidget(sbPoczY,5,1);
    layoutModel->addWidget(new QLabel("POCZ Z",this),6,0);
    layoutModel->addWidget(sbPoczZ,6,1);
    layoutModel->addWidget(new QLabel("BLOKI",this),7,0);
    layoutModel->addWidget(laBloki,7,1);
    layoutModel->addWidget(new QLabel("OBJĘTOŚĆ",this),8,0);
    layoutModel->addWidget(laObjetosc,8,1);
    layoutModel->addWidget(new QLabel("GĘSTOŚĆ",this),9,0);
    layoutModel->addWidget(sbGestosc,9,1);
    layoutModel->addWidget(new QLabel("MASA",this),10,0);
    layoutModel->addWidget(laMasa,10,1);
    layoutModel->setAlignment(Qt::AlignTop);
}
//--------------------------------------------------------------------
void GProSet::createLayoutZasoby()
{
     labelCutOff = new QLabel ("CUT OFF",this);
     sbCutOff= new QDoubleSpinBox(this);
     sbCutOff->setAlignment(Qt::AlignRight);
     sbCutOff->setDecimals(3);
     sbCutOff->setRange(0.000,999999.000);
     sbCutOff->setSingleStep(0.01);

    connect(sbCutOff,SIGNAL(valueChanged(double)),this,SLOT(slotCutOff(double)));
    laZasoby = new QLabel("",this);
    laZasoby->setAlignment(Qt::AlignRight);
    laZasobyBloki = new QLabel("",this);
    laZasobyBloki->setAlignment(Qt::AlignRight);
    laZasobyObjetosc = new QLabel("",this);
    laZasobyObjetosc->setAlignment(Qt::AlignRight);
    laZasobyMasa = new QLabel("",this);
    laZasobyMasa->setAlignment(Qt::AlignRight);

    layoutZasoby = new QGridLayout();
    layoutZasoby->addWidget(labelCutOff,0,0);
    layoutZasoby->addWidget(sbCutOff,0,1);
    layoutZasoby->addWidget(new QLabel("ZASOBY",this),2,0);
    layoutZasoby->addWidget(laZasoby,2,1);
    layoutZasoby->addWidget(new QLabel("BLOKI",this),3,0);
    layoutZasoby->addWidget(laZasobyBloki,3,1);
    layoutZasoby->addWidget(new QLabel("OBJĘTOŚĆ",this),4,0);
    layoutZasoby->addWidget(laZasobyObjetosc,4,1);
    layoutZasoby->addWidget(new QLabel("MASA",this),5,0);
    layoutZasoby->addWidget(laZasobyMasa,5,1);
    layoutZasoby->setAlignment(Qt::AlignTop);
}
//--------------------------------------------------------------------
void GProSet::zmiana_modelu()
{
    emit signalUpdateModel();
    emit signalZasoby();
    slotUpdateSet();
}
//--------------------------------------------------------------------
void GProSet::slotCutOff(double d)
{
   ustaw->cutoff=d;
   emit signalZasoby();
}
//--------------------------------------------------------------------
void GProSet::slotModel()
{

}
//--------------------------------------------------------------------
void GProSet::slotDimX(int i)
{
    ustaw->grid.x=i;
    zmiana_modelu();
}

void GProSet::slotDimY(int i)
{
    ustaw->grid.y=i;
    zmiana_modelu();
}

void GProSet::slotDimZ(int i)
{
    ustaw->grid.z=i;
    zmiana_modelu();
}

void GProSet::slotDimS(double d)
{
    ustaw->sp=d;
    zmiana_modelu();
}

void GProSet::slotPoczX(double d)
{
    ustaw->start.x=d;
    zmiana_modelu();
}

void GProSet::slotPoczY(double d)
{
    ustaw->start.y=d;
    zmiana_modelu();
}

void GProSet::slotPoczZ(double d)
{
    ustaw->start.z=d;
    zmiana_modelu();
}

void GProSet::slotGestosc(double d)
{
    ustaw->gestosc=d;
    emit signalZasoby();
    slotUpdateSet();
}

void GProSet::slotUpdateSet()
{
    sbDimX->setValue(ustaw->grid.x);
    sbDimY->setValue(ustaw->grid.y);
    sbDimZ->setValue(ustaw->grid.z);
    sbSpac->setValue(ustaw->sp);
    sbPoczX->setValue(ustaw->start.x);
    sbPoczY->setValue(ustaw->start.y);
    sbPoczZ->setValue(ustaw->start.z);
    laBloki->setText(QString::number(policzBloki()));
    laObjetosc->setText(QString::number(policzObjet(policzBloki())));
    sbGestosc->setValue(ustaw->gestosc);
    laMasa->setText(QString::number(policz_masa(policzBloki())));

    sbCutOff->setValue(ustaw->cutoff);
    laZasoby->setText(QString::number(zasoby3d.x));
    laZasobyBloki->setText(QString::number(zasoby3d.y));
    laZasobyObjetosc->setText(QString::number(policzObjet(zasoby3d.y)));
    laZasobyMasa->setText(QString::number(policz_masa(zasoby3d.y)));
}
void GProSet::setZasoby(wektor3d z)
{
    zasoby3d=z;
    laZasoby->setText(QString::number(zasoby3d.x));
    laZasobyBloki->setText(QString::number(zasoby3d.y));
    laZasobyObjetosc->setText(QString::number(policzObjet(zasoby3d.y)));
    laZasobyMasa->setText(QString::number(policz_masa(zasoby3d.y)));
}
