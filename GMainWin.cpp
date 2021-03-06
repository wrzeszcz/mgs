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

#include "GMainWin.h"
#include "GeoWidgetDane.h"
#include "GeoWidgetRaport.h"
#include "GeoWidgetVariogram.h"
#include "GeoWidget2D.h"
#include "GeoWidget3D.h"
#include "GProAnaliza.h"

#include <QMenuBar>
#include <QMenu>
#include <QSettings>
#include <QProgressBar>
#include <QSettings>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QPrinter>
#include <QtConcurrentRun>
#include <boost/bind.hpp>

//------------------------------------------------------------------------------
GMainWin::GMainWin(QWidget *parent) :
    QMainWindow(parent),
    curModel(0)
{
    mdiArea = new QMdiArea(this);

    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    createDockWin();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    updateMenus();
    resize(900,600);
    readSettings();

    projFile = "NIE ZAPISANY";
    setWindowIcon(QIcon(":/geostat"));
    setWindowTitle(APPNAME + " - " + projFile);
    createEmptyModel();
    QString mes = "Start "+QDateTime::currentDateTime().toString() + "\n";
    curModel->raport_add(mes.toStdString());

    progresTimer = new QTimer(this);
    connect(progresTimer, SIGNAL(timeout()), this, SLOT(slot_progres()));
    connect(&watcher, SIGNAL(finished()), this, SLOT(slot_calc_end()));
}
//------------------------------------------------------------------------------
GMainWin::~GMainWin()
{
    if(curModel) delete curModel;
}
//------------------------------------------------------------------------------
void GMainWin::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow()) event->ignore();
    else
    {
        writeSettings();
        event->accept();
    }
}
//------------------------------------------------------------------------------
void GMainWin::createDockWin()
{
    dockTree = new QDockWidget(tr("Projekt"),this);
    dockTree->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    proTree = new GProTree();  
    dockTree->setWidget(proTree);
    addDockWidget(Qt::LeftDockWidgetArea, dockTree);
    connect(proTree,SIGNAL(signal_open_win(QString)),
               this,SLOT(slot_open_win(QString)));

    dockSet = new QDockWidget(tr("Ustawienia"), this);
    dockSet->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    proSet = new GProSet();
    dockSet->setWidget(proSet);
    addDockWidget(Qt::LeftDockWidgetArea, dockSet);
    connect(proSet,SIGNAL(signalZasoby()),this,SLOT(slot_zasoby()));
    connect(proSet,SIGNAL(signalUpdateModel()),this,SLOT(slot_reset_model()));
    connect(proSet, SIGNAL(signalNeedRepaint()),this, SLOT(slot_repaint()));
}
//------------------------------------------------------------------------------
void GMainWin::createActions()
{
    //--------------------------------------------------------------------------
    actionNew = new QAction(QIcon(":/nowy"), tr("&Nowy projekt"), this);
    actionNew->setShortcut(QKeySequence::New);
    actionNew->setStatusTip(tr("Nowy pusty projekt"));
    connect(actionNew, SIGNAL(triggered()), this, SLOT(slot_nowy_proj()));

    actionOpen = new QAction(QIcon(":/open"), tr("&Otwórz projekt"), this);
    actionOpen->setShortcut(QKeySequence::Open);
    actionOpen->setStatusTip(tr("Otwórz projekt"));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(slot_open_proj()));

    actionSave = new QAction(QIcon(":/save"), tr("&Zapisz projekt"), this);
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setStatusTip(tr("Zapisz projekt"));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(slot_save_proj()));

    actionSaveAs = new QAction(QIcon(":/save_as"),tr("Zapisz &Jako"), this);
    actionSaveAs->setShortcut(QKeySequence::SaveAs);
    actionSaveAs->setStatusTip(tr("Zapisz projekt jako ..."));
    connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(slot_save_proj_as()));

    actionExit = new QAction(QIcon(":/exit"),tr("Wyjście"), this);
    actionExit->setShortcut(QKeySequence::Quit);
    actionExit->setStatusTip(tr("Koniec pracy"));
    connect(actionExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));

    //--------------------------------------------------------------------------

    actionOpenData = new QAction(QIcon(":/open_dat"), tr("Wczytaj dane"), this);
    actionOpenData->setShortcut(Qt::CTRL + Qt::Key_D);
    actionOpenData->setStatusTip(tr("Wczytuje dane z pliku tekstowego"));
    connect(actionOpenData, SIGNAL(triggered()), this, SLOT(slot_wczytaj_dane()));

    actionOpenModel = new QAction(QIcon(":/open_dat"), tr("Wczytaj model"), this);
    actionOpenModel->setShortcut(Qt::CTRL + Qt::Key_M);
    actionOpenModel->setStatusTip(tr("Wczytuje model z pliku"));
    connect(actionOpenModel, SIGNAL(triggered()), this, SLOT(slot_wczytaj_model()));

    actionOpenSurf = new QAction(QIcon(":/open_dat"), tr("Wczytaj powierzchnię"),this);
    actionOpenSurf->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(actionOpenSurf, SIGNAL(triggered()), this, SLOT(slot_wczytaj_surf()));

    actionZapiszDane = new QAction(QIcon(":/save"), tr("Zapisz dane"),this);
    connect(actionZapiszDane,SIGNAL(triggered()), this, SLOT(slot_zapis_dane()));

    actionZapiszModel = new QAction(QIcon(":/save"), tr("Zapisz model"),this);
    connect(actionZapiszModel,SIGNAL(triggered()), this, SLOT(slot_zapis_model()));

    actionZapiszZasoby = new QAction(QIcon(":/save"), tr("Zapisz zasoby"),this);
    connect(actionZapiszZasoby,SIGNAL(triggered()), this, SLOT(slot_zapis_zasoby()));

    actionZapiszRaport = new QAction(QIcon(":/save_report"), tr("Zapisz raport"),this);
    connect(actionZapiszRaport,SIGNAL(triggered()), this, SLOT(slot_zapis_raport()));

    actionZapiszVariogram = new QAction(QIcon(":/save"), tr("Zapisz wariogram"),this);
    connect(actionZapiszVariogram,SIGNAL(triggered()), this, SLOT(slot_zapis_variogram()));

    //--------------------------------------------------------------------------

    action_invdist = new QAction(QIcon(":/grid"),tr("odwrotne odległości"),this);
    action_invdist->setStatusTip(tr("odwrotne odległości"));
    connect(action_invdist,SIGNAL(triggered()),this,SLOT(slot_invdist()));

    action_okriging = new QAction(QIcon(":/krige"),tr("kriging zwykły"),this);
    action_okriging->setStatusTip(tr("ordinary kriging"));
    connect(action_okriging,SIGNAL(triggered()),this,SLOT(slot_okriging()));

    action_variogram = new QAction(QIcon(":/vario"),tr("semiwariogram empiryczny"),this);
    action_variogram->setStatusTip(tr("semiwariogram empiryczny"));
    connect(action_variogram,SIGNAL(triggered()),this,SLOT(slot_variogram()));

    //--------------------------------------------------------------------------

    actionZasoby = new QAction(QIcon(":/zasoby"),tr("Przelicz"),this);
    actionZasoby->setStatusTip(tr("Liczenie zasobów"));
    connect(actionZasoby,SIGNAL(triggered()),this,SLOT(slot_zasoby()));

    actionAnaliza = new QAction(QIcon(":/analiza"),tr("Analiza"),this);
    actionAnaliza->setStatusTip(tr("Analiza wyników"));
    connect(actionAnaliza,SIGNAL(triggered()),this,SLOT(slot_analiza()));

    //--------------------------------------------------------------------------

    actionToolSend = new QAction(QIcon(":/email"),tr("Wyślij wyniki"),this);
    connect(actionToolSend,SIGNAL(triggered()),this,SLOT(slot_tool_send()));

    actionToolPdf = new QAction(QIcon(":/pdf"),tr("Raport PDF"),this);
    connect(actionToolPdf,SIGNAL(triggered()),this,SLOT(slot_tool_pdf()));

    //--------------------------------------------------------------------------

    actZamk = new QAction(QIcon(":/close"),tr("Zamknij okno"), this);
    actZamk->setStatusTip(tr("Zamknij aktywne okno"));
    connect(actZamk, SIGNAL(triggered()),mdiArea, SLOT(closeActiveSubWindow()));

    actZamkAll = new QAction(tr("Zamknij wszystkie"), this);
    actZamkAll->setStatusTip(tr("Zamknij wszystkie okna"));
    connect(actZamkAll,SIGNAL(triggered()),mdiArea,SLOT(closeAllSubWindows()));

    actTile = new QAction(QIcon(":/tile"),tr("Tile"), this);
    actTile->setStatusTip(tr("Tile"));
    connect(actZamkAll,SIGNAL(triggered()),mdiArea,SLOT(tileSubWindows()));

    actCascade = new QAction(QIcon(":/cascade"),tr("Kaskada"), this);
    actCascade->setStatusTip(tr("Kaskada"));
    connect(actCascade,SIGNAL(triggered()),mdiArea,SLOT(cascadeSubWindows()));

    actNext = new QAction(QIcon(":/next"),tr("Kolejne okno"), this);
    actNext->setShortcuts(QKeySequence::NextChild);
    actNext->setStatusTip(tr("Uaktywnij kolejne okno"));
    connect(actNext,SIGNAL(triggered()),mdiArea,SLOT(activateNextSubWindow()));

    actPrev = new QAction(QIcon(":/prev"),tr("Poprzednie okno"), this);
    actPrev->setShortcuts(QKeySequence::PreviousChild);
    actPrev->setStatusTip(tr("Uaktywnij poprzenie okno"));
    connect(actPrev,SIGNAL(triggered()),mdiArea,SLOT(activatePreviousSubWindow()));

    actTabbed = new QAction(tr("Widok zkładek"), this);
    actTabbed->setCheckable(true);
    connect(actTabbed,SIGNAL(triggered()),this,SLOT(slot_tabbed()));

    //--------------------------------------------------------------------------

    actionAbout = new QAction(QIcon(":/mw"), tr("&O programie"), this);
    actionAbout->setStatusTip(tr("O programie"));
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(slot_about()));

    actionHelp = new QAction(QIcon(":/instr"), tr("&Instrukcja"), this);
    actionHelp->setStatusTip(tr("Krótka instrukcja obsługi"));
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(slot_instrukcja()));
}
//------------------------------------------------------------------------------
void GMainWin::createMenus()
{
    menuProj = menuBar()->addMenu(tr("&Projekt"));
    menuProj->addAction(actionNew);
    menuProj->addAction(actionOpen);
    menuProj->addAction(actionSave);
    menuProj->addAction(actionSaveAs);
    menuProj->addSeparator();
    menuProj->addAction(actionExit);

    menuData= menuBar()->addMenu(tr("&Dane"));
    subMenuOpen = menuData->addMenu(QIcon(":/open_dat"),"Wczytaj");
    subMenuOpen->addAction(actionOpenData);
    subMenuOpen->addAction(actionOpenModel);
    //subMenuOpen->addAction(actionOpenSurf);
    subMenuSave = menuData->addMenu(QIcon(":/save"),"Zapisz");
    subMenuSave->addAction(actionZapiszDane);
    subMenuSave->addAction(actionZapiszModel);
    subMenuSave->addAction(actionZapiszZasoby);
    subMenuSave->addAction(actionZapiszRaport);
    subMenuSave->addAction(actionZapiszVariogram);

    menuInterp = menuBar()->addMenu(tr("&Interpolacja"));
    menuInterp->addAction(action_invdist);
    menuInterp->addAction(action_okriging);
    menuInterp->addSeparator();
    menuInterp->addAction(action_variogram);

    menuZasoby = menuBar()->addMenu("&Zasoby");
    menuZasoby->addAction(actionZasoby);
    menuZasoby->addAction(actionAnaliza);

    menuTools = menuBar()->addMenu(tr("&Narzędzia"));
    //menuTools->addAction(actionToolSend);
    menuTools->addAction(actionToolPdf);

    menuWindow = menuBar()->addMenu(tr("&Widok"));
    menuWindow->addAction(actZamk);
    menuWindow->addAction(actZamkAll);
    menuWindow->addAction(actTile);
    menuWindow->addAction(actCascade);
    menuWindow->addAction(actNext);
    menuWindow->addAction(actPrev);
    menuWindow->addSeparator();
    menuWindow->addAction(actTabbed);

    menuHelp = menuBar()->addMenu(tr("&Pomoc"));
    menuHelp->addAction(actionAbout);
    menuHelp->addAction(actionHelp);
}
//------------------------------------------------------------------------------
void GMainWin::createToolBars()
{
    toolBarProj = addToolBar(tr("Projekt"));
    toolBarProj->addAction(actionNew);
    toolBarProj->addAction(actionOpen);
    toolBarProj->addAction(actionSave);

    toolBarDane = addToolBar(tr("Dane"));
    toolBarDane->addAction(actionOpenData);

    toolBarInte = addToolBar(tr("Interpolacja"));
    toolBarInte->addAction(action_invdist);
    toolBarInte->addAction(action_okriging);
    toolBarInte->addAction(action_variogram);

    toolBarZaso = addToolBar(tr("Zasoby"));
    toolBarZaso->addAction(actionZasoby);
    toolBarZaso->addAction(actionAnaliza);

    toolBarTool = addToolBar(tr("Narzędzia"));
    toolBarTool->addAction(actionToolPdf);
    toolBarTool->addAction(actionHelp);
}
//------------------------------------------------------------------------------
void GMainWin::createStatusBar()
{
    progresBar = new QProgressBar(this);
    progresBar->hide();
    statusBar()->addWidget(new QLabel("marek.wrzeszcz@hotmail.com",this));
    statusBar()->addWidget(progresBar,true);
}
//------------------------------------------------------------------------------
void GMainWin::updateMenus()
{

}
//------------------------------------------------------------------------------
void GMainWin::readSettings()
{
    QSettings settings("Marek Wrzeszcz", "MGS");
    settings.beginGroup("GMainWindow");
        resize(settings.value("size", QSize(400, 400)).toSize());
        move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();
}
//------------------------------------------------------------------------------
void GMainWin::writeSettings()
{
    QSettings settings("Marek Wrzeszcz", "MGS");
    settings.beginGroup("GMainWindow");
         settings.setValue("size", size());
         settings.setValue("pos", pos());
    settings.endGroup();
}
//------------------------------------------------------------------------------
QWidget  *GMainWin::activeMdiW()
{
    if(QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<QWidget  *> (activeSubWindow->widget());
    return 0;
}
//------------------------------------------------------------------------------
void GMainWin::slot_nowy_proj()
{
    createEmptyModel();
    projFile = "NIE ZAPISANY";
    setWindowTitle(APPNAME + " - " + projFile);
}
//------------------------------------------------------------------------------
void GMainWin::slot_open_proj()
{
    QString fileName = QFileDialog::getOpenFileName (this,"Otwórz projekt","",
                                                     tr("Geostat (*.gst)"));
    if(!fileName.isEmpty())
    {
        ifstream we(fileName.toStdString().c_str());
        if(we.is_open())
        {
            Mset m;
            Set_interpolacja s;
            if(we >> m >> s)
            {
                if(curModel->wczytaj_proj(m, s))
                {
                    proSet->slotUpdateSet();
                    projFile = fileName;
                    setWindowTitle(APPNAME + " - " + projFile);
                    emit signal_zmiana_danych();
                }
                else
                {

                    QMessageBox::information(this,"Brak pliku",QString::fromStdString(m.name));
                }
            }
            else  QMessageBox::information(this,"Błąd w pliku",fileName);

            we.close();
        }
    }
}
//------------------------------------------------------------------------------
void GMainWin::slot_open_win(QString s)
{
    if(is_win(s))
        mdiArea->setActiveSubWindow(is_win(s));
    else
    {
       if(s=="WIDOK 3D") otworz(WIDOK);
       else if(s=="MAPA") otworz(MAPA);
       else if(s=="DANE") otworz(TABELA);
       else if(s=="VARIOGRAM") otworz(VARIOGRAM);
       else if(s=="RAPORT") otworz(RAP);
       else return;
    }
}
//------------------------------------------------------------------------------
QMdiSubWindow *GMainWin::is_win(const QString akcess_name)
{
    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        if (window->widget()->accessibleName() == akcess_name) return window;
    }
    return 0;
}
//------------------------------------------------------------------------------
void GMainWin::slot_save_proj()
{
    if(projFile == "NIE ZAPISANY") slot_save_proj_as();
    else
    {
        if (zapisz_projekt())
        {
            QMessageBox::information(this,"Zapis projektu",projFile);
        }
        else
        {
            QMessageBox::information(this,"Nieudany zapis",projFile);
        }
    }

}
//------------------------------------------------------------------------------
void GMainWin::slot_save_proj_as()
{

    QString fileName = QFileDialog::getSaveFileName (this,
                        "Zapisz projekt jako...","",tr("Geostat (*.gst)"));
    if(!fileName.isEmpty())
    {
        fileName += ".gst";
        QString old = projFile;
        projFile = fileName;

        if (zapisz_projekt())
        {
            setWindowTitle(APPNAME + " - " + projFile);
            QMessageBox::information(this,"Zapis projektu",fileName);
        }
        else
        {
            projFile = old;
            QMessageBox::information(this,"Nieudany zapis",fileName);
        }
    }
}
//------------------------------------------------------------------------------
void GMainWin::slot_wczytaj_dane()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Otwórz plik z danymi"),
                               QString(),
                               tr("ASCII (*.txt *.dat *.csv);;Wszystkie (*)"));
    if(!fileName.isEmpty())
    {
        QMessageBox::information(this,"WYBRAŁEŚ",fileName);
        curModel->wczytaj_dane(fileName.toStdString(),"\t");
        //proSet->slotUpdateSet();
        proSet->updateView();
        emit signal_zmiana_danych();
    }
}
//------------------------------------------------------------------------------
void GMainWin::slot_wczytaj_model()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Otwórz plik *set modelu"),
                               QString(),
                               tr("ASCII SET (*.set);;Wszystkie (*)"));
    if(!fileName.isEmpty())
    {
        QMessageBox::information(this,"INFORMACJA",fileName);
        curModel->wczytaj_model(fileName.toStdString(),"\t");
        proSet->updateView();
        emit signal_zmiana_danych();
    }
}
//------------------------------------------------------------------------------
void GMainWin::slot_wczytaj_surf()
{
    QMessageBox::information(this,"INFORMACJA","to do - slot_wczytaj_surf");
}
//------------------------------------------------------------------------------
void GMainWin::slot_about()
{
    QMessageBox::about(this, tr("PROJEKT MGS 2014"),
                       tr("wersja 0.1\nautor @ Marek Wrzeszcz 2014\n\n GNU General Public License \n www.gnu.org/licenses"));
}

