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

#ifndef GEOKRIGING_H
#define GEOKRIGING_H

#include "globalne.h"
#include "GeoVariogramModel.h"
#include <vector>
#include <ostream>
#include <math.h>
#include <algorithm>

///
/// \brief The GeoKriging class - interpolator
///
class GeoKriging
{
public:
    ///
    /// \brief GeoKriging - konstruktor()
    ///
    GeoKriging();
    ///
    /// \brief GeoKriging - konstruktor
    /// \param vario - model variogramu
    /// \param nugget - efekt samorodka
    /// \param sill - próg nasycenia
    /// \param range - zasięg korelacji
    /// \param minO - minimalna ilość danych w otoczeniu
    /// \param maxO - maksymalna ilość danych w otoczeniu
    ///
    GeoKriging(variogram vario, double nugget, double sill, double range, int minO, int maxO);
    ///
    /// \brief GeoKriging - konstruktor
    /// \param m - model semiwaruigramu
    /// \param minO - minimalna ilość danych w otoczeniu
    /// \param maxO - maksymalna ilość danych w otoczeniu
    ///
    GeoKriging(GeoVariogramModel &m , int minO, int maxO);
    ///
    /// \brief GeoKriging
    /// \param s
    ///
    GeoKriging(Set_interpolacja &s);
    ///
    /// \brief o_kriging
    /// \param pkt
    /// \param otoczenie
    /// \return
    ///
    wektor3d o_kriging (wektor3d pkt,std::vector<geo3d> &otoczenie);
    ///
    /// \brief set_parametry
    /// \param vario
    /// \param nugget
    /// \param sill
    /// \param range
    /// \param minO
    /// \param maxO
    ///
    void set_parametry(variogram vario, double nugget, double sill, double range, int minO, int maxO);
    ///
    /// \brief set_variogram
    /// \param v
    ///
    void set_variogram(variogram v){cur_vario = v;}
    ///
    /// \brief set_nugget
    /// \param n
    ///
    void set_nugget(double n){c0 = n;}
    ///
    /// \brief set_sill
    /// \param s
    ///
    void set_sill  (double s){c1 = s;}
    ///
    /// \brief set_range
    /// \param r
    ///
    void set_range (double r){a = r;}
    ///
    /// \brief set_minOt
    /// \param minO
    ///
    void set_minOt(int minO){minOt = minO;}
    ///
    /// \brief set_maxOt
    /// \param maxO
    ///
    void set_maxOt(int maxO){maxOt = maxO;}
    ///
    /// \brief set_geoWariogramModel
    /// \param m
    ///
    void set_geoWariogramModel(GeoVariogramModel &m){variogram_model=m;}
private:
    ///
    /// \brief spr_otoczenie
    /// \param pkt
    /// \param otoczenie
    /// \param max
    ///
    void spr_otoczenie(const wektor3d &pkt,std::vector<geo3d> &otocz, int max);
    ///
    /// \brief cur_vario
    ///
    variogram cur_vario;
    ///
    /// \brief variogram_model
    ///
    GeoVariogramModel variogram_model;
    ///
    /// \brief c0
    ///
    double c0;
    ///
    /// \brief c1
    ///
    double c1;
    ///
    /// \brief a
    ///
    double a;
    ///
    /// \brief minOt
    ///
    int minOt;
    ///
    /// \brief maxOt
    ///
    int maxOt;
    ///
    /// \brief dist
    ///
    Odl dist;
};

#endif // GEOKRIGING_H
