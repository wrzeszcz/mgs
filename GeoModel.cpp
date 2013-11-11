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

#include "GeoModel.h"
#include <iostream>
//------------------------------------------------------------------------------
GeoModel::GeoModel()
{
    modset = new Mset();
    dane = new GeoDat();
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
    curVariogram = new GeoVariogram(dane,last_set.rozmiar_klasy);
    this->raport_add("nowy model \n");
}
GeoModel::~GeoModel()
{
    delete modset;
    delete dane;
    delete cube;
    if (curVariogram) delete curVariogram;
}
//------------------------------------------------------------------------------
void GeoModel::wczytaj_dane(string fileName, string sep, bool nowe, bool sred)
{
    if(!dane) dane = new GeoDat();
    else if (nowe) dane->usun();

    wektor3d w;

    dane->wczytaj_plik(fileName,sep, sred);
    modset->start = dane->get_min_zakres();
    w = dane->get_wymiary();

    double d = std::max(w.x, w.y);
    d =std::max(d, w.z);
    double s= ceil(d/50);

    modset->wym =w;
    modset->name = fileName;

    modset->sp=s;
    modset->grid = wektor3i((int)(w.x/s+2),(int)(w.y/s+2),(int)(w.z/s+2));

    updateModel();

    //nowy_variogram(last_set.rozmiar_klasy);
    modset->cutoff = dane->get_min_value().x+
            0.5 * (dane->get_max_value().x-dane->get_min_value().x);

    this->raport_add("wczytany plik "+ fileName + "\n");
}
//------------------------------------------------------------------------------
bool GeoModel::wczytaj_proj(Mset _modset, Set_interpolacja _interp)
{
    if(!dane) dane = new GeoDat();
    else dane->usun();

    if(!dane->wczytaj_plik(_modset.name)) return false;

    *modset = _modset;

    last_set = _interp;

    updateModel();

    //nowy_variogram(last_set.rozmiar_klasy);

    return true;
}
//------------------------------------------------------------------------------
void GeoModel::updateModel()
{
    if(cube) delete cube;
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
}
//------------------------------------------------------------------------------
void GeoModel::resetModel()
{
    if (modset) delete modset;
    if (dane) delete dane;
    if (cube) delete cube;
    if (curVariogram) delete curVariogram;
    modset = new Mset();
    dane = new GeoDat;
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
    curVariogram = NULL;
    this->raport_add("nowy model \n");
}
//------------------------------------------------------------------------------
bool GeoModel::interpolacja(Set_interpolacja ust, METODA metod)
{
    if (metod == INVDIST) calc_invdist(ust);
    else if (metod == OKRIGING) calc_okriging(ust);
    else return false;
    return true;
}
//------------------------------------------------------------------------------
void GeoModel::calc_invdist(Set_interpolacja ustaw)
{  
    cube->reset_min_max();
    progres.pmax = cube->size();
    progres.pmin = progres.pcur = 0;

    for(int a=0; a<cube->size_x();++a)
        for(int b=0; b<cube->size_y();++b)
            for(int c=0; c<cube->size_z();++c)
            {
                wektor3d tmp = inv_dist(this->lok2glob(wektor3d(a,b,c)),
                                        ustaw.promien,ustaw.potega);
                cube->setRekLok(wektor3i(a,b,c),tmp);
                progres.pcur=progres.pcur+1;
            }
    last_set=ustaw;

    modset->min_val=cube->get_min();
    modset->max_val=cube->get_max();
    modset->algorytm = INVDIST;
}
//------------------------------------------------------------------------------
void GeoModel::calc_okriging(Set_interpolacja ustaw)
{   
    cube->reset_min_max();
    progres.pmax = cube->size();
    progres.pmin = progres.pcur = 0;

    GeoKriging gek(ustaw);
    std::vector<geo3d> otocz;

    for(int a=0; a<cube->size_x();++a)
        for(int b=0; b<cube->size_y();++b)
            for(int c=0; c<cube->size_z();++c)
            {
               dane->wypisz_dat(otocz,this->lok2glob(wektor3d(a,b,c)),ustaw.promien);
               wektor3d tmp = gek.o_kriging(this->lok2glob(wektor3d(a,b,c)),otocz);
               cube->setRekLok(wektor3i(a,b,c),tmp);
               progres.pcur = progres.pcur+1;
            }
    last_set=ustaw;

    modset->min_val=cube->get_min();
    modset->max_val=cube->get_max();
    modset->algorytm = OKRIGING;
}
//------------------------------------------------------------------------------
wektor3d GeoModel::policzZasoby()
{
    GeoZasoby gZasoby(modset,cube);
    return gZasoby.get_zasoby();
}
//------------------------------------------------------------------------------
std::vector<geo3d> GeoModel::analizaZasoby(int _ileKlas)
{
    GeoZasoby gZasoby(modset,cube);
    vector<geo3d> analiza = gZasoby.analiza_zasoby(_ileKlas);
    return analiza;
}
//------------------------------------------------------------------------------
string GeoModel::analizaZasobyReport(int _ileKlas)
{
    GeoZasoby gZasoby(modset,cube);
    vector<geo3d> analiza = gZasoby.analiza_zasoby(_ileKlas);
    wektor3d suma;
    string aa;
    for(vector<geo3d>::iterator it = analiza.begin(); it!=analiza.end();++it)
        {
           aa += cos2str(it->xyz.x) + "\t";
           aa += cos2str(it->xyz.y) + " - ";
           aa += cos2str(it->xyz.z) + "\t";
           aa += cos2str(it->dat.x) + "\t";
           aa += cos2str(it->dat.y) + "\t";
           aa += cos2str(it->dat.z) + "\t";
           aa += "\n";
           suma.x += it->dat.x;
           suma.y += it->dat.y;
           suma.z += it->dat.z;

        }
    aa += "\t\t\t"+cos2str(suma.x) + "\t";
    aa += cos2str(suma.y) + "\t";
    aa += cos2str(suma.z) + "\t";
    return aa;
}
//------------------------------------------------------------------------------
void GeoModel::wypiszXYZdane(ostream &os)
{
    dane->wypisz_xyz(os);
}
//------------------------------------------------------------------------------
void GeoModel::wypiszXYZmodel(ostream &os, bool tylkoZasoby)
{
    if (tylkoZasoby) cube->wypiszGlo(os,true, modset->cutoff);
    else cube->wypiszGlo(os,true, -1);
}
//------------------------------------------------------------------------------
void GeoModel::get_xyz_dane(std::vector<wektor3d> &vec, bool cen)
{
    wektor3d ofset;
    if(cen) ofset = (modset->wym/2)+modset->start;
    dane->wypisz_xyz(vec,ofset);
}
//------------------------------------------------------------------------------
void GeoModel::get_xyz_model(std::vector<wektor3d> &vec,bool cen, bool zasoby)
{
    wektor3d ofset;
    if(cen) ofset = (modset->wym/2)+modset->start;
    if(zasoby) cube->wypiszGlo(vec,modset->cutoff, ofset);
    else cube->wypiszGlo(vec,-1,ofset);
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_dane(string fileName, string sep)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        dane->wypisz(of,sep);
        of.close();
    }
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_model(string fileName, string sep)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        cube->wypiszGlo(of, sep);
        of.close();
    }
    ofstream ofs((fileName+".set").c_str());

    modset->name=fileName;
    if(ofs.is_open())
    {
        ofs << *modset;

        ofs.close();
    }
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_zasoby(string fileName, string sep)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        cube->wypiszGlo(of, false, modset->cutoff, sep);
        of.close();
    }
}
//------------------------------------------------------------------------------
void GeoModel::wypisz_raport(string fileName)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        of << strRaport;
        of.close();
    }
}

