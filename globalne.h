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

#ifndef GLOBALNE_H
#define GLOBALNE_H
#include <ostream>
#include <sstream>
#include <math.h>

using namespace std;
//------------------------------------------------------------------------------
const double NULLDAT = -1e+20;
//------------------------------------------------------------------------------
///
/// \brief The variogram enum
///
enum variogram
{
    EXPONENTIAL=0,
    SPHERICAL=1,
    GAUSSIAN=2
};
///
/// \brief The METODA enum
///
enum METODA
{
    INVDIST,
    OKRIGING
};
///
/// \brief The JEDNOSTKI enum
///
enum JEDNOSTKI
{
    PPM=0,
    PROCENTY=1,
    GRAMY=2,
    KILOGRAMY=3
};
//------------------------------------------------------------------------------
template<typename T> string cos2str(T t)
{
    stringstream s;
    s << t;
    return s.str();
}
//------------------------------------------------------------------------------
///
/// \brief The wektor3i struct
///
struct wektor3i
{
    ///
    /// \brief wektor3i
    ///
    wektor3i() : x(0),y(0),z(0) { }
    ///
    /// \brief wektor3i
    /// \param xx
    /// \param yy
    /// \param zz
    ///
    wektor3i(int xx, int yy, int zz): x(xx), y(yy), z(zz) { }
    int x,y,z;
};
//------------------------------------------------------------------------------
///
/// \brief The wektor3d class
///
class wektor3d
{
public:
    ///
    /// \brief wektor3d
    ///
    wektor3d(): x(0.0),y(0.0),z(0.0){}
    ///
    /// \brief wektor3d
    /// \param xx
    /// \param yy
    /// \param zz
    ///
    wektor3d(double xx, double yy, double zz): x(xx), y(yy), z(zz){}
    ///
    /// \brief operator +
    /// \param d
    /// \return
    ///
    wektor3d operator + (const wektor3d &d)const
    {
        return wektor3d(x+d.x, y+d.y, z+d.z);
    }
    ///
    /// \brief operator -
    /// \param d
    /// \return
    ///
    wektor3d operator - (const wektor3d &d)const
    {
        return wektor3d(x-d.x, y-d.y, z-d.z);
    }
    ///
    /// \brief operator *
    /// \param liczba
    /// \return
    ///
    wektor3d operator *(const double &liczba)const
    {
         return wektor3d(x*liczba, y*liczba, z*liczba);
    }
    ///
    /// \brief operator /
    /// \param liczba
    /// \return
    ///
    wektor3d operator /(const double &liczba)const
    {
         return wektor3d(x/liczba, y/liczba, z/liczba);
    }
    ///
    /// \brief operator <
    /// \param d
    /// \return
    ///
    bool operator < (const wektor3d &d)const
    {
        if (x != d.x) return (x < d.x);
        if (y != d.y) return (y < d.y);
        if (z != d.z) return (z < d.z);
        return false;
    }
    ///
    /// \brief operator ==
    /// \param d
    /// \return
    ///
    bool operator ==(const wektor3d &d)const
    {
        return this->x==d.x
             && this->y==d.y
             && this->z==d.z;
    }

