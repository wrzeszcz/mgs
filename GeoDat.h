#ifndef GEODAT_H
#define GEODAT_H

#include <map>
#include <fstream>
#include <vector>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>
#include <map>
#include "globalne.h"

using namespace std;
///
/// \brief GeoMapa
///
typedef map<wektor3d,wektor3d> GeoMapa;
///
/// \brief The GeoDat class
///
class GeoDat
{
public:
    ///
    /// \brief GeoDat
    ///
    GeoDat();
    ~GeoDat();
    ///
    /// \brief dodaj_rek
    /// \param rek
    /// \param nadpisz
    ///
    void dodaj_rek (geo3d rek,bool nadpisz);
    ///
    /// \brief dodaj_rek
    /// \param wsp
    /// \param geoval
    /// \param nadpisz
    ///
    void dodaj_rek (wektor3d wsp, wektor3d geoval, bool nadpisz);
    ///
    /// \brief dodaj_rek
    /// \param linia
    /// \param sep
    /// \param nadpisz
    ///
    void dodaj_rek (string linia, string sep, bool nadpisz);
    ///
    /// \brief usun
    /// \param wsp
    ///
    void usun (wektor3d wsp);
    ///
    /// \brief usun
    ///
    void usun ();
    ///
    /// \brief get_rek
    /// \param nr
    /// \return
    ///
    geo3d get_rek(unsigned int nr);
    ///
    /// \brief get_rek
    /// \param wsp
    /// \return
    ///
    geo3d get_rek(wektor3d wsp);
    ///
    /// \brief get_rek
    /// \param git
    /// \return
    ///
    vector<double> get_rek(GeoMapa::iterator git);
    ///
    /// \brief wypisz
    /// \param os
    /// \param sep
    ///
    void wypisz    (std::ostream& os, string sep="\t"); 
    ///
    /// \brief wczytaj
    /// \param is
    ///
    void wczytaj   (istream& is);
    ///
    /// \brief wczytaj
    /// \param is
    /// \param sep
    /// \param sred
    ///
    void wczytaj   (istream& is, string sep="\t", bool sred=true);
    ///
    /// \brief wypisz_xyz
    /// \param os
    /// \param sep
    ///
    void wypisz_xyz(ostream& os, string sep="\t");
    ///
    /// \brief wypisz_xyz
    /// \param vec
    /// \param ofs
    ///
    void wypisz_xyz(vector<wektor3d> &vec, wektor3d ofs);
    ///
    /// \brief wypisz_dat
    /// \param vec
    ///
    void wypisz_dat(vector<geo3d> &vec);
    ///
    /// \brief wypisz_dat
    /// \param vec
    /// \param centr
    /// \param r
    ///
    void wypisz_dat(vector<geo3d> &vec, wektor3d centr, double r);
    ///
    /// \brief wczytaj_plik
    /// \param fileName
    /// \param sep
    /// \param sred
    /// \return
    ///
    bool wczytaj_plik(string fileName, string sep="\t", bool sred=true);
    ///
    /// \brief wypisz_plik
    /// \param fileName
    /// \param sep
    /// \return
    ///
    bool wypisz_plik (string fileName, string sep="\t");
    ///
    /// \brief polacz
    /// \param tab2
    /// \param od_poz
    /// \return
    ///
    int polacz(const GeoDat& tab2, int  od_poz);
    ///
    /// \brief dolacz
    /// \param tab2
    /// \param nadpisz
    /// \return
    ///
    int dolacz(GeoDat& tab2, bool nadpisz);
    ///
    /// \brief calc_min_zakres
    /// \return
    ///
    wektor3d calc_min_zakres();
    ///
    /// \brief calc_max_zakres
    /// \return
    ///
    wektor3d calc_max_zakres();
    ///
    /// \brief update_min_max
    ///
    void update_min_max();
    ///
    /// \brief get_min_zakres
    /// \return
    ///
    wektor3d get_min_zakres(){return min_zakres;}
    ///
    /// \brief get_max_zakres
    /// \return
    ///
    wektor3d get_max_zakres(){return max_zakres;}
    ///
    /// \brief get_min_value
    /// \return
    ///
    wektor3d get_min_value(){return min_value;}
    ///
    /// \brief get_max_value
    /// \return
    ///
    wektor3d get_max_value(){return max_value;}
    ///
    /// \brief get_srodek
    /// \return
    ///
    wektor3d get_srodek();
    ///
    /// \brief get_srodek_A
    /// \return
    ///
    wektor3d get_srodek_A();
    ///
    /// \brief get_wymiary
    /// \return
    ///
    wektor3d get_wymiary();
    ///
    /// \brief get_size
    /// \return
    ///
    int get_size(){return geoMap.size();}
    ///
    /// \brief get_begin
    /// \return
    ///
    GeoMapa::iterator get_begin(){return geoMap.begin();}
    ///
    /// \brief get_end
    /// \return
    ///
    GeoMapa::iterator get_end(){return geoMap.end();}
private:
    ///
    /// \brief min_zakres
    ///
    wektor3d min_zakres;
    ///
    /// \brief max_zakres
    ///
    wektor3d max_zakres;
    ///
    /// \brief min_value
    ///
    wektor3d min_value;
    ///
    /// \brief max_value
    ///
    wektor3d max_value;
    ///
    /// \brief geoMap
    ///
    GeoMapa geoMap;
    ///
    /// \brief it
    ///
    GeoMapa::iterator it;
    ///
    /// \brief dist
    ///
    Odl dist;
    ///
    /// \brief str2double
    /// \param s
    /// \return
    ///
    double str2double(string s)
     {
         stringstream ss("");
         double dd;
         ss << s;
         ss >> dd;
         return dd;
     }
};

#endif // GEODAT_H
