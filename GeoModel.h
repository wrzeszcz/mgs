#ifndef GEOMODEL_H
#define GEOMODEL_H

#include "GeoCube.h"
#include "GeoKriging.h"
#include "GeoVariogram.h"
#include "GeoDat.h"
#include "GeoZasoby.h"

using namespace std;

//------------------------------------------------------------------------------
class GeoModel
{
public:
    GeoModel();
    ~GeoModel();

    void wczytaj_dane(string fileName,
                      string sep="\t",bool nowe = true, bool sred = true);
    void wczytaj_proj(Mset _modset, Set_interpolacja _intep);

    void wypiszXYZdane (ostream &os);
    void wypiszXYZmodel(ostream &os, bool tylkoZasoby);

    void wypisz_dane  (string fileName, string sep="\t");
    void wypisz_model (string fileName, string sep="\t");
    void wypisz_zasoby(string fileName, string sep="\t");
    void wypisz_raport(string fileName);
    void wypisz_vario (string fileName);

    void get_xyz_dane (std::vector<wektor3d> &vec,bool centr);
    void get_xyz_model(std::vector<wektor3d> &vec,bool centr, bool zasoby);

    GeoDat  *ptr_dane() {return dane;}
    GeoCube *ptr_cube() {return cube;}
    Mset    *ptr_mset() {return modset;}
    GeoVariogram *ptr_vario(){return curVariogram;}
    Set_interpolacja get_iset(){return last_set;}
    void set_iset(Set_interpolacja s){last_set = s;}

    wektor3d glob2lok(wektor3d wsp);
    wektor3d lok2glob(wektor3d wsp);

    void updateModel();
    void resetModel();

    bool interpolacja(Set_interpolacja ustawienia,METODA metod);
    void calc_invdist(Set_interpolacja ustawienia);
    void calc_okriging(Set_interpolacja ustawienia);  

    wektor3d policzZasoby();
    std::vector<geo3d> analizaZasoby(int _ileKlas);

    void setGeoSet(Mset gset){*modset = gset;}

    void raport_add(string str){strRaport.append(str);}
    string raport_get(){return strRaport;}

    void nowy_variogram(double rozmiar_klasy);
    void calc_variogram(double rozmiar_klasy);
    Set_interpolacja get_last_set(){return last_set;}

    Progres get_progres(){return progres;}

private:

    wektor3d inv_dist(const wektor3d& pkt, double promien, float potega);

    Mset    *modset;
    GeoDat  *dane;
    GeoCube *cube;
    GeoVariogram *curVariogram;
    Set_interpolacja last_set;
    string  strRaport;
    Odl     dist;
    Progres progres;
};
//------------------------------------------------------------------------------
#endif // GEOMODEL_H