void GMainWin::slot_instrukcja()
{
    QMessageBox::information(this,"INFORMACJA","to do - instrukcja");
}
//------------------------------------------------------------------------------
void GMainWin::updateWindowMenu()
{
    QMessageBox::information(this,"INFORMACJA","to do");
}
//------------------------------------------------------------------------------
void GMainWin::slot_tabbed()
{
    if(mdiArea->viewMode() == QMdiArea::SubWindowView)
        mdiArea->setViewMode(QMdiArea::TabbedView);
    else mdiArea->setViewMode(QMdiArea::SubWindowView);
}
//------------------------------------------------------------------------------
void GMainWin::createEmptyModel()
{
    if (curModel) curModel->resetModel();
    else curModel = new GeoModel();
    proSet->setUstaw(curModel->ptr_mset());
    emit signal_zmiana_danych();
}
//------------------------------------------------------------------------------
void GMainWin::slot_zasoby()
{
    proSet->setZasoby(curModel->policzZasoby());
    emit signal_zmiana_danych();
}
//------------------------------------------------------------------------------
void GMainWin::slot_analiza()
{
    GProAnaliza an(new GeoZasoby(curModel->ptr_mset(),curModel->ptr_cube()), curModel, this);
    if(an.exec()==QDialog::Accepted)
    {
        curModel->ptr_mset()->klasy_zas = an.get_klasy();
    }
}
//------------------------------------------------------------------------------
void GMainWin::slot_tool_send()
{
    QMessageBox::information(this,"INFORMACJA","to do - slot_tool_send");
}
//------------------------------------------------------------------------------
void GMainWin::slot_tool_pdf()
{
    slot_open_win("RAPORT");
    GeoWidgetRaport *r = 0;
    if(QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
    r = qobject_cast<GeoWidgetRaport *> (activeSubWindow->widget());
    if(!r) return;

    QString fileName = QFileDialog::getSaveFileName(this, "Raport PDF",
                                                    QString(), "*.pdf");
        if (!fileName.isEmpty())
        {
            if (QFileInfo(fileName).suffix().isEmpty())
                fileName.append(".pdf");
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            r->ptr_textEdit()->document()->print(&printer);
        }
}
//------------------------------------------------------------------------------
void GMainWin::slot_calc_end()
{
    slot_repaint();
    slot_zasoby();
    progresTimer->stop();
    double t = zegar.elapsed()/1000.0;
    QMessageBox::information(this,"INFORMACJA","policzono w czasie "
                             +QString::number(t) + " s ");
    progresBar->hide();
}
//------------------------------------------------------------------------------
void GMainWin::slot_repaint()
{
    foreach (QMdiSubWindow *window, mdiArea->subWindowList())
    {
        window->repaint();
    }
}
//------------------------------------------------------------------------------
void GMainWin::slot_invdist()
{
    interpolacja(INVDIST);
}
//------------------------------------------------------------------------------
void GMainWin::slot_okriging()
{
    interpolacja(OKRIGING);
}
//------------------------------------------------------------------------------
void GMainWin::slot_variogram()
{
    progresBar->show();
    progresTimer->start();
    zegar.start();
    QFuture<void> future;
    future = QtConcurrent::run( boost::bind( &GeoModel::calc_variogram,
                                             curModel,
                                             curModel->get_last_set().set_variogram) );
    watcher.setFuture(future);
}
//------------------------------------------------------------------------------
void GMainWin::zapisz(ZAPIS zapis)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz");
    if(!fileName.isEmpty())
    {
    switch(zapis)
    {
    case DANE:
         QMessageBox::information(this,"ZAPISANO DANE",fileName);
         curModel->wypisz_dane(fileName.toStdString());
         break;
    case MODEL:
         QMessageBox::information(this,"ZAPISANO MODEL",fileName);
         curModel->wypisz_model(fileName.toStdString());
         break;
    case ZASOBY:
         QMessageBox::information(this,"ZAPISANO ZASOBY",fileName);
         curModel->wypisz_zasoby(fileName.toStdString());
         break;
    case RAPORT:
         QMessageBox::information(this,"ZAPISANO RAPORT",fileName);
         curModel->wypisz_raport(fileName.toStdString());
         break;
    case SEMIVARIOGRAM:
         QMessageBox::information(this,"ZAPISANO SEMIVARIOGRAM",fileName);
         curModel->wypisz_vario(fileName.toStdString());
         break;
    default:
         break;
    }
    }
}
//------------------------------------------------------------------------------
bool GMainWin::zapisz_projekt()
{
    ofstream wy(projFile.toStdString().c_str());
    if(wy.is_open())
    {
         wy << *curModel->ptr_mset() << endl << curModel->get_iset();
         wy.close();
         return true;
    }
    else return false;
}
//------------------------------------------------------------------------------
void GMainWin::interpolacja(METODA metoda)
{
    GProDialog d(curModel->get_last_set(),metoda,this);
    Set_interpolacja set_interp;
    if(d.exec()==QDialog::Accepted)
    {
        set_interp = d.get_set_interp();
    }
    else return;
    progresBar->show();
    progresTimer->start();
    zegar.start();
    QFuture<void> future;
    if(metoda == OKRIGING)
         future = QtConcurrent::run( boost::bind( &GeoModel::calc_okriging,
                                                  curModel, set_interp) );
    else if(metoda == INVDIST)
          future = QtConcurrent::run( boost::bind( &GeoModel::calc_invdist,
                                                   curModel, set_interp) );
    watcher.setFuture(future);
}
//------------------------------------------------------------------------------
void GMainWin::otworz(OKNO okno)
{
    switch(okno)
    {
    case TABELA:
        slot_okno_dane();
        break;
    case VARIOGRAM:
        slot_okno_variogram();
        break;
    case MAPA:
        slot_okno_mapa();
        break;
    case WIDOK:
        slot_okno_widok();
        break;
    case RAP:
        slot_okno_raport();
        break;
    default:
        break;
    }
}
//------------------------------------------------------------------------------
void GMainWin::slot_okno_dane()
{
    if(curModel && curModel->ptr_dane()->get_size())
    {
        QMdiSubWindow *subWindow = new QMdiSubWindow;
        GeoWidgetDane *wDat = new GeoWidgetDane(curModel,this);
        subWindow->setWidget(wDat);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->setWindowIcon(QIcon(":/table"));
        subWindow->resize(700,300);
        mdiArea->addSubWindow(subWindow)->show();
    }
    else
        QMessageBox::information(this,"INFORMACJA","brak danych");
}
//------------------------------------------------------------------------------
void GMainWin::slot_okno_variogram()
{
    QMdiSubWindow *subWindow = new QMdiSubWindow;
    subWindow->setWidget(new GeoWidgetVariogram(curModel,this));
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowIcon(QIcon(":/vario"));
    subWindow->resize(890,350);
    mdiArea->addSubWindow(subWindow)->show();
}
//------------------------------------------------------------------------------
void GMainWin::slot_okno_mapa()
{
    QMdiSubWindow *subWindow = new QMdiSubWindow;
    subWindow->setWidget(new GeoWidget2D(curModel,this));
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowIcon(QIcon(":/map"));
    subWindow->resize(600,600);
    mdiArea->addSubWindow(subWindow)->show();
}
//------------------------------------------------------------------------------
void GMainWin::slot_okno_widok()
{
    QMdiSubWindow *subWindow = new QMdiSubWindow;
    subWindow->setWidget(new GeoWidget3D(curModel,this));
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowIcon(QIcon(":/model"));
    subWindow->resize(600,600);
    mdiArea->addSubWindow(subWindow)->show();
}
//------------------------------------------------------------------------------
void GMainWin::slot_okno_raport()
{
    QMdiSubWindow *subWindow = new QMdiSubWindow;
    subWindow->setWidget(new GeoWidgetRaport(curModel,this));
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowIcon(QIcon(":/raport"));
    subWindow->resize(600,400);
    mdiArea->addSubWindow(subWindow)->show();
}
//------------------------------------------------------------------------------
 void GMainWin::slot_reset_model()
 {
     curModel->updateModel();
     proSet->setUstaw(curModel->ptr_mset());
     emit signal_zmiana_danych();
 }
//------------------------------------------------------------------------------
 void GMainWin::slot_progres()
 {
     progresBar->setRange(curModel->get_progres().pmin,
                          curModel->get_progres().pmax);
     progresBar->setValue(curModel->get_progres().pcur);
 }
//------------------------------------------------------------------------------
 void GMainWin::slot_zapis_dane()
 {
     zapisz(DANE);
 }
//------------------------------------------------------------------------------
 void GMainWin::slot_zapis_model()
 {
     zapisz(MODEL);
 }
//------------------------------------------------------------------------------
 void GMainWin::slot_zapis_zasoby()
 {
     zapisz(ZASOBY);
 }
//------------------------------------------------------------------------------
 void GMainWin::slot_zapis_raport()
 {
     zapisz(RAPORT);
 }
 //------------------------------------------------------------------------------
 void GMainWin::slot_zapis_variogram()
 {
     zapisz(SEMIVARIOGRAM);
 }
 //-----------------------------------------------------------------------------
 void GMainWin::slot_dane_stat()
 {

 }
//------------------------------------------------------------------------------
void GMainWin::slot_zmiana_punktu(wektor3d w)
{
    emit signal_zmiana_punktu(w);
}
//------------------------------------------------------------------------------
