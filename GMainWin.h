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

#ifndef GMAINWIN_H
#define GMAINWIN_H

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDockWidget>
#include <QMainWindow>
#include <QApplication>
#include <QCloseEvent>
#include <QAction>
#include <QFutureWatcher>
#include <QTime>

class QMenuBar;
class QMenu;
class QToolBar;
class QStatusBar;
class QMessageBox;
class QFileDialog;
class QSettings;
class QProgressBar;

#include "GProTree.h"
#include "GProSet.h"
#include "GeoModel.h"
#include "globalne.h"
#include "GeoVariogram.h"
#include "GProDialog.h"

///
/// \brief APPNAME stała - nazwa programu
///
QString const static APPNAME = "MGS";
///
/// \brief Klasa GMainWin - GUI aplikacji
///
class GMainWin : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief GMainWin
    /// \param parent wskaźnik na rodzica
    ///
    GMainWin(QWidget *parent = 0);
    ~GMainWin();
    ///
    /// \brief typ wyliczeniowy ZAPIS
    ///
    enum ZAPIS{DANE = 0, MODEL,ZASOBY,RAPORT,SEMIVARIOGRAM};
    ///
    /// \brief typ wyliczeniowy dla pod-okien MDI
    ///
    enum OKNO{TABELA = 0,VARIOGRAM,MAPA,WIDOK,RAP};

protected:
    ///
    /// \brief closeEvent - zdarzenie wyjścia z programu
    /// \param event
    ///
    void closeEvent(QCloseEvent *event);

signals:
    ///
    /// \brief signal_zmiana_danych
    ///
    void signal_zmiana_danych();
    ///
    /// \brief signal_zmiana_modelu
    ///
    void signal_zmiana_modelu();
    ///
    /// \brief signal_zmiana_widoku
    ///
    void signal_zmiana_widoku();
    ///
    /// \brief signal_zmiana_punktu
    ///
    void signal_zmiana_punktu(wektor3d);

private slots:
    ///
    /// \brief slot_nowy_proj
    ///
    void slot_nowy_proj();
    ///
    /// \brief slot_open_proj
    ///
    void slot_open_proj();
    ///
    /// \brief slot_save_proj
    ///
    void slot_save_proj();
    ///
    /// \brief slot_save_proj_as
    ///
    void slot_save_proj_as();

    ///
    /// \brief slot_wczytaj_dane
    ///
    void slot_wczytaj_dane();
    ///
    /// \brief slot_wczytaj_model
    ///
    void slot_wczytaj_model();
    ///
    /// \brief slot_wczytaj_surf
    ///
    void slot_wczytaj_surf();
    ///
    /// \brief slot_zapis_dane
    ///
    void slot_zapis_dane();
    ///
    /// \brief slot_zapis_model
    ///
    void slot_zapis_model();
    ///
    /// \brief slot_zapis_zasoby
    ///
    void slot_zapis_zasoby();
    ///
    /// \brief slot_zapis_raport
    ///
    void slot_zapis_raport();
    ///
    /// \brief slot_zapis_variogram
    ///
    void slot_zapis_variogram();
    ///
    /// \brief slot_dane_stat
    ///
    void slot_dane_stat();

    ///
    /// \brief slot_invdist
    ///
    void slot_invdist();
    ///
    /// \brief slot_okriging
    ///
    void slot_okriging();
    ///
    /// \brief slot_okno_variogram
    ///
    void slot_variogram();

    ///
    /// \brief slot_zasoby
    ///
    void slot_zasoby();
    ///
    /// \brief slot_analiza
    ///
    void slot_analiza();

    ///
    /// \brief slot_tool_send
    ///
    void slot_tool_send();
    ///
    /// \brief slot_tool_pdf
    ///
    void slot_tool_pdf();

    ///
    /// \brief slot_open_win
    /// \param s
    ///
    void slot_open_win(QString s);
    ///
    /// \brief slot_okno_dane
    ///
    void slot_okno_dane();
    ///
    /// \brief slot_okno_variogram
    ///
    void slot_okno_variogram();
    ///
    /// \brief slot_okno_mapa
    ///
    void slot_okno_mapa();
    ///
    /// \brief slot_okno_widok
    ///
    void slot_okno_widok();
    ///
    /// \brief slot_okno_raport
    ///
    void slot_okno_raport();

    ///
    /// \brief slot_zmiana_punktu
    /// \param w
    ///
    void slot_zmiana_punktu(wektor3d w);
    ///
    /// \brief slot_reset_model
    ///
    void slot_reset_model();
    ///
    /// \brief slot_progres
    ///
    void slot_progres();

    ///
    /// \brief slot_calc_end
    ///
    void slot_calc_end();
    ///
    /// \brief slot_repaint
    ///
    void slot_repaint();

    ///
    /// \brief about
    ///
    void slot_about();
    ///
    /// \brief slot_instrukcja
    ///
    void slot_instrukcja();
    ///
    /// \brief updateMenus
    ///
    void updateMenus();
    ///
    /// \brief updateWindowMenu
    ///
    void updateWindowMenu();
    ///
    /// \brief slot_tabbed
    ///
    void slot_tabbed();

