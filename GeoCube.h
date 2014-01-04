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

#ifndef GEOCUBE_H
#define GEOCUBE_H

#include <cstdlib>
#include <ostream>
#include <exception>
#include <vector>
#include "globalne.h"

using namespace std;
///
/// \brief Klasa GeoCube
///
class GeoCube
{
public:
    ///
    /// \brief GeoCube
    /// \param start - wektor zawierający wsþółrzędne X,Y,Z początku modelu
    /// \param blok - rozmiar bloku (bok sześcianu)
    /// \param dim - wymiary - wektor zawierający ilość bloków w kierunkach X,Y,Z
    ///
    GeoCube(wektor3d start, double blok, wektor3i dim);
    ~GeoCube();
    ///
    /// \brief wyczysc - zwalnia pamięć
    ///
    void wyczysc();
    ///
    /// \brief getRekLok - zwraca wartość w bloku (pozycja podana lokalnie) - po przekroczeniu zakresu zwaraca wektor(0,0,0)
    /// \param poz - index tablicy 3 wymiarowej (0,0,0 == początek modelu)
    /// \return
    ///
    wektor3d getRekLok(wektor3i  poz);
    ///
    /// \brief getRekGlo - zwraca wartość w bloku (pozycja podana globalnie) - po przekroczeniu zakresu zwaraca wektor(0,0,0)
    /// \param poz - współrzedne X,Y,Z
    /// \return
    ///
    wektor3d getRekGlo(wektor3d poz);
    ///
    /// \brief getRek - jak getRekLok ale bez sprawdzania zakresu
    /// \param poz - index tablicy 3 wymiarowej (0,0,0 == początek modelu)
    /// \return
    ///
    wektor3d getRek(wektor3i poz);
    ///
    /// \brief getRek - zwraca wartość w bloku (pozycja podana lokalnie), bez sprawdzania zakresu
    /// \param a - index X
    /// \param b - index Y
    /// \param c - index Z
    /// \return
    ///
    wektor3d getRek(int a,int b, int c);
    ///
    /// \brief setRekLok
    /// \param poz
    /// \param dane
    ///
    void setRekLok(wektor3i poz, wektor3d dane);
    ///
    /// \brief setRekGlo
    /// \param poz
    /// \param dane
    ///
    void setRekGlo(wektor3d poz, wektor3d dane);
    ///
    /// \brief wypiszLok
    /// \param os
    /// \param tylkoXYZ
    /// \param limit
    ///
    void wypiszLok(ostream& os, bool tylkoXYZ, double limit);
    ///
    /// \brief wypiszGlo - wypisuje dane (wsp. globalne) do strumienia
    /// \param os - referencja do strumienia
    /// \param tylkoXYZ - bool - czy wypisac tylko wsp. XYZ
    /// \param limit - referencja do strumienia
    /// \param sep - separator (domyślnie tabulacja)
    ///
    void wypiszGlo(ostream& os, bool tylkoXYZ, double limit, string sep = "\t");
    ///
    /// \brief wypiszGlo - wypisuje dane (wsp. globalne) do strumienia
    /// \param os - referencja do strumienia
    /// \param sep - separator (domyślnie tabulacja)
    ///
    void wypiszGlo(ostream& os, std::string sep = "\t");
    ///
    /// \brief wypiszGlo
    /// \param vec
    /// \param limit
    /// \param ofset
    ///
    void wypiszGlo(vector<wektor3d> &vec, double limit, wektor3d ofset);
    ///
    /// \brief getStart
    /// \return współrzędne początku (0,0,0)
    ///
    wektor3d getStart(){return start3d;}
    ///
    /// \brief getSize
    /// \return
    ///
    wektor3i getSize(){return dim3i;}
    ///
    /// \brief size_x
    /// \return rozmiar w kierunku x
    ///
    int size_x(){return dim3i.x;}
    ///
    /// \brief size_y
    /// \return rozmiar w kierunku y
    ///
    int size_y(){return dim3i.y;}
    ///
    /// \brief size_z
    /// \return rozmiar w kierunku z
    ///
    int size_z(){return dim3i.z;}
    ///
    /// \brief size
    /// \return ilość bloków
    ///
    int size(){return dim3i.x * dim3i.y * dim3i.z;}
    ///
    /// \brief getSpac
    /// \return
    ///
    double getSpac(){return spacing;}
    ///
    /// \brief get_max
    /// \return
    ///
    wektor3d get_max(){return w_max;}
    ///
    /// \brief get_min
    /// \return
    ///
    wektor3d get_min(){return w_min;}
    ///
    /// \brief min_max
    /// \param min
    /// \param max
    ///
    void min_max(wektor3d &min, wektor3d &max);
    ///
    /// \brief min_max
    ///
    void min_max();
    ///
    /// \brief reset_min_max
    ///
    void reset_min_max();

private:
    ///
    /// \brief cube
    ///
    wektor3d ***cube;
    ///
    /// \brief start3d
    ///
    wektor3d start3d;
    ///
    /// \brief dim3i
    ///
    wektor3i dim3i;
    ///
    /// \brief spacing
    ///
    double spacing;
    ///
    /// \brief inicjuj
    ///
    void   inicjuj(); 
    ///
    /// \brief w_max
    ///
    wektor3d w_max;
    ///
    /// \brief w_min
    ///
    wektor3d w_min;
};
//------------------------------------------------------------------------------
#endif // GEOCUBE_H
