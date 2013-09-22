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

#include "GeoZasoby.h"
//------------------------------------------------------------------------------
GeoZasoby::GeoZasoby(Mset *_modelSet, GeoCube *_geoCube):
    modelSet(_modelSet),
    geoCube(_geoCube),
    ileKlas(10)
{
    zasoby = przelicz_zasoby();
    ustaw_klasy();
}
//------------------------------------------------------------------------------
GeoZasoby::~GeoZasoby()
{

}
//------------------------------------------------------------------------------
wektor3d GeoZasoby::przelicz_zasoby()
{
    if(!geoCube || !modelSet) return wektor3d();

    double cutof=modelSet->cutoff;
    wektor3d blok, blok2;
    int licz1,licz2;
    licz1=licz2=0;
    for(int a=0; a<geoCube->size_x(); ++a)
        for(int b=0; b<geoCube->size_y(); ++b)
            for(int c=0; c<geoCube->size_z(); ++c)
            {
                licz1++;
                blok = geoCube->getRekLok(wektor3i(a,b,c));
                if(blok.x > cutof)
                {
                    licz2++;
                    blok2=blok2+policzBlok(blok,modelSet->sp);
                }
            }
    blok2.y=licz2;
    blok2.z=licz1;
    return blok2;
}
//------------------------------------------------------------------------------
wektor3d GeoZasoby::przelicz_zasoby(double _minp, double _maxp)
{
    if(!geoCube || !modelSet) return wektor3d();
    wektor3d blok, blok2;
    int licz1,licz2;
    licz1=licz2=0;
    for(int a=0; a<geoCube->size_x(); ++a)
        for(int b=0; b<geoCube->size_y(); ++b)
            for(int c=0; c<geoCube->size_z(); ++c)
            {
                licz1++;
                blok = geoCube->getRekLok(wektor3i(a,b,c));
                if(blok.x >= _minp && blok.x < _maxp)
                {
                    licz2++;
                    blok2=blok2+policzBlok(blok,modelSet->sp);
                }
            }
    blok2.y=licz2;
    blok2.z=licz1;
    return blok2;
}
//------------------------------------------------------------------------------
std::vector<geo3d> GeoZasoby::analiza_zasoby()
{
    wynikAnalizy.clear();
    for(unsigned int i =0; i<klasyZas.size(); ++i)
    {
        geo3d wyn;
        wyn.xyz.x = i+1;
        wyn.xyz.y = klasyZas[i].first;
        wyn.xyz.z = klasyZas[i].second;
        wynikAnalizy.push_back(wyn);
    }
    if(!wynikAnalizy.size())return wynikAnalizy;
    wektor3d blok;
    for(int a=0; a<geoCube->size_x(); ++a)
        for(int b=0; b<geoCube->size_y(); ++b)
            for(int c=0; c<geoCube->size_z(); ++c)
            {
                blok = geoCube->getRekLok(wektor3i(a,b,c));
                double v = blok.x;
                for(unsigned int i =0; i<wynikAnalizy.size(); ++i)
                {                     
                    if(v >= wynikAnalizy[i].xyz.y && v < wynikAnalizy[i].xyz.z)
                    {
                        wynikAnalizy[i].dat.x += 1;
                        wektor3d tmp = policzBlok(blok,modelSet->sp);
                        wynikAnalizy[i].dat.y += tmp.x;
                        wynikAnalizy[i].dat.z += tmp.y;
                    }
                }
                if( v == wynikAnalizy[wynikAnalizy.size()-1].xyz.z)
                {
                wynikAnalizy[wynikAnalizy.size()-1].dat.x += 1;
                wektor3d tmp = policzBlok(blok,modelSet->sp);
                wynikAnalizy[wynikAnalizy.size()-1].dat.y += tmp.x;
                wynikAnalizy[wynikAnalizy.size()-1].dat.z += tmp.y;
                }
            }
    return wynikAnalizy;
}
//------------------------------------------------------------------------------
std::vector<geo3d> GeoZasoby::analiza_zasoby(int _ileKlas)
{
    ileKlas = _ileKlas;
    ustaw_klasy();
    return analiza_zasoby();
}
//------------------------------------------------------------------------------
void GeoZasoby::ustaw_klasy()
{
    klasyZas.clear();
    double mink = geoCube->get_min().x;
    double maxk = geoCube->get_max().x;
    if(mink == -NULLDAT || maxk == NULLDAT || ileKlas == 0)
    {
        wynikAnalizy.clear();
        return ;
    }
    double sizek = (maxk - mink) / ileKlas;
    KlasaZas klasa;
    for(int i = 0; i < ileKlas; ++i)
    {
        klasa.first = mink + i*sizek;
        klasa.second = mink + (i+1)*sizek;
        klasyZas.push_back(klasa);
    }
}
//------------------------------------------------------------------------------
wektor3d GeoZasoby::policzBlok(wektor3d parametry, double rozmiar)
{
    double masa_bloku, masa_kop ;
    double dzielnik = 1.0;
    if(modelSet->jednostki == PPM) dzielnik = 1000000.0;
    else if (modelSet->jednostki == PROCENTY) dzielnik = 100.0;
    masa_bloku = (rozmiar*rozmiar*rozmiar)*modelSet->gestosc;
    masa_kop = masa_bloku * parametry.x / dzielnik;
    return wektor3d(masa_kop,masa_bloku,0);
}
//------------------------------------------------------------------------------