    double x,y,z;
};
///
/// \brief operator <<
/// \param os
/// \param d
/// \return
///
inline ostream& operator << (ostream& os, const wektor3d &d)
{
    os.setf(ios::fixed);
    os.precision(6);
    return os << d.x << " " << d.y << " " << d.z;
}
///
/// \brief operator >>
/// \param is
/// \param d
/// \return
///
inline istream& operator >> (istream& is, wektor3d& d)
{
    is >> d.x >> d.y >> d.z;
    if(!is) return is;
    return is;
}
///
/// \brief operator <<
/// \param os
/// \param d
/// \return
///
inline ostream& operator << (ostream& os, const wektor3i &d)
{
    return os << d.x << " " << d.y << " " << d.z;
}
///
/// \brief operator >>
/// \param is
/// \param d
/// \return
///
inline istream& operator >> (istream& is, wektor3i& d)
{
    is >> d.x >> d.y >> d.z;
    if(!is) return is;
    return is;
}
//------------------------------------------------------------------------------
///
/// \brief The Odl struct
///
struct Odl
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    double operator()(const wektor3d &a, const wektor3d &b)
    {
        return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
    }
};
///
/// \brief The Odl2 struct
///
struct Odl2
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    double operator()(const wektor3d &a, const wektor3d &b)
    {
        return (pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
    }
};
//------------------------------------------------------------------------------
///
/// \brief The geo3d struct
///
struct geo3d
{
    ///
    /// \brief geo3d
    ///
    geo3d(): xyz(0.0,0.0,0.0),dat(0.0,0.0,0.0){}
    ///
    /// \brief geo3d
    /// \param X
    /// \param V
    ///
    geo3d(wektor3d X, wektor3d V): xyz(X),dat(V){}
    ///
    /// \brief xyz
    ///
    wektor3d xyz;
    ///
    /// \brief dat
    ///
    wektor3d dat;
};
///
/// \brief operator <<
/// \param os
/// \param d
/// \return
///
inline ostream& operator << (ostream& os, const geo3d &d)
{
    return os << d.xyz << " " << d.dat;
}
//------------------------------------------------------------------------------
// funktatory
///
/// \brief The W3d_odl struct
///
struct W3d_odl
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    double operator()(const wektor3d &a, const wektor3d &b)
    {
        return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
    }
};
//------------------------------------------------------------------------------
///
/// \brief The G3d_comp_dat_z struct
///
struct G3d_comp_dat_z
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    bool operator()(const geo3d &a, const geo3d &b)
    {
        return a.dat.z < b.dat.z;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The G3d_comp_odl_pkt struct
///
struct G3d_comp_odl_pkt
{
    ///
    /// \brief G3d_comp_odl_pkt
    /// \param pkt
    ///
    G3d_comp_odl_pkt(const wektor3d &pkt): p(pkt) {}
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    bool operator()(const geo3d &a, const geo3d &b)
    {
        return ( odl(a.xyz, p) < odl(b.xyz, p) );
    }
    ///
    /// \brief p
    ///
    wektor3d p;
    ///
    /// \brief odl
    ///
    Odl2 odl;
};
//------------------------------------------------------------------------------
///
/// \brief The W3d_comp_x struct
///
struct W3d_comp_x
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    bool operator()(const wektor3d &a, const wektor3d &b)
    {
        return a.x < b.x;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The W3d_comp_y struct
///
struct W3d_comp_y
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    bool operator()(const wektor3d &a, const wektor3d &b)
    {
        return a.y < b.y;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The W3d_comp_z struct
///
struct W3d_comp_z
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param b
    /// \return
    ///
    bool operator()(const wektor3d &a, const wektor3d &b)
    {
        return a.z < b.z;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The Mset struct
///
struct Mset
{
    ///
    /// \brief Mset
    ///
    Mset():
        grid(6,6,3),
        start(0.0,0.0,0.0),
        start_grid(0.0,0.0,0.0),
        wym(100,100,40),
        name("pusty"),
        sp(20),
        cutoff(0.0),
        flag(true),
        min_val(0.0,0.0,0.0),
        max_val(0.0,0.0,0.0),
        gestosc(2.5),
        jednostki(PPM)
    {

    }
    ///
    /// \brief Mset
    /// \param cub
    /// \param pocz
    /// \param wymiary
    /// \param nazwa
    /// \param spa
    /// \param ct
    /// \param fl
    /// \param min_dat
    /// \param max_dat
    /// \param gest
    /// \param jedn
    ///
    Mset (wektor3i cub, wektor3d pocz, wektor3d wymiary, string nazwa,
          double spa,double ct, bool fl, wektor3d min_dat, wektor3d max_dat,
          double gest, JEDNOSTKI jedn):
        grid(cub),
        start(pocz),
        start_grid(pocz),
        wym(wymiary),
        name(nazwa),
        sp(spa),
        cutoff(ct),
        flag(fl),
        min_val(min_dat),
        max_val(max_dat),
        gestosc(gest),
        jednostki(jedn)
    {

    }

    int get_bloki(){return grid.x*grid.y*grid.z;}

    double get_objetosc(){return get_bloki() * sp * sp * sp;}

    double get_masa(){return get_objetosc() * gestosc;}

    wektor3d get_wymiary(){return wektor3d(grid.x * sp, grid.y*sp,grid.z *sp);}

    wektor3i grid;
    wektor3d start;
    wektor3d start_grid;
    wektor3d wym;
    string name;
    double sp;
    double cutoff;
    bool   flag;
    wektor3d min_val;
    wektor3d max_val;
    double gestosc;
    JEDNOSTKI jednostki;
};
///
/// \brief operator <<
/// \param os
/// \param d
/// \return
///
inline ostream& operator << (ostream& os, const Mset &d)
{
    return os << d.grid << endl
              << d.start << endl
              << d.wym << endl
              << d.name << endl
              << d.sp << endl
              << d.cutoff << endl
              << d.flag << endl
              << d.min_val << endl
              << d.max_val << endl
              << d.gestosc << endl
              << d.jednostki << endl;
}
///
/// \brief operator >>
/// \param is
/// \param d
/// \return
///
inline istream& operator >> (istream& is, Mset& d)
{
    if(!is) return is;
    int jedn = 0;

    is >> d.grid
       >> d.start
       >> d.wym
       >> d.name
       >> d.sp
       >> d.cutoff
       >> d.flag
       >> d.min_val
       >> d.max_val
       >> d.gestosc
       >> jedn;

    switch(jedn)
    {
        case 0: d.jednostki = PPM; break;
        case 1: d.jednostki = PROCENTY; break;
        case 2: d.jednostki = GRAMY; break;
        case 3: d.jednostki = KILOGRAMY; break;
        default: break;
    }

    return is;
}
//------------------------------------------------------------------------------
///
/// \brief The DataInfo struct
///
struct DataInfo
{
    wektor3d zakres_min;
    wektor3d zakres_max;
};
//------------------------------------------------------------------------------
///
/// \brief The Vset struct
///
struct Vset
{
    ///
    /// \brief Vset
    ///
    Vset():
        zakres(true),
        dane(true),
        siatka(true),
        wezel(false),
        zasoby(true),
        perspektywa(true),
        tlo(true),
        interp(true),
        error_map(false)
    {

    }
    bool zakres;
    bool dane;
    bool siatka;
    bool wezel;
    bool zasoby;
    bool perspektywa;
    bool tlo;
    bool interp;
    bool error_map;
};
//------------------------------------------------------------------------------
///
/// \brief The Set_interpolacja struct
///
struct Set_interpolacja
{
    ///
    /// \brief Set_interpolacja
    ///
    Set_interpolacja():
        vario(SPHERICAL),
        nuget_c0(0.0),
        sill_c1(0.1),
        range_a(50.0),
        potega(2.0),
        promien(50.0),
        min_ilosc(1),
        max_ilosc(32),
        rozmiar_klasy(1.0)
    {

    }
    ///
    /// \brief toString
    /// \return
    ///
    string toString()
    {
        stringstream ret;
        ret << endl << "ustawienia interpolacji" << endl
            << "wariogam: " << vario << endl
            << "nugget     : " << nuget_c0 << endl
            << "sill            : " << sill_c1 << endl
            << "range      : " << range_a << endl
            << "potęga    : " << potega << endl
            << "promień     : " << promien << endl
            << "min_ilosc: " << min_ilosc << endl
            << "max_ilosc : " << max_ilosc << endl;

        return ret.str();
    }

    variogram vario;   
    double nuget_c0;
    double sill_c1;
    double range_a;
    float potega;
    double promien;
    int min_ilosc;
    int max_ilosc;
    double rozmiar_klasy;
};
///
/// \brief operator <<
/// \param os
/// \param d
/// \return
///
inline ostream& operator << (ostream& os, const Set_interpolacja &d)
{
    return os << d.vario << endl
              << d.nuget_c0 << endl
              << d.sill_c1 << endl
              << d.range_a << endl
              << d.potega << endl
              << d.promien << endl
              << d.min_ilosc << endl
              << d.max_ilosc << endl
              << d.rozmiar_klasy << endl;
}
//------------------------------------------------------------------------------
///
/// \brief The Cube2win struct
///
struct Cube2win
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param set
    /// \return
    ///
    wektor3d operator()(const wektor3d &a, const Mset &set)
    {
        return a*set.sp - set.wym/2;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The Win2cube struct
///
struct Win2cube
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param set
    /// \return
    ///
    wektor3d operator()(const wektor3d &a, const Mset &set)
    {
        return (a + set.wym/2) / set.sp;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The Glob2lok struct
///
struct Glob2lok
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param set
    /// \return
    ///
    wektor3d operator()(const wektor3d &a, const Mset &set)
    {
        return (a - set.start) / set.sp;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The Lok2glob struct
///
struct Lok2glob
{
    ///
    /// \brief operator ()
    /// \param a
    /// \param set
    /// \return
    ///
    wektor3d operator()(const wektor3d &a, const Mset &set)
    {
       return a*set.sp + set.start;
    }
};
//------------------------------------------------------------------------------
///
/// \brief The Progres struct
///
struct Progres
{
    ///
    /// \brief Progres
    ///
    Progres():pmin(0), pmax(0), pcur(0) {}
    ///
    /// \brief Progres
    /// \param _min
    /// \param _max
    /// \param _cur
    ///
    Progres(int _min, int _max, int _cur):pmin(_min),pmax(_max),pcur(_cur){}
    ///
    /// \brief get_part
    /// \return
    ///
    float get_part()
    {
        return float(pcur-pmin)/float(pmax-pmin);
    }
    int pmin,pmax,pcur;
};
//------------------------------------------------------------------------------
#endif // GLOBALNE_H
