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
GeoVariogram::GeoVariogram(GeoDat *_dane, double rozmiar_klasy):
    dane(_dane),
    rozmiar(rozmiar_klasy)
{
    max_dist = find_max_dis(dane);
    recalc();
}
//------------------------------------------------------------------------------
GeoVariogram::GeoVariogram(GeoDat *_dane):
    dane(_dane)
{
    max_dist = find_max_dis(dane);
    rozmiar = auto_rozmiar(max_dist,100);
    recalc();
}
//------------------------------------------------------------------------------
void GeoVariogram::recalc(double rozmiar_klasy)
{
    rozmiar = rozmiar_klasy;
    recalc();
}
//------------------------------------------------------------------------------
void GeoVariogram::recalc()
{
    GeoMapa::iterator it = dane->get_begin();
    GeoMapa::iterator end = dane->get_end();
    GeoMapa::iterator jt;

    dist_delta.clear();
    dist_delta_klas.clear();

    policz_klasy(vario_data);

    for(; it != end; ++it)
        for(jt = it ; jt != end; ++jt)
        {
            double dst(0.0), kw(0.0);
            dst = dist( it->first, jt->first );
            kw = (it->second.x - jt->second.x)*(it->second.x - jt->second.x);

            for(unsigned int i =0; i<vario_data.size(); ++i)
            {
                if(!dst) break;
                if(dst >= vario_data[i].xyz.y && dst < vario_data[i].xyz.z)
                {
                    vario_data[i].dat.y = vario_data[i].dat.y + kw;
                    vario_data[i].dat.z = vario_data[i].dat.z + 1;
                }
            }


        }


    for(unsigned int i =0; i<vario_data.size(); ++i)
    {
        vario_data[i].dat.y = vario_data[i].dat.y/ (2*vario_data[i].dat.z);
    }
//---------------------------------------------------------
     it = dane->get_begin();
     end = dane->get_end();


    for(; it != end; ++it)
        for(jt = it ; jt != end; ++jt)
        {
            wektor3d tmp;
            tmp.x = dist( it->first, jt->first );
            tmp.y = (it->second.x - jt->second.x)*(it->second.x - jt->second.x);
            if(tmp.y) dist_delta.push_back(tmp);
        }

    std::sort(dist_delta.begin(),dist_delta.end());

    double limit = rozmiar;
    double suma(0.0);
    int licz(0);
    if(!limit)return;
    for(unsigned i=0;i <dist_delta.size();++i)
    {
        if(dist_delta[i].x < limit)
        {
            suma += dist_delta[i].y;
            licz++;
        }
        else
        {
            if(licz)
            dist_delta_klas.push_back(wektor3d(limit - rozmiar/2.0, suma/(2*licz),licz));
            suma=0.0;
            licz=0;
            limit +=rozmiar;
        }
    }
    std::cout<< this->get_raport() << endl;
}
//------------------------------------------------------------------------------
void GeoVariogram::set_dane(GeoDat *_dane, double rozmiar_klasy)
{
    dane = _dane;
    max_dist = find_max_dis(dane);
    rozmiar = rozmiar_klasy;
}
//------------------------------------------------------------------------------
void GeoVariogram::set_dane(GeoDat *_dane)
{
    dane = _dane;
    max_dist = find_max_dis(dane);
    rozmiar = auto_rozmiar(max_dist,100);
}
//------------------------------------------------------------------------------
string GeoVariogram::get_raport()
{
    stringstream ss;
    for(unsigned i=0; i <  dist_delta_klas.size(); ++i)
    {
        ss << dist_delta_klas[i].x << "\t"
           << dist_delta_klas[i].y << "\t"
           << dist_delta_klas[i].z << endl;
    }
    for(unsigned i=0; i <  vario_data.size(); ++i)
    {
        ss << vario_data[i] << endl;
    }
    return ss.str();
}
//------------------------------------------------------------------------------
void GeoVariogram::wypisz_dist_delta(string filename)
{
    ofstream wy(filename.c_str());
    if(wy.is_open())
    {
        wy << dist_delta[dist_delta.size()-1].x << endl;
        for (unsigned i=0; i < dist_delta.size(); ++i)
        {
            wy << dist_delta[i].x << "\t"
               << dist_delta[i].y << "\t"
               << dist_delta[i].z << endl;
        }
        wy.close();
    }
}

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

void GeoVariogram::policz_klasy(std::vector<geo3d> &vd)
{
    vd.clear();
    geo3d tmpklas;
    tmpklas.xyz.x = 1.0;
    tmpklas.xyz.y = 0.0;
    tmpklas.xyz.z = rozmiar;
    tmpklas.dat.x = tmpklas.xyz.y + (tmpklas.xyz.z - tmpklas.xyz.y) / 2.0;

    while(tmpklas.xyz.y < max_dist)
    {
        vd.push_back(tmpklas);
        tmpklas.xyz.x = tmpklas.xyz.x+1;
        tmpklas.xyz.y = tmpklas.xyz.z;
        tmpklas.xyz.z = tmpklas.xyz.z + rozmiar;
        tmpklas.dat.x = tmpklas.xyz.y + (tmpklas.xyz.z - tmpklas.xyz.y) / 2.0;
    }
}


//------------------------------------------------------------------------------

