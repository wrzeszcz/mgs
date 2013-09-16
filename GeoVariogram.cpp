#include "GeoVariogram.h"
//--------------------------------------------------------------------
GeoVariogram::GeoVariogram(GeoDat *_dane, double rozmiar_klasy):
    dane(_dane),
    rozmiar(rozmiar_klasy)
{
    recalc();
}
//--------------------------------------------------------------------
GeoVariogram::GeoVariogram(GeoDat *_dane):
    dane(_dane)
{
    rozmiar = auto_rozmiar(dist_delta,100);
    recalc();
}
//--------------------------------------------------------------------
void GeoVariogram::recalc(double rozmiar_klasy)
{
    rozmiar = rozmiar_klasy;
    recalc();
}
//--------------------------------------------------------------------
void GeoVariogram::recalc()
{
    GeoMapa::iterator it = dane->get_begin();
    GeoMapa::iterator end = dane->get_end();
    GeoMapa::iterator jt;

    wektor3d pocz = dane->get_min_zakres();
    wektor3d koni = dane->get_max_zakres();
    double max_dist = dist(pocz,koni);

    dist_delta.clear();
    dist_delta_klas.clear();

    for(; it != end; ++it)
        for(jt = it ; jt != end; ++jt)
        {
            wektor3d tmp;
            tmp.x = dist( it->first , jt->first );
            tmp.y = (it->second.x - jt->second.x) * (it->second.x - jt->second.x);
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
}
//--------------------------------------------------------------------
void GeoVariogram::set_dane(GeoDat *_dane, double rozmiar_klasy)
{
    dane = _dane;
    rozmiar = rozmiar_klasy;
}
//--------------------------------------------------------------------
void GeoVariogram::set_dane(GeoDat *_dane)
{
    dane = _dane;
    rozmiar = auto_rozmiar(dist_delta,100);
}
//--------------------------------------------------------------------
string GeoVariogram::get_raport()
{
    stringstream ss;
    for(unsigned i=0; i <  dist_delta_klas.size(); ++i)
    {
        ss << dist_delta_klas[i].x << "\t"
           << dist_delta_klas[i].y << "\t"
           << dist_delta_klas[i].z << endl;
    }
    return ss.str();
}
//--------------------------------------------------------------------
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
//--------------------------------------------------------------------
double GeoVariogram::auto_rozmiar(const std::vector<wektor3d> &delty, int ile)
{
    return ( delty[delty.size()-1].x / ile );
}
//--------------------------------------------------------------------

