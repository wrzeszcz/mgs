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
#include "TNT/tnt.h"
#include "TNT/jama_lu.h"
#include "GeoKriging.h"
//------------------------------------------------------------------------------
GeoKriging::GeoKriging():
    variogram_model(),
    minOt(1),
    maxOt(64)
{

}
//------------------------------------------------------------------------------
GeoKriging::GeoKriging (variogram vario, double nugget, double sill,
                        double range, int minO, int maxO):
    variogram_model(vario,nugget,sill,range),
    minOt(minO),
    maxOt(maxO)
{

}
//------------------------------------------------------------------------------
GeoKriging::GeoKriging(GeoVariogramModel&m, int minO, int maxO):
    variogram_model(m),
    minOt(minO),
    maxOt(maxO)
{

}
//------------------------------------------------------------------------------
GeoKriging::GeoKriging(Set_interpolacja &s):
    variogram_model(s.vario, s.nuget_c0, s.sill_c1, s.range_a),
    minOt(s.min_ilosc),
    maxOt(s.max_ilosc)
{

}
//------------------------------------------------------------------------------
wektor3d GeoKriging::o_kriging(wektor3d pkt, std::vector<geo3d> &otoczenie)
{
// równanie [C] * [W] = [D]
// mC macierz wartości variogramu dla odleglości wszystkich par w otoszeniu
// vD wektor wartości variogramu dla odległości pkt i kolejnych elementów otoczenia
// W szukany wektor wag

    unsigned int vOsize = otoczenie.size();
    unsigned int i = 0;
    unsigned int j = 0;

    if(!vOsize || vOsize < (unsigned int)minOt)
        return wektor3d(NULLDAT,NULLDAT,NULLDAT);

    if(otoczenie.size() > (unsigned int)maxOt)
    {
        spr_otoczenie(pkt,otoczenie,maxOt);
        vOsize = otoczenie.size();
    }

    unsigned int mDsize = vOsize+1;

    TNT::Array2D<double> mC (mDsize,mDsize,1.0);
    TNT::Array1D<double> vD (mDsize,1.0);
    TNT::Array1D<double> Wagi (mDsize,1.0);
    wektor3d wynik;

    //wypełniam macierz mC wartościami variogramu
    //macierz symetryczna
    for (i = 0; i < vOsize; ++ i)
            for (j = i; j < vOsize; ++ j)
                mC [i][j] = mC [j][i] = variogram_model.licz_vario(dist(otoczenie[i].xyz,otoczenie[j].xyz));

    mC[vOsize][vOsize] = 0.0;

    //wypełniam vektor vD wartościami variogramu dla odległości pkt interpolowanego
    for (i = 0; i < vOsize; ++ i)
        vD [i] = variogram_model.licz_vario(dist(pkt,otoczenie[i].xyz));
    vD[vOsize]=1.0;

    //--------------------------- rozwiązanie układu równań---------------------
    JAMA::LU<double> lu(mC);
    Wagi = lu.solve(vD);
    if (!Wagi.dim()) return wektor3d(NULLDAT,NULLDAT,NULLDAT);
    //--------------------------------------------------------------------------

    for (i = 0; i < vOsize; ++ i)
    {
        wynik.x += Wagi[i] * otoczenie[i].dat.x; //liczę wynik
        wynik.y += Wagi[i] * vD[i];              //liczę błąd
    }
    wynik.y += Wagi[vOsize];
    wynik.y = sqrt(wynik.y);
    wynik.z = vOsize;
    return wynik;
}
//------------------------------------------------------------------------------
void GeoKriging::set_parametry (variogram _vario, double _nugget, double _sill,
                                double _range, int minO, int maxO)
{
    variogram_model.set_param(_vario, _nugget, _sill, _range);
    minOt = minO;
    maxOt = maxO;
}
//------------------------------------------------------------------------------
void GeoKriging::spr_otoczenie(const wektor3d &pkt, std::vector<geo3d> &otocz, int m)
{
    G3d_comp_odl_pkt comp(pkt);
    std::sort(otocz.begin(),otocz.end(), comp);
    otocz.resize(m);
}
//------------------------------------------------------------------------------
