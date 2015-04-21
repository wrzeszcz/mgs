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

#ifndef GEOMODEL_H
#define GEOMODEL_H

#include "GeoCube.h"
#include "GeoKriging.h"
#include "GeoVariogram.h"
#include "GeoDat.h"
#include "GeoZasoby.h"
#include <math.h>

using namespace std;

//------------------------------------------------------------------------------
///
/// \brief The GeoModel class - moduł obliczeniowy
///
class GeoModel
{
public:
    ///
    /// \brief GeoModel
    ///
    GeoModel();
    ~GeoModel();  
    ///
    /// \brief wczytaj_dane - wczytuje dane z pliku
    /// \param fileName - nazwa pliku
    /// \param sep - separator pól (domyślnie tabulacja)
    /// \param nowe - czy usunać istniejące dane
    /// \param sred - czy uśrednić dane dla powtarzających się współrzędnych
    ///
    void wczytaj_dane(string fileName,
                      string sep="\t",bool nowe = true, bool sred = true);  
    ///
    /// \brief wczytaj_proj - wcztuje projekt
    /// \param _modset - ustawienia modelu
    /// \param _intep - ustawienia interpolacji
    ///
    bool wczytaj_proj(Mset _modset, Set_interpolacja _intep);
    ///
    /// \brief wypiszXYZdane - wypisuje dane do strumienia
    /// \param os - referencja do strumienia
    ///
    void wypiszXYZdane (ostream &os);
    ///
    /// \brief wypiszXYZmodel - wypisuje model do strumienia
    /// \param os - referencja do strumienia
    /// \param tylkoZasoby - czy pisać tylko bloki zasobów
    ///
    void wypiszXYZmodel(ostream &os, bool tylkoZasoby);
    ///
    /// \brief wypisz_dane - zapsiuje dane do pliku
    /// \param fileName - nazwa pliku
    /// \param sep - separator pola (domyślnie tabulator)
    ///
    void wypisz_dane  (string fileName, string sep="\t");
    ///
    /// \brief wypisz_model - zapisuju model do pliku
    /// \param fileName - nawa pliku
    /// \param sep  - separator pola (domyślnie tabulator)
    ///
    void wypisz_model (string fileName, string sep="\t");
    ///
    /// \brief wczytaj_model
    /// \param fileName
    /// \param sep
    ///
    void wczytaj_model(string fileName, string sep="\t");
    ///
    /// \brief wypisz_zasoby - zapisuje zasoby do pliku
    /// \param fileName - nazwa pliku
    /// \param sep - separator pola (domyślnie tabulator)
    ///
    void wypisz_zasoby(string fileName, string sep="\t");
    ///
    /// \brief wypisz_raport - zapsiuje raport do pliku
    /// \param fileName - nazwa pliku
    ///
    void wypisz_raport(string fileName);
    ///
    /// \brief wypisz_vario - zapisuje dane wariogramu do pliku
    /// \param fileName - nazwa pliku
    ///
    void wypisz_vario (string fileName);
    ///
    /// \brief get_xyz_dane - zapisuje do vectora dane
    /// \param vec - vector wynikowy
    /// \param centr
    ///
    void get_xyz_dane (std::vector<wektor3d> &vec,bool centr);
    ///
    /// \brief get_xyz_model - zapisuje do vectora model
    /// \param vec - vector wynikowy
    /// \param centr
    /// \param zasoby
    ///
    void get_xyz_model(std::vector<wektor3d> &vec,bool centr, bool zasoby);
    ///
    /// \brief ptr_dane
    /// \return wskaźnik do obiektu danych
    ///
    GeoDat  *ptr_dane() {return dane;}
    ///
    /// \brief ptr_cube
    /// \return wskażnik do obiketu modelu GeoCube
    ///
    GeoCube *ptr_cube() {return cube;}
    ///
    /// \brief ptr_mset
    /// \return wskaźnik do obiektu ustawień
    ///
    Mset    *ptr_mset() {return modset;}
    ///
    /// \brief ptr_vario
    /// \return wskaźnik do obiketu wariogramu
    ///
    GeoVariogram *ptr_vario(){return curVariogram;}
    ///
    /// \brief get_iset
    /// \return aktualne ustawienia interpolacji
    ///
    Set_interpolacja get_iset(){return last_set;}
    ///
    /// \brief set_iset
    /// \param s - ustawienia interpolacji
    ///
    void set_iset(Set_interpolacja s){last_set = s;}
    ///
    /// \brief glob2lok - konwertuje współrzędne globalne do lokalnych
    /// \param wsp
    /// \return współrzedne lokalne
    ///
    wektor3d glob2lok(wektor3d wsp);
    ///
    /// \brief lok2glob - konwertuje współrzędne lokalne na globalne
    /// \param wsp
    /// \return współrzędne globalne
    ///
    wektor3d lok2glob(wektor3d wsp);
    ///
    /// \brief updateModel - aktualizauje model
    ///
    void updateModel();
    ///
    /// \brief resetModel - resetuje wszystkie dane modelu
    ///
    void resetModel();
    ///
    /// \brief interpolacja - interpoluje wybraną metodą
    /// \param ustawienia
    /// \param metod - typ wyliczeniowy metoda interpolacji
    /// \return
    ///
    bool interpolacja(Set_interpolacja ustawienia, METODA metod);
    ///
    /// \brief calc_invdist - interpoluje metodą odwrotnych odległości
    /// \param ustawienia
    ///
    void calc_invdist(Set_interpolacja ustawienia);
    ///
    /// \brief calc_okriging - interpoluje metodą krigingu zwykłego
    /// \param ustawienia
    ///
    void calc_okriging(Set_interpolacja ustawienia);  
    ///
    /// \brief policzZasoby
    /// \return zasoby
    ///
    wektor3d policzZasoby();
    ///
    /// \brief analizaZasoby
    /// \param _ileKlas
    /// \return vector z zasobami dla danych przedziałów
    ///
    std::vector<geo3d> analizaZasoby(int _ileKlas);
    ///
    /// \brief analizaZasobyReport
    /// \param _ileKlas
    /// \param precyzja_liczb
    /// \return
    ///
    std::string analizaZasobyReport(int _ileKlas, int precyzja_liczb);
    ///
    /// \brief setGeoSet
    /// \param gset
    ///
    void setGeoSet(Mset gset){*modset = gset;}
    ///
    /// \brief create_rapor
    /// \return raport
    ///
    std::string recreate_rapor(const std::string& datetimeStr);
    ///
    /// \brief raport_add
    /// \param str
    ///
    void raport_add(string str){strRaport.insert(0,str);}
    ///
    /// \brief raport_clear
    ///
    void raport_clear(){strRaport.clear();}
    ///
    /// \brief raport_get
    /// \return
    ///
    string raport_get(){return strRaport;}
    ///
    /// \brief nowy_variogram
    /// \param  ust - rozmiar_klasy
    ///
    void nowy_variogram(wektor3d ust);
    ///
    /// \brief calc_variogram
    /// \param ust - rozmiar_klasy
    ///
    void calc_variogram(wektor3d ust);
    ///
    /// \brief get_last_set
    /// \return aktualne ustawienia interpolacji
    ///
    Set_interpolacja get_last_set(){return last_set;}
    ///
    /// \brief get_progres
    /// \return postęp opracji
    ///
    Progres get_progres(){return progres;}
    ///
    /// \brief set_progres_cur
    /// \param v
    ///
    void set_progres_cur(int v){progres.pcur=v;}
    ///
    /// \brief get_progres_cur
    ///
    int get_progres_cur(){return progres.pcur;}

private:
    ///
    /// \brief inv_dist
    /// \param pkt
    /// \param promien
    /// \param potega
    /// \return
    ///
    wektor3d inv_dist(const wektor3d& pkt, double promien, double potega);
    ///
    /// \brief modset
    ///
    Mset *modset;
    ///
    /// \brief dane
    ///
    GeoDat *dane;
    ///
    /// \brief cube
    ///
    GeoCube *cube;
    ///
    /// \brief curVariogram
    ///
    GeoVariogram *curVariogram;
    ///
    /// \brief last_set
    ///
    Set_interpolacja last_set;
    ///
    /// \brief strRaport
    ///
    string strRaport;
    ///
    /// \brief dist
    ///
    Odl dist;
    ///
    /// \brief progres
    ///
    Progres progres;
};
//------------------------------------------------------------------------------
#endif // GEOMODEL_H