private:
    ///
    /// \brief watcher
    ///
    QFutureWatcher<void> watcher;
    ///
    /// \brief zapisz
    ///
    void zapisz(ZAPIS);
    ///
    /// \brief zapisz_projekt
    /// \return
    ///
    bool zapisz_projekt();
    ///
    /// \brief interpolacja
    /// \param metoda
    ///
    void interpolacja(METODA metoda);
    ///
    /// \brief otworz
    /// \param okno
    ///
    void otworz(OKNO okno);
    ///
    /// \brief createActions
    ///
    void createActions();
    ///
    /// \brief createMenus
    ///
    void createMenus();
    ///
    /// \brief createToolBars
    ///
    void createToolBars();
    ///
    /// \brief createStatusBar
    ///
    void createStatusBar();
    ///
    /// \brief createDockWin
    ///
    void createDockWin();
    ///
    /// \brief readSettings
    ///
    void readSettings();
    ///
    /// \brief writeSettings
    ///
    void writeSettings();
    ///
    /// \brief createEmptyModel
    ///
    void createEmptyModel();

    ///
    /// \brief projFile
    ///
    QString projFile;
    ///
    /// \brief activeMdiW
    /// \return
    ///
    QWidget  *activeMdiW();
    ///
    /// \brief findMdiW
    /// \param wName
    /// \return
    ///
    QMdiSubWindow *findMdiW(const QString &wName);
    ///
    /// \brief is_win
    /// \param akcess_name
    /// \return
    ///
    QMdiSubWindow * is_win(const QString akcess_name);
    ///
    /// \brief proTree
    ///
    GProTree *proTree;
    ///
    /// \brief proSet
    ///
    GProSet *proSet;
    ///
    /// \brief curModel
    ///
    GeoModel *curModel;
    ///
    /// \brief mdiArea
    ///
    QMdiArea *mdiArea;
    ///
    /// \brief dockTree
    ///
    QDockWidget *dockTree;
    ///
    /// \brief dockSet
    ///
    QDockWidget *dockSet;
    ///
    /// \brief progresBar
    ///
    QProgressBar *progresBar;
    ///
    /// \brief progresTimer
    ///
    QTimer *progresTimer;
    ///
    /// \brief zegar
    ///
    QTime zegar;

    ///
    /// \brief menuProj
    ///
    QMenu *menuProj;
    ///
    /// \brief menuData
    ///
    QMenu *menuData;
    ///
    /// \brief subMenuOpen
    ///
    QMenu *subMenuOpen;
    ///
    /// \brief subMenuSave
    ///
    QMenu *subMenuSave;
    ///
    /// \brief menuInterp
    ///
    QMenu *menuInterp;
    ///
    /// \brief menuZasoby
    ///
    QMenu *menuZasoby;
    ///
    /// \brief menuTools
    ///
    QMenu *menuTools;
    ///
    /// \brief menuWindow
    ///
    QMenu *menuWindow;
    ///
    /// \brief menuHelp
    ///
    QMenu *menuHelp;

    ///
    /// \brief toolBarProj
    ///
    QToolBar *toolBarProj;
    ///
    /// \brief toolBarDane
    ///
    QToolBar *toolBarDane;
    ///
    /// \brief toolBarInte
    ///
    QToolBar *toolBarInte;
    ///
    /// \brief toolBarZaso
    ///
    QToolBar *toolBarZaso;
    ///
    /// \brief toolBarTool
    ///
    QToolBar *toolBarTool;

    ///
    /// \brief actionNew
    ///
    QAction *actionNew;
    ///
    /// \brief actionOpen
    ///
    QAction *actionOpen;
    ///
    /// \brief actionSave
    ///
    QAction *actionSave;
    ///
    /// \brief actionSaveAs
    ///
    QAction *actionSaveAs;
    ///
    /// \brief actionExit
    ///
    QAction *actionExit;

    ///
    /// \brief actionOpenData
    ///
    QAction *actionOpenData;
    ///
    /// \brief actionOpenModel
    ///
    QAction *actionOpenModel;
    ///
    /// \brief actionOpenSurf
    ///
    QAction *actionOpenSurf;
    ///
    /// \brief actionZapiszDane
    ///
    QAction *actionZapiszDane;
    ///
    /// \brief actionZapiszModel
    ///
    QAction *actionZapiszModel;
    ///
    /// \brief actionZapiszZasoby
    ///
    QAction *actionZapiszZasoby;
    ///
    /// \brief actionZapiszRaport
    ///
    QAction *actionZapiszRaport;
    ///
    /// \brief actionZapiszVariogram
    ///
    QAction *actionZapiszVariogram;
    ///
    /// \brief actionDaneStat
    ///
    QAction *actionDaneStat;

    ///
    /// \brief action_invdist
    ///
    QAction *action_invdist;
    ///
    /// \brief action_okriging
    ///
    QAction *action_okriging;
    ///
    /// \brief action_variogram
    ///
    QAction *action_variogram;

    ///
    /// \brief actionZasoby
    ///
    QAction *actionZasoby;
    ///
    /// \brief actionAnaliza
    ///
    QAction *actionAnaliza;

    ///
    /// \brief actionToolSend
    ///
    QAction *actionToolSend;
    ///
    /// \brief actionToolPdf
    ///
    QAction *actionToolPdf;

    ///
    /// \brief actZamk
    ///
    QAction *actZamk;
    ///
    /// \brief actZamkAll
    ///
    QAction *actZamkAll;
    ///
    /// \brief actTile
    ///
    QAction *actTile;
    ///
    /// \brief actCascade
    ///
    QAction *actCascade;
    ///
    /// \brief actNext
    ///
    QAction *actNext;
    ///
    /// \brief actPrev
    ///
    QAction *actPrev;
    ///
    /// \brief actTabbed
    ///
    QAction *actTabbed;

    ///
    /// \brief actionAbout
    ///
    QAction *actionAbout;
    ///
    /// \brief actionHelp
    ///
    QAction *actionHelp;
};

#endif // GMAINWIN_H
