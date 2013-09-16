#ifndef GLOBALNE_H
#define GLOBALNE_H
#include <ostream>
#include <sstream>
#include <math.h>

using namespace std;
//------------------------------------------------------------------------------
const double NULLDAT = -1e+20;
//------------------------------------------------------------------------------
enum variogram
{
    EXPONENTIAL=0,
    SPHERICAL=1,
    GAUSSIAN=2
};
enum METODA
{
    INVDIST,
    OKRIGING
};
enum JEDNOSTKI
{
    PPM=0,
    PROCENTY=1,
    GRAMY=2,
    KILOGRAMY=3
};

//------------------------------------------------------------------------------
template<typename T>
string cos2str(T t)
{
    stringstream s;
    s << t;
    return s.str();
}
//------------------------------------------------------------------------------
struct wektor3i
{
    wektor3i() : x(0),y(0),z(0) { }
    wektor3i(int xx, int yy, int zz): x(xx), y(yy), z(zz) { }
    int x,y,z;
};
//------------------------------------------------------------------------------
class wektor3d
{
public:
    wektor3d(): x(0.0),y(0.0),z(0.0){}
    wektor3d(double xx, double yy, double zz): x(xx), y(yy), z(zz){}

    wektor3d operator + (const wektor3d &d)const
    {
        return wektor3d(x+d.x, y+d.y, z+d.z);
    }
    wektor3d operator - (const wektor3d &d)const
    {
        return wektor3d(x-d.x, y-d.y, z-d.z);
    }
    wektor3d operator *(const double &liczba)const
    {
         return wektor3d(x*liczba, y*liczba, z*liczba);
    }
    wektor3d operator /(const double &liczba)const
    {
         return wektor3d(x/liczba, y/liczba, z/liczba);
    }

    bool operator < (const wektor3d &d)const
    {
        if (x != d.x) return (x < d.x);
        if (y != d.y) return (y < d.y);
        if (z != d.z) return (z < d.z);
        return false;
    }
    bool operator ==(const wektor3d &d)const
    {
        return this->x==d.x
             && this->y==d.y
             && this->z==d.z;
    }

    double x,y,z;
};

inline ostream& operator << (ostream& os, const wektor3d &d)
{
    return os << d.x << " " << d.y << " " << d.z;
}
inline istream& operator >> (istream& is, wektor3d& d)
{
    is >> d.x >> d.y >> d.z;
    if(!is) return is;
    return is;
}

inline ostream& operator << (ostream& os, const wektor3i &d)
{
    return os << d.x << " " << d.y << " " << d.z;
}
inline istream& operator >> (istream& is, wektor3i& d)
{
    is >> d.x >> d.y >> d.z;
    if(!is) return is;
    return is;
}
//------------------------------------------------------------------------------
struct Odl
{
    double operator()(const wektor3d &a, const wektor3d &b)
    {
        return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
    }
};
struct Odl2
{
    double operator()(const wektor3d &a, const wektor3d &b)
    {
        return (pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
    }
};
//------------------------------------------------------------------------------
struct geo3d
{
    geo3d(): xyz(0.0,0.0,0.0),dat(0.0,0.0,0.0){}
    geo3d(wektor3d X, wektor3d V): xyz(X),dat(V){}
    wektor3d xyz;
    wektor3d dat;
};
inline ostream& operator << (ostream& os, const geo3d &d)
{
    return os << d.xyz << " " << d.dat;
}
//------------------------------------------------------------------------------
// funktatory
struct W3d_odl
{
    double operator()(const wektor3d &a, const wektor3d &b)
    {
        return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
    }
};
//------------------------------------------------------------------------------
struct G3d_comp_dat_z
{
    bool operator()(const geo3d &a, const geo3d &b)
    {
        return a.dat.z < b.dat.z;
    }
};
//------------------------------------------------------------------------------
struct G3d_comp_odl_pkt
{
    G3d_comp_odl_pkt(const wektor3d &pkt):
        p(pkt)
    {

    }

    bool operator()(const geo3d &a, const geo3d &b)
    {
        return ( odl(a.xyz, p) < odl(b.xyz, p) );
    }
    wektor3d p;
    Odl2 odl;
};
//------------------------------------------------------------------------------
struct W3d_comp_x
{
    bool operator()(const wektor3d &a, const wektor3d &b)
    {
        return a.x < b.x;
    }
};
//------------------------------------------------------------------------------
struct W3d_comp_y
{
    bool operator()(const wektor3d &a, const wektor3d &b)
    {
        return a.y < b.y;
    }
};
//------------------------------------------------------------------------------
struct W3d_comp_z
{
    bool operator()(const wektor3d &a, const wektor3d &b)
    {
        return a.z < b.z;
    }
};
//------------------------------------------------------------------------------
struct Mset
{
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
inline istream& operator >> (istream& is, Mset& d)
{
    int jedn;
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
        case 0: d.jednostki == PPM; break;
        case 1: d.jednostki == PROCENTY; break;
        case 2: d.jednostki == GRAMY; break;
        case 3: d.jednostki == KILOGRAMY; break;
        defoult: break;
   }

    if(!is) return is;
    return is;
}
//------------------------------------------------------------------------------
struct DataInfo
{
    wektor3d zakres_min;
    wektor3d zakres_max;
};
//------------------------------------------------------------------------------
struct Vset
{
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
struct Set_interpolacja
{
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
struct Cube2win
{
    wektor3d operator()(const wektor3d &a, const Mset &set)
    {
        return a*set.sp - set.wym/2;
    }
};
//------------------------------------------------------------------------------
struct Win2cube
{
    wektor3d operator()(const wektor3d &a, const Mset &set)
    {
        return (a + set.wym/2) / set.sp;
    }
};
//------------------------------------------------------------------------------
struct Glob2lok
{
    wektor3d operator()(const wektor3d &a, const Mset &set)
    {
        return (a - set.start) / set.sp;
    }
};
//------------------------------------------------------------------------------
struct Lok2glob
{
   wektor3d operator()(const wektor3d &a, const Mset &set)
   {
       return a*set.sp + set.start;
   }
};
//------------------------------------------------------------------------------
struct Cube2glo
{

};
//------------------------------------------------------------------------------
struct Glo2cube
{

};
//------------------------------------------------------------------------------
struct Progres
{
    Progres():
        pmin(0),
        pmax(0),
        pcur(0)
    {

    }
    Progres(int _min, int _max, int _cur):
        pmin(_min),
        pmax(_max),
        pcur(_cur)
    {

    }
    float get_part()
    {
        return float(pcur-pmin)/float(pmax-pmin);
    }

    int pmin,pmax,pcur;
};
//------------------------------------------------------------------------------
#endif // GLOBALNE_H
