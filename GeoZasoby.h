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

#ifndef GEOZASOBY_H
#define GEOZASOBY_H

#include "GeoModel.h"
#include "globalne.h"
///
/// \brief KlasaZas
///
typedef std::pair<double,double> KlasaZas;
///
/// \brief KlasyZas
///
typedef std::vector<KlasaZas> KlasyZas;
///
/// \brief The GeoZasoby class
///
class GeoZasoby
{
public:
    ///
    /// \brief GeoZasoby
    /// \param _modelSet
    /// \param _geoCube
    ///
    GeoZasoby(Mset *_modelSet, GeoCube * _geoCube);
    ///
    /// \brief ~GeoZasoby
    ///
    virtual ~GeoZasoby();
    ///
    /// \brief przelicz_zasoby
    /// \return
    ///
    wektor3d przelicz_zasoby();
    ///
    /// \brief przelicz_zasoby
    /// \param _minp
    /// \param _maxp
    /// \return
    ///
    wektor3d przelicz_zasoby(double _minp, double _maxp);
    ///
    /// \brief analiza_zasoby
    /// \return
    ///
    std::vector<geo3d> analiza_zasoby();
    ///
    /// \brief analiza_zasoby
    /// \param _ileKlas
    /// \return
    ///
    std::vector<geo3d> analiza_zasoby(int _ileKlas);
    ///
    /// \brief get_zasoby
    /// \return
    ///
    wektor3d get_zasoby(){return zasoby;}
    ///
    /// \brief set_klasy
    /// \param kl
    ///
    void set_klasy(KlasyZas kl){klasyZas = kl;}
    ///
    /// \brief set_klasy
    /// \param ile
    ///
    void set_klasy(int ile){ileKlas = ile;}
    ///
    /// \brief getError
    /// \return
    ///
    double getError()const {return error;}

private:
    ///
    /// \brief ustaw_klasy
    ///
    void ustaw_klasy();
    ///
    /// \brief policzBlok
    /// \param parametry
    /// \param rozmiar
    /// \return
    ///
    wektor3d policzBlok(wektor3d parametry, double rozmiar);
    ///
    /// \brief modelSet
    ///
    Mset *modelSet;
    ///
    /// \brief geoCube
    ///
    GeoCube *geoCube;
    ///
    /// \brief zasoby
    ///
    wektor3d zasoby;
    ///
    /// \brief wynikAnalizy
    ///
    std::vector<geo3d> wynikAnalizy;
    ///
    /// \brief klasyZas
    ///
    KlasyZas klasyZas;
    ///
    /// \brief ileKlas
    ///
    int ileKlas;

    double error;
};

#endif // GEOZASOBY_H
