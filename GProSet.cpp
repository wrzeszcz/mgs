/*******************************************************************************
**  Copyright (C) 2013  Marek Wrzeszcz
**  mail: marek.wrzeszcz@hotmail.com
**
**  This file is part of the MGEOSTAT.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "GProSet.h"
//--------------------------------------------------------------------
GProSet::GProSet(QWidget *parent) :  QWidget(parent),
    isInitialized(false)
{
    ustaw = new Mset();
    createLayout();
    slotUpdateSet();
    isInitialized = true;
}
//--------------------------------------------------------------------
GProSet::GProSet(Mset  *ustawienia, QWidget *parent):
    QWidget(parent),
    ustaw(ustawienia),
    isInitialized(false)
{
    createLayout();
    slotUpdateSet();
    isInitialized = true;
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
    sbPoczX->setRange(-9999999.000,9999999.000);
    connect(sbPoczX,SIGNAL(valueChanged(double)),this,SLOT(slotPoczX(double)));

    sbPoczY = new QDoubleSpinBox(this);
    sbPoczY->setAlignment(Qt::AlignRight);
    sbPoczY->setDecimals(3);
    sbPoczY->setRange(-9999999.000,9999999.000);
    connect(sbPoczY,SIGNAL(valueChanged(double)),this,SLOT(slotPoczY(double)));

    sbPoczZ = new QDoubleSpinBox(this);
    sbPoczZ->setAlignment(Qt::AlignRight);
    sbPoczZ->setDecimals(3);
    sbPoczZ->setRange(-9999999.000,9999999.000);
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

    buttonZatw = new QPushButton(this);
    buttonZatw->setText(tr("ZATWIERDŹ"));
    buttonZatw->setVisible(false);
    connect(buttonZatw, SIGNAL(clicked()), this, SLOT(slotButtZatw()));
    buttonAnul = new QPushButton(this);
    buttonAnul->setText(tr("ANULUJ"));
    buttonAnul->setVisible(false);
    connect(buttonAnul, SIGNAL(clicked()), this, SLOT(slotButtAnul()));

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

    layoutModel->addWidget(buttonAnul,11,0);
    layoutModel->addWidget(buttonZatw,11,1);
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
    if(!isInitialized)return;
    buttonAnul->setVisible(true);
    buttonZatw->setVisible(true);
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
    if(ustaw->grid.x!=i) zmiana_modelu();
}

void GProSet::slotDimY(int i)
{
    if(ustaw->grid.y!=i) zmiana_modelu();
}

void GProSet::slotDimZ(int i)
{
    if(ustaw->grid.z!=i) zmiana_modelu();
}

void GProSet::slotDimS(double d)
{
    if (ustaw->sp!=d) zmiana_modelu();
}

void GProSet::slotPoczX(double d)
{
    if (ustaw->start.x!=d) zmiana_modelu();
}

void GProSet::slotPoczY(double d)
{
   if( ustaw->start.y!=d ) zmiana_modelu();
}

void GProSet::slotPoczZ(double d)
{
   if( ustaw->start.z!=d ) zmiana_modelu();
}

void GProSet::slotGestosc(double d)
{
    ustaw->gestosc=d;
    emit signalZasoby();
    slotUpdateSet();
}

void GProSet::slotButtZatw()
{
    buttonZatw->setVisible(false);
    buttonAnul->setVisible(false);

    ustaw->grid.x = sbDimX->value();
    ustaw->grid.y = sbDimY->value();
    ustaw->grid.z = sbDimZ->value();

    ustaw->sp = sbSpac->value();

    ustaw->start.x = sbPoczX->value();
    ustaw->start.y = sbPoczY->value();
    ustaw->start.z = sbPoczZ->value();

    emit signalUpdateModel();
    emit signalZasoby();
    slotUpdateSet();
}

void GProSet::slotButtAnul()
{
    buttonAnul->setVisible(false);
    buttonZatw->setVisible(false);
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

void GProSet::updateView()
{
    isInitialized=false;
    slotUpdateSet();
    isInitialized=true;
}
