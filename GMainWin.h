#ifndef GMAINWIN_H
#define GMAINWIN_H

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDockWidget>
#include <QMainWindow>
#include <QApplication>

class QMenuBar;
class QMenu;
class QToolBar;
class QStatusBar;
class QMessageBox;
class QFileDialog;
class QSettings;
class QProgressBar;

#include <QCloseEvent>
#include <QAction>

#include "GProTree.h"
#include "GProSet.h"
#include "GeoModel.h"
#include "globalne.h"
#include "GeoVariogram.h"
#include "GProDialog.h"

#include <QFutureWatcher>
#include <QTime>

QString const APPNAME = "GeoStat";
///
/// \brief Klasa GMainWin - GUI aplikacji
///
class GMainWin : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief GMainWin
    /// \param wskaźnik na rodzica
    ///
    GMainWin(QWidget *parent = 0);
    ~GMainWin();
    ///
    /// \brief typ wyliczeniowy ZAPIS
    ///
    enum ZAPIS{DANE,MODEL,ZASOBY,RAPORT};
    ///
    /// \brief The OKNO enum
    ///
    enum OKNO{TABELA,VARIOGRAM,MAPA,WIDOK,RAP};

protected:
    ///
    /// \brief closeEvent
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
    ///
    void slot_open_win(QString);

    void slot_okno_dane();
    void slot_okno_variogram();
    void slot_okno_mapa();
    void slot_okno_widok();
    void slot_okno_raport();

    void slot_zmiana_punktu(wektor3d);
    void slot_reset_model();
    void slot_progres();

    void slot_calc_end();
    void slot_repaint();

    void about();
    void updateMenus();
    void updateWindowMenu();

private:
    QFutureWatcher<void> watcher;

    void zapisz(ZAPIS);
    bool zapisz_projekt();

    void interpolacja(METODA);
    void otworz(OKNO);
    void dodaj_okno(QMdiSubWindow *);

    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void createDockWin();
    void readSettings();
    void writeSettings();
    void createEmptyModel();

    QString projFile;

    QWidget  *activeMdiW();
    QMdiSubWindow *findMdiW(const QString &wName);
    QMdiSubWindow * is_win(const QString akcess_name);

    GProTree *proTree;
    GProSet *proSet;

    GeoModel *curModel;

    QMdiArea *mdiArea;

    QDockWidget *dockTree;
    QDockWidget *dockSet;

    QProgressBar *progresBar;
    QTimer *progresTimer;
    QTime zegar;

    QMenu *menuProj;
    QMenu *menuData;
    QMenu *subMenuOpen;
    QMenu *subMenuSave;
    QMenu *menuInterp;
    QMenu *menuZasoby;
    QMenu *menuTools;
    QMenu *menuWindow;
    QMenu *menuHelp;

    QToolBar *toolBarProj;
    QToolBar *toolBarDane;
    QToolBar *toolBarInte;
    QToolBar *toolBarZaso;
    QToolBar *toolBarTool;

    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;

    QAction *actionOpenData;
    QAction *actionOpenModel;
    QAction *actionOpenSurf;
    QAction *actionZapiszDane;
    QAction *actionZapiszModel;
    QAction *actionZapiszZasoby;
    QAction *actionZapiszRaport;
    QAction *actionDaneStat;

    QAction *action_invdist;
    QAction *action_okriging;

    QAction *actionZasoby;
    QAction *actionAnaliza;

    QAction *actionToolSend;
    QAction *actionToolPdf;

    QAction *actZamk;
    QAction *actZamkAll;
    QAction *actTile;
    QAction *actCascade;
    QAction *actNext;
    QAction *actPrev;

    QAction *actionAbout;
    QAction *actionHelp;
};

#endif // GMAINWIN_H
