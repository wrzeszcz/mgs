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
GeoModel::GeoModel(): modset(0), dane(0), cube(0), curVariogram(0)
{
    modset = new Mset();
    dane = new GeoDat();
    cube = new GeoCube(modset->start,modset->sp,modset->grid);
    curVariogram = new GeoVariogram(dane,last_set.set_variogram);
    this->raport_add("nowy model \n");
}
GeoModel::~GeoModel()
{
    if (modset) delete modset;
    if (dane) delete dane;
    if (cube) delete cube;
    if (curVariogram) delete curVariogram;
}
//------------------------------------------------------------------------------
void GeoModel::wczytaj_dane(string fileName, string sep, bool nowe, bool sred)
{
    if(!dane) dane = new GeoDat();
    else if (nowe) dane->usun();

    dane->wczytaj_plik(fileName,sep, sred);
    modset->start = dane->get_min_zakres();
    wektor3d w = dane->get_wymiary();

    double d = std::max(std::max(w.x, w.y), w.z);
    double s = ceil(d/50);

    modset->wym = w;
    modset->name = fileName;

    modset->sp=s;
    modset->grid = wektor3i((int)(w.x/s+2),(int)(w.y/s+2),(int)(w.z/s+2));

    modset->max_val = dane->get_max_value();
    modset->min_val = dane->get_min_value();

    updateModel();

    nowy_variogram(last_set.set_variogram);
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

    nowy_variogram(last_set.set_variogram);

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
    err = gZasoby.getError();
    return gZasoby.get_zasoby();
}
//------------------------------------------------------------------------------
std::vector<geo3d> GeoModel::analizaZasoby(int _ileKlas)
{
    GeoZasoby gZasoby(modset,cube);
    err = gZasoby.getError();
    vector<geo3d> analiza = gZasoby.analiza_zasoby(_ileKlas);
    return analiza;
}
//------------------------------------------------------------------------------
string GeoModel::analizaZasobyReport(int _ileKlas, int p)
{
    GeoZasoby gZasoby(modset,cube);
    err = gZasoby.getError();
    vector<geo3d> analiza = gZasoby.analiza_zasoby(_ileKlas);
    if(!analiza.size()) return "brak danych";
    wektor3d suma;
    string aa;
    for(vector<geo3d>::iterator it = analiza.begin(); it!=analiza.end();++it)
        {
           aa += cos2str(it->xyz.x) + "\t";
           aa += cos2str(it->xyz.y) + " - ";
           aa += cos2str(it->xyz.z) + "\t";
           aa += cos2str(it->dat.x) + "\t";
           aa += cos2str(it->dat.y,p) + "\t";
           aa += cos2str(it->dat.z,3) + "\t";
           aa += "\n";
           suma.x += it->dat.x;
           suma.y += it->dat.y;
           suma.z += it->dat.z;

        }
    aa += "w sumie :";
    aa += "\t\t\t"+cos2str(suma.x) + "\t";
    aa += cos2str(suma.y) + "\t";
    aa += cos2str(suma.z) + "\t";
    return aa;
}
//------------------------------------------------------------------------------
std::string GeoModel::recreate_rapor(const std::string& datetimeStr)
{
    this->raport_clear();
    string s;
    if(modset->algorytm == OKRIGING) s = "krigring zwyczajny";
    else if(modset->algorytm == INVDIST) s = "odwrotne odelgłości";
    wektor3d zas = this->policzZasoby();
    this->raport_add
        (
            "MGEOSTAT 0.1 2013 marek.wrzeszcz@hotmail.com\n"
            "RAPORT =========================================================\n"
            + datetimeStr + "\n\n"
            "DANE WEJŚCIOWE =================================================\n"
            "dane: "+ modset->name + "\n"
            "wiersze:\t\t" + cos2str(dane->get_size()) + "\n"
            "początek xyz:\t"+ cos2str(modset->start) + "\n"
            "końcowe  xyz:\t"+ cos2str(dane->get_max_zakres())+"\n"
            "min  wartość:\t"+ cos2str(dane->get_min_value())+"\n"
            "max  wartość:\t"+ cos2str(dane->get_max_value())+"\n\n"
            "MODEL ==========================================================\n"
            "wymiary modelu: \t"+       cos2str(modset->grid) + "\n"
            "rozmiar bloku : \t"+       cos2str(modset->sp) + "\n"
            "początek xyz  :\t"+          cos2str(modset->start) + "\n"
            "wymiary  xyz  :\t"+           cos2str(modset->get_wymiary()) + "\n"
            "ilość bloków  :\t"+         cos2str(modset->get_bloki()) + "\n"
            "objętość modelu: \t"+      cos2str(modset->get_objetosc()) + "\n"
            "gęstość przestrzenna: \t"+ cos2str(modset->gestosc) + "\n"
            "masa modelu: \t"+          cos2str(modset->get_masa()) + "\n"
            "min wartość: \t"+          cos2str(modset->min_val)+"\n"
            "max wartość: \t"+          cos2str(modset->max_val)+"\n\n"
            "ZASOBY =========================================================\n"
            "wartości graniczna (cut-off):\t"+cos2str(modset->cutoff) + "\tppm\n"
            "zasoby wynosza: \t\t"+ cos2str(zas.x) + "\tton\n"+
            "w "+cos2str(zas.y)+" blokach "
            "o objętości "+cos2str(zas.y*modset->sp*modset->sp*modset->sp)+"\n"
            "błąd = +- " + cos2str(err) +" ("+ cos2str( (zas.x!=0.0)?(err/zas.x)*100:0,3)  +"%)\n"
            "dla poszczególnych przedziałow całego modelu:\n"
            + this->analizaZasobyReport(modset->klasy_zas,7) +"\n\n"
            "INTERPOLACJA ====================================================\n"
            "algorytm:\t"+s+"\n"
            "zakres wartości:\t"+cos2str(modset->min_val.x)+ " - " + cos2str(modset->max_val.x)+"\n"
            "zakres błędu:\t"+cos2str(modset->min_val.y)+ " - " + cos2str(modset->max_val.y)+"\n"
            "ilość danych:\t"+cos2str(modset->min_val.z)+ " - " + cos2str(modset->max_val.z)+"\n"
        );
    return raport_get();
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

void GeoModel::wczytaj_model(string fileName, string )
{
    fstream in(fileName.c_str());
    if(in.is_open())
    {
        if( !(in >> *modset)) return;
        in.close();
    }
    else return;
    fstream we(modset->name.c_str());
    if(we.is_open())
    {
        updateModel();
        geo3d tmp;
        while(we >> tmp)
        {
            //cout << tmp << endl;
            cube->setRekGlo(tmp.xyz, tmp.dat);
        }
        we.close();
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
wektor3d GeoModel::inv_dist(const wektor3d& pkt, double promien, double potega)
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
    if (suma2) return wektor3d( suma1/suma2, 0.0, waga);
    else return wektor3d( NULLDAT, NULLDAT, NULLDAT);
}
//------------------------------------------------------------------------------
 void GeoModel::nowy_variogram(wektor3d ust)
 {
     if(curVariogram) delete curVariogram;
     curVariogram = new GeoVariogram(dane,ust);
 }
//------------------------------------------------------------------------------
 void GeoModel::calc_variogram(wektor3d ust)
 {
     progres.pmax = dane->get_size()*dane->get_size();
     progres.pmin = progres.pcur = 0;
     if(curVariogram) curVariogram->recalc(ust);
 }

//------------------------------------------------------------------------------
