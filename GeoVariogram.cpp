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

#include "GeoVariogram.h"
#include <iostream>
//------------------------------------------------------------------------------
GeoVariogram::GeoVariogram(GeoDat *_dane, wektor3d ustawienie):
    dane(_dane),
    vario_set(ustawienie)
{

}
//------------------------------------------------------------------------------
GeoVariogram::GeoVariogram(GeoDat *_dane):
    dane(_dane),
    vario_set(wektor3d(1.0,100.0,32.0))
{

}
//------------------------------------------------------------------------------
void GeoVariogram::recalc(wektor3d ustawienie)
{
    vario_set = ustawienie;
    recalc();
}
//------------------------------------------------------------------------------
void GeoVariogram::recalc()
{
    GeoMapa::iterator it = dane->get_begin();
    GeoMapa::iterator end = dane->get_end();
    GeoMapa::iterator jt;

    policz_klasy(vario_data);

    double dst(0.0), kw(0.0);

    for(; it != end; ++it)
        for(jt = it ; jt != end; ++jt)
        {          
            dst = dist( it->first, jt->first );
            if(dst > max_dist) continue;
            kw = (it->second.x - jt->second.x)*(it->second.x - jt->second.x);

            for(unsigned int i =0; i<vario_data.size(); ++i)
            {
                if(dst >= vario_data[i].xyz.y && dst < vario_data[i].xyz.z)
                {
                    vario_data[i].dat.x = vario_data[i].dat.x + dst;
                    vario_data[i].dat.y = vario_data[i].dat.y + kw;
                    vario_data[i].dat.z = vario_data[i].dat.z + 1;
                }
            }
        }
    for(unsigned int i =0; i<vario_data.size(); ++i)
    {
        vario_data[i].dat.x =  vario_data[i].dat.x /  vario_data[i].dat.z;
        vario_data[i].dat.y = vario_data[i].dat.y / (2*vario_data[i].dat.z);
    }    
    wektor3d tmp;
    dist_delta_klas.clear();
    for(unsigned int i =0; i<vario_data.size(); ++i)
    {
        tmp = vario_data[i].dat;
        if(tmp.z>=vario_set.z) dist_delta_klas.push_back(tmp);
    }
}
//------------------------------------------------------------------------------
void GeoVariogram::set_dane(GeoDat *_dane, wektor3d ust)
{
    dane = _dane;
    vario_set = ust;
}
//------------------------------------------------------------------------------
void GeoVariogram::set_dane(GeoDat *_dane)
{
    dane = _dane;
    vario_set = wektor3d(1.0,100.0,32.0);
}
//------------------------------------------------------------------------------
string GeoVariogram::get_raport()
{
    stringstream ss;
    for(unsigned i=0; i <  vario_data.size(); ++i)
    {
        ss << vario_data[i] << endl;
    }
    return ss.str();
}
//------------------------------------------------------------------------------
double GeoVariogram::auto_rozmiar(double siz, int ile)
{
    return ceil(siz)/(double)ile;
}
//------------------------------------------------------------------------------
double GeoVariogram::find_max_dis(GeoDat *d)
{
    double maxd = 0.0;
    GeoMapa::iterator it = d->get_begin();
    GeoMapa::iterator end = d->get_end();
    GeoMapa::iterator jt;
    for(; it != end; ++it)
        for(jt = it ; jt != end; ++jt)
        {
            double tmp = dist( it->first, jt->first );
            if(maxd < tmp) maxd =tmp;
        }
    std::cout << maxd << std::endl;
    return maxd;
}
//------------------------------------------------------------------------------
void GeoVariogram::policz_klasy(std::vector<geo3d> &vd)
{
    max_dist = vario_set.x*vario_set.y;
    vd.clear();
    geo3d tmpklas;

    tmpklas.xyz.x = 1.0;
    tmpklas.xyz.y = 0.0;
    tmpklas.xyz.z = vario_set.x;
    vd.push_back(tmpklas);

    for(int i = 1; i < (int)vario_set.y; ++i)
    {
        tmpklas.xyz.x = i+1.0;
        tmpklas.xyz.y = tmpklas.xyz.z ;
        tmpklas.xyz.z = tmpklas.xyz.z+vario_set.x;
        vd.push_back(tmpklas);
    }
}
//------------------------------------------------------------------------------

