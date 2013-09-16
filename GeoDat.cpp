#include "GeoDat.h"
//------------------------------------------------------------------------------
GeoDat::GeoDat()
{
}
GeoDat::~GeoDat()
{

}
//------------------------------------------------------------------------------
void GeoDat::dodaj_rek (geo3d rek,bool nadpisz)
{
    dodaj_rek(rek.xyz, rek.dat, nadpisz);
}
//------------------------------------------------------------------------------
void GeoDat::dodaj_rek (wektor3d wsp, wektor3d geoval, bool nadpisz)
{
    if(nadpisz) geoMap[wsp]=geoval;
    else if (geoMap.find(wsp) == geoMap.end()) geoMap[wsp]=geoval;
    else geoMap[wsp] = (geoMap[wsp]+geoval) / 2;

    if(geoMap.size()==1)
    {
        it = geoMap.begin();
        min_zakres = max_zakres = it->first;
        min_value  = max_value  = it->second;
    }
    else
    {
        if(min_zakres.x > wsp.x) min_zakres.x = wsp.x;
        if(min_zakres.y > wsp.y) min_zakres.y = wsp.y;
        if(min_zakres.z > wsp.z) min_zakres.z = wsp.z;

        if(max_zakres.x < wsp.x) max_zakres.x = wsp.x;
        if(max_zakres.y < wsp.y) max_zakres.y = wsp.y;
        if(max_zakres.z < wsp.z) max_zakres.z = wsp.z;

        if(min_value.x > geoMap[wsp].x) min_value.x = geoMap[wsp].x;
        if(min_value.y > geoMap[wsp].y) min_value.y = geoMap[wsp].y;
        if(min_value.z > geoMap[wsp].z) min_value.z = geoMap[wsp].z;

        if(max_value.x < geoMap[wsp].x) max_value.x = geoMap[wsp].x;
        if(max_value.y < geoMap[wsp].y) max_value.y = geoMap[wsp].y;
        if(max_value.z < geoMap[wsp].z) max_value.z = geoMap[wsp].z;
    }
}
//------------------------------------------------------------------------------
void GeoDat::dodaj_rek (string ln, string sep, bool nadpisz)
{
    int sepS=sep.size();
    if (sepS==0 || ln.size()==0) return;
    unsigned int licz = 0;
    unsigned int poz1 = 0;
    unsigned int poz2 = ln.find(sep,poz1);
    wektor3d tmp1, tmp2;
    tmp1.x = str2double(ln.substr(poz1,poz2));
    while (poz2<ln.size() && (poz2+sepS)<ln.size() && licz < 5)
    {
        poz1 = poz2+sepS;
        poz2 = ln.find(sep,poz1);
        switch(licz)
        {
        case(0): tmp1.y = str2double(ln.substr(poz1,poz2-poz1));break;
        case(1): tmp1.z = str2double(ln.substr(poz1,poz2-poz1));break;
        case(2): tmp2.x = str2double(ln.substr(poz1,poz2-poz1));break;
        case(3): tmp2.y = str2double(ln.substr(poz1,poz2-poz1));break;
        case(4): tmp2.z = str2double(ln.substr(poz1,poz2-poz1));break;
        }
        licz++;
    }
    dodaj_rek(tmp1,tmp2,nadpisz);
}
//------------------------------------------------------------------------------
void GeoDat::usun(wektor3d wsp)
{
    it = geoMap.find(wsp);
    if (it != geoMap.end())
    {
        geoMap.erase(it);
        update_min_max();
    }
}
//------------------------------------------------------------------------------
void GeoDat::usun ()
{
    geoMap.clear();
    min_zakres = max_zakres = min_value = max_value = wektor3d();
}
//------------------------------------------------------------------------------
geo3d GeoDat::get_rek(unsigned nr)
{
    geo3d ret;
    if (nr < geoMap.size())
    {
        int licz=0;
        for(it=geoMap.begin();it !=geoMap.end(); ++it)
        {
            if(licz=nr) ret = geo3d(it->first,it->second);
            ++licz;
        }
    }
    return ret;
}
//------------------------------------------------------------------------------
geo3d GeoDat::get_rek(wektor3d wsp)
{
    geo3d ret;
    it = geoMap.find(wsp);
    if (it != geoMap.end()) ret = geo3d(it->first,it->second);
    return ret;
}
//------------------------------------------------------------------------------
std::vector<double> GeoDat::get_rek(GeoMapa::iterator git)
{
    std::vector<double> ret;
    ret.push_back(git->first.x);
    ret.push_back(git->first.y);
    ret.push_back(git->first.z);
    ret.push_back(git->second.x);
    ret.push_back(git->second.y);
    ret.push_back(git->second.z);
    return ret;
}
//--------------------------------------------------------------------
void GeoDat::wypisz(std::ostream& os, string s)
{
    wektor3d w,d;
    os.setf(ios::fixed);
    os.precision(10);
    for(it=geoMap.begin();it !=geoMap.end(); ++it)
    {
        w = it->first;
        d = it->second;
        os << w.x << s << w.y << s << w.z << s << d.x << s << d.y << s << d.z << endl;
    }
}
//------------------------------------------------------------------------------
void GeoDat::wypisz_xyz (std::ostream& os, string s)
{
    wektor3d w;
    os.setf(ios::fixed);
    os.precision(10);
    for(it = geoMap.begin();it !=geoMap.end(); ++it)
    {
        w = it->first;
        os << w.x << s << w.y << s << w.z << endl;
    }
}
//------------------------------------------------------------------------------
void GeoDat::wypisz_xyz(std::vector<wektor3d> &vec, wektor3d ofs)
{
    wektor3d w;
    vec.clear();
    for(it=geoMap.begin();it !=geoMap.end(); ++it)
    {
        w = it->first;
        vec.push_back(wektor3d(w.x,w.y,w.z)-ofs);
    }
}
//------------------------------------------------------------------------------
void GeoDat::wypisz_dat(std::vector<geo3d> &vec)
{
    wektor3d w,d;
    geo3d tmp;
    vec.clear();
    it=geoMap.begin();
    for(;it !=geoMap.end(); ++it)
    {
        w = it->first;
        d = it->second;
        tmp.xyz = w;
        tmp.dat = d;
        vec.push_back(tmp);
    }
}
//------------------------------------------------------------------------------
void GeoDat::wypisz_dat(std::vector<geo3d> &vec, wektor3d centr, double promien)
{
    wektor3d w,d;
    geo3d tmp;
    vec.clear();
    it = geoMap.begin();
    for (; it != geoMap.end(); ++it)
    {
       w = it->first;
       double odleg = dist(centr,w);
       if ( odleg > promien ) continue;
       d = it->second;
       tmp.xyz = w;
       tmp.dat = d;
       tmp.dat.z = odleg;
       vec.push_back(tmp);
    }
}
//------------------------------------------------------------------------------
void GeoDat::wczytaj(std::istream& is)
{
    double x(0.0),y(0.0),z(0.0),a(0.0),b(0.0),c(0.);
    while(is >> x >> y >> z >> a >> b >> c)
    {
        dodaj_rek(wektor3d(x,y,z),wektor3d(a,b,c),true);
    }
}
//------------------------------------------------------------------------------
void GeoDat::wczytaj(istream& is, string s, bool sred)
{
    std::string linia;
    while(!is.eof())
    {
        getline   (is, linia);
        dodaj_rek (linia, s, !sred);
    }
}
//------------------------------------------------------------------------------
bool GeoDat::wczytaj_plik(string fileName, string sep, bool sred)
{
    ifstream plik(fileName.c_str()) ;
    if (plik.is_open())
    {
        wczytaj (plik,sep,sred);
        plik.close();
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------
bool GeoDat::wypisz_plik (string fileName, string sep)
{
    ofstream plik(fileName.c_str());
    if (!plik.is_open()) return false;
    wypisz (plik,sep);
    plik.close();
    return true;
}
//------------------------------------------------------------------------------
int GeoDat::polacz(const GeoDat& tab2, int  od_poz)
{
    return 0;
}
//------------------------------------------------------------------------------
int GeoDat::dolacz(GeoDat& tab2, bool nadpisz)
{
    GeoMapa::iterator git;
    git = tab2.get_begin();
    for(; git!=tab2.get_end(); ++git)
        dodaj_rek(git->first,git->second,nadpisz);
    return 0;
}
//------------------------------------------------------------------------------
wektor3d GeoDat::calc_min_zakres()
{
    if (!geoMap.size()) return wektor3d();
    double x(0.0),y(0.0),z(0.0);
    it = geoMap.begin();
    wektor3d w = it->first;
    x = w.x;
    y = w.y;
    z = w.z;
    for(it; it!=geoMap.end(); ++it)
    {
        w = it->first;
        if ( x > w.x ) x = w.x;
        if ( y > w.y ) y = w.y;
        if ( z > w.z ) z = w.z;
    }
    return wektor3d(x,y,z);
}
//------------------------------------------------------------------------------
wektor3d GeoDat::calc_max_zakres()
{
    if (!geoMap.size()) return wektor3d();
    double x(0.0),y(0.0),z(0.0);
    it = geoMap.begin();
    wektor3d w = it->first;
    x = w.x;
    y = w.y;
    z = w.z;
    for(it; it!=geoMap.end(); ++it)
    {
        w = it->first;
        if ( x < w.x ) x = w.x;
        if ( y < w.y ) y = w.y;
        if ( z < w.z ) z = w.z;
    }
    return wektor3d(x,y,z);
}
//------------------------------------------------------------------------------
void GeoDat::update_min_max()
{
    it = geoMap.begin();
    wektor3d wsp,dat;
    if(geoMap.size()==1)
    {
        min_zakres = max_zakres = it->first;
        min_value  = max_value  = it->second;
    }
    else
    {
        for(it; it!=geoMap.end(); ++it)
        {
            wsp = it->first;
            dat = it->second;
            if(min_zakres.x > wsp.x) min_zakres.x = wsp.x;
            if(min_zakres.y > wsp.y) min_zakres.y = wsp.y;
            if(min_zakres.z > wsp.z) min_zakres.z = wsp.z;

            if(max_zakres.x < wsp.x) max_zakres.x = wsp.x;
            if(max_zakres.y < wsp.y) max_zakres.y = wsp.y;
            if(max_zakres.z < wsp.z) max_zakres.z = wsp.z;

            if(min_value.x > dat.x) min_value.x = dat.x;
            if(min_value.y > dat.y) min_value.y = dat.y;
            if(min_value.z > dat.z) min_value.z = dat.z;

            if(max_value.x < dat.x) max_value.x = dat.x;
            if(max_value.y < dat.y) max_value.y = dat.y;
            if(max_value.z < dat.z) max_value.z = dat.z;
        }
    }
}
//--------------------------------------------------------------------
wektor3d GeoDat::get_srodek()
{
    return (get_max_zakres()-get_min_zakres())*0.5;
}
//--------------------------------------------------------------------
wektor3d GeoDat::get_srodek_A()
{
    return (get_srodek()+get_min_zakres());
}
//--------------------------------------------------------------------
wektor3d GeoDat::get_wymiary()
{
    return (get_max_zakres()-get_min_zakres());
}
//------------------------------------------------------------------------------
