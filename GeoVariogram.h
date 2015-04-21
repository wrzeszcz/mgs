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

#ifndef GEOVARIOGRAM_H
#define GEOVARIOGRAM_H

#include "GeoDat.h"
#include "globalne.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

///
/// \brief The GeoVariogram class
///
class GeoVariogram
{
public:
    ///
    /// \brief GeoVariogram
    /// \param dane
    /// \param ustawienie rozmiar_klasy
    ///
    GeoVariogram(GeoDat *dane, wektor3d ustawienie);
    ///
    /// \brief GeoVariogram
    /// \param dane
    ///
    GeoVariogram(GeoDat *dane);
    ///
    /// \brief recalc
    /// \param ustawienie rozmiar_klasy
    ///
    void recalc(wektor3d ustawienie);
    ///
    /// \brief recalc
    ///
    void recalc();
    ///
    /// \brief set_dane
    /// \param dane
    /// \param ustawienie - rozmiar_klasy
    ///
    void set_dane(GeoDat *dane, wektor3d ustawienie);
    ///
    /// \brief set_dane
    /// \param dane
    ///
    void set_dane(GeoDat *dane);
    ///
    /// \brief get_raport
    /// \return
    ///
    string get_raport();
    ///
    /// \brief get_klasy
    /// \return
    ///
    std::vector<wektor3d> &get_klasy(){return dist_delta_klas;}
    ///
    /// \brief get_data
    /// \return
    ///
    std::vector<geo3d> &get_data(){return vario_data;}
    ///
    /// \brief find_max_dis
    /// \param d
    /// \return
    ///
    double find_max_dis(GeoDat *d);

private:
    ///
    /// \brief auto_rozmiar
    /// \param siz
    /// \param ile
    /// \return
    ///
    double auto_rozmiar(double siz, int ile);
    ///
    /// \brief policz_klasy
    /// \param vd
    ///
    void policz_klasy(std::vector<geo3d> &vd);
    ///
    /// \brief dist_delta_klas
    ///
    std::vector<wektor3d> dist_delta_klas;
    ///
    /// \brief vario_data
    ///
    std::vector<geo3d> vario_data;
    ///
    /// \brief dane
    ///
    GeoDat *dane;
    ///
    /// \brief dist
    ///
    Odl dist;
    ///
    /// \brief max_dist
    ///
    double max_dist;
    ///
    /// \brief vario_set
    /// vario_set.x - rozmiar klasy
    /// vario_set.y - ilosc klas
    /// vario_set.z - min ilość par
    wektor3d vario_set;
};

#endif // GEOVARIOGRAM_H