void GeoModel::wypisz_vario(string fileName)
{
    ofstream of(fileName.c_str());
    if(of.is_open())
    {
        of << curVariogram->get_raport();
        of.close();
    }
}
//------------------------------------------------------------------------------
wektor3d GeoModel::glob2lok(wektor3d wsp)
{
    return (wsp - modset->start)/modset->sp;
}
//------------------------------------------------------------------------------
wektor3d GeoModel::lok2glob(wektor3d wsp)
{
    return wsp*modset->sp+modset->start;
}
//------------------------------------------------------------------------------
wektor3d GeoModel::inv_dist(const wektor3d& pkt, double promien, float potega)
{
    wektor3d x,r, wsp2;
    double val(0.0), waga(0.0), odl(0.0), suma1(0.0), suma2(0.0);

    for (GeoMapa::iterator it = dane->get_begin(); it !=dane->get_end(); ++it)
    {
        x = it->first;
        r = it->second;
        wsp2 = wektor3d(x.x,x.y,x.z);
        odl = dist(pkt,wsp2);

        if (odl<promien)
        {
            val = r.x;
            waga = 1 / (pow(odl,potega));
            suma1 += val*waga;
            suma2 += waga;
        }
    }
    if (suma2)
    return wektor3d( suma1/suma2, 0.0, waga);
    else
    return wektor3d( NULLDAT, NULLDAT, NULLDAT);
}
//------------------------------------------------------------------------------
 void GeoModel::nowy_variogram(double rozmiar_klasy)
 {
     if(curVariogram) delete curVariogram;
     curVariogram = new GeoVariogram(dane,rozmiar_klasy);
 }
//------------------------------------------------------------------------------
 void GeoModel::calc_variogram(double rozmiar_klasy)
 {
     if(curVariogram) curVariogram->recalc(rozmiar_klasy);
 }
//------------------------------------------------------------------------------
