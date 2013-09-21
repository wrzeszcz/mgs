#ifndef GEOMODEL_H
#define GEOMODEL_H

#include "GeoCube.h"
#include "GeoKriging.h"
#include "GeoVariogram.h"
#include "GeoDat.h"
#include "GeoZasoby.h"

using namespace std;

//------------------------------------------------------------------------------
///
/// \brief The GeoModel class
///
class GeoModel
{
public:
    ///
    /// \brief GeoModel
    ///
    GeoModel();
    ~GeoModel();  
    ///
    /// \brief wczytaj_dane
    /// \param fileName
    /// \param sep
    /// \param nowe
    /// \param sred
    ///
    void wczytaj_dane(string fileName,
                      string sep="\t",bool nowe = true, bool sred = true);  
    ///
    /// \brief wczytaj_proj
    /// \param _modset
    /// \param _intep
    ///
    void wczytaj_proj(Mset _modset, Set_interpolacja _intep);   
    ///
    /// \brief wypiszXYZdane
    /// \param os
    ///
    void wypiszXYZdane (ostream &os);
    ///
    /// \brief wypiszXYZmodel
    /// \param os
    /// \param tylkoZasoby
    ///
    void wypiszXYZmodel(ostream &os, bool tylkoZasoby);
    ///
    /// \brief wypisz_dane
    /// \param fileName
    /// \param sep
    ///
    void wypisz_dane  (string fileName, string sep="\t");
    ///
    /// \brief wypisz_model
    /// \param fileName
    /// \param sep
    ///
    void wypisz_model (string fileName, string sep="\t");
    ///
    /// \brief wypisz_zasoby
    /// \param fileName
    /// \param sep
    ///
    void wypisz_zasoby(string fileName, string sep="\t");
    ///
    /// \brief wypisz_raport
    /// \param fileName
    ///
    void wypisz_raport(string fileName);
    ///
    /// \brief wypisz_vario
    /// \param fileName
    ///
    void wypisz_vario (string fileName);
    ///
    /// \brief get_xyz_dane
    /// \param vec
    /// \param centr
    ///
    void get_xyz_dane (std::vector<wektor3d> &vec,bool centr);
    ///
    /// \brief get_xyz_model
    /// \param vec
    /// \param centr
    /// \param zasoby
    ///
    void get_xyz_model(std::vector<wektor3d> &vec,bool centr, bool zasoby);
    ///
    /// \brief ptr_dane
    /// \return
    ///
    GeoDat  *ptr_dane() {return dane;}
    ///
    /// \brief ptr_cube
    /// \return
    ///
    GeoCube *ptr_cube() {return cube;}
    ///
    /// \brief ptr_mset
    /// \return
    ///
    Mset    *ptr_mset() {return modset;}
    ///
    /// \brief ptr_vario
    /// \return
    ///
    GeoVariogram *ptr_vario(){return curVariogram;}
    ///
    /// \brief get_iset
    /// \return
    ///
    Set_interpolacja get_iset(){return last_set;}
    ///
    /// \brief set_iset
    /// \param s
    ///
    void set_iset(Set_interpolacja s){last_set = s;}
    ///
    /// \brief glob2lok
    /// \param wsp
    /// \return
    ///
    wektor3d glob2lok(wektor3d wsp);
    ///
    /// \brief lok2glob
    /// \param wsp
    /// \return
    ///
    wektor3d lok2glob(wektor3d wsp);
    ///
    /// \brief updateModel
    ///
    void updateModel();
    ///
    /// \brief resetModel
    ///
    void resetModel();
    ///
    /// \brief interpolacja
    /// \param ustawienia
    /// \param metod
    /// \return
    ///
    bool interpolacja(Set_interpolacja ustawienia, METODA metod);
    ///
    /// \brief calc_invdist
    /// \param ustawienia
    ///
    void calc_invdist(Set_interpolacja ustawienia);
    ///
    /// \brief calc_okriging
    /// \param ustawienia
    ///
    void calc_okriging(Set_interpolacja ustawienia);  
    ///
    /// \brief policzZasoby
    /// \return
    ///
    wektor3d policzZasoby();
    ///
    /// \brief analizaZasoby
    /// \param _ileKlas
    /// \return
    ///
    std::vector<geo3d> analizaZasoby(int _ileKlas);
    ///
    /// \brief setGeoSet
    /// \param gset
    ///
    void setGeoSet(Mset gset){*modset = gset;}
    ///
    /// \brief raport_add
    /// \param str
    ///
    void raport_add(string str){strRaport.append(str);}
    ///
    /// \brief raport_get
    /// \return
    ///
    string raport_get(){return strRaport;}
    ///
    /// \brief nowy_variogram
    /// \param rozmiar_klasy
    ///
    void nowy_variogram(double rozmiar_klasy);
    ///
    /// \brief calc_variogram
    /// \param rozmiar_klasy
    ///
    void calc_variogram(double rozmiar_klasy);
    ///
    /// \brief get_last_set
    /// \return
    ///
    Set_interpolacja get_last_set(){return last_set;}
    ///
    /// \brief get_progres
    /// \return
    ///
    Progres get_progres(){return progres;}

private:
    ///
    /// \brief inv_dist
    /// \param pkt
    /// \param promien
    /// \param potega
    /// \return
    ///
    wektor3d inv_dist(const wektor3d& pkt, double promien, float potega);
    ///
    /// \brief modset
    ///
    Mset    *modset;
    ///
    /// \brief dane
    ///
    GeoDat  *dane;
    ///
    /// \brief cube
    ///
    GeoCube *cube;
    ///
    /// \brief curVariogram
    ///
    GeoVariogram *curVariogram;
    ///
    /// \brief last_set
    ///
    Set_interpolacja last_set;
    ///
    /// \brief strRaport
    ///
    string  strRaport;
    ///
    /// \brief dist
    ///
    Odl     dist;
    ///
    /// \brief progres
    ///
    Progres progres;
};
//------------------------------------------------------------------------------
#endif // GEOMODEL_H
