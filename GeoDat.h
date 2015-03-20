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

#ifndef GEODAT_H
#define GEODAT_H

#include <map>
#include <fstream>
#include <vector>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>
#include <map>
#include "globalne.h"

using namespace std;
///
/// \brief GeoMapa - struktura danych
///
typedef map<wektor3d,wektor3d> GeoMapa;
///
/// \brief The GeoDat class - dane
///
class GeoDat
{
public:
    ///
    /// \brief GeoDat - konstruktor
    ///
    GeoDat();
    ~GeoDat();
    ///
    /// \brief dodaj_rek - dodaje rekord geo3d (współrzędne, dane)
    /// \param rekord
    /// \param nadpisz - bool - czy nadpisać jeśli dane o takich samych współrzędnych istnieją w mapie
    ///
    void dodaj_rek (geo3d rek, bool nadpisz);
    ///
    /// \brief dodaj_rek
    /// \param wsp - wektor współrzednych
    /// \param geoval - wektor danych
    /// \param nadpisz - bool - czy nadpisać jeśli dane o takich samych współrzędnych istnieją w mapie
    ///
    void dodaj_rek (wektor3d wsp, wektor3d geoval, bool nadpisz);
    ///
    /// \brief dodaj_rek
    /// \param linia - napis z danymi
    /// \param sep - separator danych
    /// \param nadpisz - bool - czy nadpisać jeśli dane o takich samych współrzędnych istnieją w mapie
    ///
    void dodaj_rek (string linia, string sep, bool nadpisz);
    ///
    /// \brief usun - usuwa
    /// \param wsp - współrzędne danych do usunięcia
    ///
    void usun (wektor3d wsp);
    ///
    /// \brief usun - czyści i resetuje dane
    ///
    void usun ();
    ///
    /// \brief get_rek - zwraca rekord o danym indexie
    /// \param nr - kolejny index
    /// \return - geo3d
    ///
    geo3d getRek(unsigned int nr);
    ///
    /// \brief get_rek - zwraca rekord o danych współrzędnych
    /// \param wsp - wspołrzedne
    /// \return - geo3d
    ///
    geo3d get_rek(wektor3d wsp);
    ///
    /// \brief get_rek - zwraca rekord o danym iteratorze
    /// \param git - iterator
    /// \return vector z danymi rekordu
    ///
    vector<double> get_rek(GeoMapa::iterator git);
    ///
    /// \brief wypisz - wypisuje do strumienia
    /// \param os - referancja do strumienia
    /// \param sep - separator
    ///
    void wypisz(std::ostream& os, const string &sep="\t");
    ///
    /// \brief wczytaj - wczytuje dane ze strumienia
    /// \param is - referencja do strumienia
    ///
    void wczytaj(istream& is);
    ///
    /// \brief wczytaj - wczytuje dane ze strumienia
    /// \param is - referencja do strumienia
    /// \param sep - separator
    /// \param sred - bool - czy uśreniać dane dla zdublowanych współrzędnych
    ///
    void wczytaj(istream& is, const string &sep="\t", bool sred=true);
    ///
    /// \brief wypisz_xyz - wypisuje współrzedne do strumienia
    /// \param os - referancja do strumienia
    /// \param sep - separator
    ///
    void wypisz_xyz(ostream& os, const string &sep="\t");
    ///
    /// \brief wypisz_xyz - wypisuje współrzedne vekctora
    /// \param vec - referencja do vectora
    /// \param ofs - wektor przesuniecia
    ///
    void wypisz_xyz(vector<wektor3d> &vec, wektor3d ofs);
    ///
    /// \brief wypisz_dat - wypisuje dane do vector'a (czyści vector)
    /// \param vector
    ///
    void wypisz_dat(vector<geo3d> &vec);
    ///
    /// \brief wypisz_dat - wypisuje dane w otoczeniu punktu do vector'a (cysci vector)
    /// \param vector
    /// \param centr - punkt centralny
    /// \param r - promień
    ///
    void wypisz_dat(vector<geo3d> &vec, wektor3d centr, double r);
    ///
    /// \brief wczytaj_plik - wczytuje dane z pliku
    /// \param fileName - nazwa pliku
    /// \param sep - separator pola
    /// \param sred - czy usreniać dane dla zdublowanych współrzednych
    /// \return true jeśli sukces
    ///
    bool wczytaj_plik(const string &fileName, const string &sep="\t", bool sred=true);
    ///
    /// \brief wypisz_plik - zapisuje dane do pliku
    /// \param fileName - nazwa
    /// \param sep - separator
    /// \return true jeśli sukces
    ///
    bool wypisz_plik (const string &fileName, const string &sep="\t");
    ///
    /// \brief polacz - dodaje dane z tab2 do odpowiadających rekordów GeoDat (jeśli znajdzie klucz)
    /// \param tab2 - GeoDat
    /// \param od_poz - zaczyna dodawać od danej pozucji
    /// \return ilośc zmodyfikowanych rekordów
    ///
    int polacz(GeoDat& tab2, int  od_poz);
    ///
    /// \brief dolacz - kopiuje dane do GeoDat
    /// \param tab2 - GeoDat
    /// \param nadpisz - czy nadpisać zadublowane dane
    /// \return ilość rekordów dołączonych
    ///
    int dolacz(GeoDat& tab2, bool nadpisz);
    ///
    /// \brief calc_min_zakres - oblicza zakres współrzędnych
    /// \return wektor z minimalnymi wartościami współrzędnych
    ///
    wektor3d calc_min_zakres();
    ///
    /// \brief calc_max_zakres - oblicza zakres współrzędnych
    /// \return wektor z max wartościami współrzędnych
    ///
    wektor3d calc_max_zakres();
    ///
    /// \brief update_min_max - aktualizacja
    ///
    void update_min_max();
    ///
    /// \brief get_min_zakres
    /// \return wektor z minimalnymi wartościami współrzędnych
    ///
    wektor3d get_min_zakres(){return min_zakres;}
    ///
    /// \brief get_max_zakres
    /// \return wektor z maksymalnymi wartościami współrzędnych
    ///
    wektor3d get_max_zakres(){return max_zakres;}
    ///
    /// \brief get_min_value
    /// \return wektor z minimalnymi wartościami danych
    ///
    wektor3d get_min_value(){return min_value;}
    ///
    /// \brief get_max_value
    /// \return wektor z maksymalnymi wartościami danych
    ///
    wektor3d get_max_value(){return max_value;}
    ///
    /// \brief get_srodek
    /// \return współrzędne punktu centalnego bloku danych
    ///
    wektor3d get_srodek();
    ///
    /// \brief get_srodek_A
    /// \return współrzedne punktu centalnego bloku danych przesunięte o wektor początkowy
    ///
    wektor3d get_srodek_A();
    ///
    /// \brief get_wymiary
    /// \return wymiary (rozmiar) bloku danych
    ///
    wektor3d get_wymiary();
    ///
    /// \brief get_size
    /// \return liczebność
    ///
    int get_size()const{return geoMap.size();}
    ///
    /// \brief get_begin
    /// \return iterator
    ///
    GeoMapa::iterator get_begin(){return geoMap.begin();}
    ///
    /// \brief get_end
    /// \return iterator
    ///
    GeoMapa::iterator get_end(){return geoMap.end();}
private:
    ///
    /// \brief min_zakres - wektor najmniejszych wartosci współrzęnych odpowiednio x,y,z
    ///
    wektor3d min_zakres;
    ///
    /// \brief max_zakres - wektor największych wartosci współrzęnych odpowiednio x,y,z
    ///
    wektor3d max_zakres;
    ///
    /// \brief min_value - wektor najmniejszych wartosci danych odpowiednio x,y,z
    ///
    wektor3d min_value;
    ///
    /// \brief max_value - wektor najwiekszych wartosci danych odpowiednio x,y,z
    ///
    wektor3d max_value;
    ///
    /// \brief geoMap - mapa
    ///
    GeoMapa geoMap;
    ///
    /// \brief it - iterator
    ///
    GeoMapa::iterator it;
    ///
    /// \brief dist - obiekt funkcyjny ( wektor3d, wektor3d ) oblicza odległość
    ///
    Odl dist;
    ///
    /// \brief str2double
    /// \param s - anpis
    /// \return double
    ///
    double str2double(string s)
    {
         stringstream ss("");
         double dd;
         ss << s;
         ss >> dd;
         return dd;
    }
};

#endif // GEODAT_H
