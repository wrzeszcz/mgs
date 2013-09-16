#include "GeoStat.h"

GeoStat::GeoStat()
{
}
GeoStat::GeoStat(GeoDat *dane)
{
    dat = dane;
}

wektor3d GeoStat::inv_dist(const wektor3d& pkt, double promien, int potega)
{
    wektor3d x,r;
    double val, waga, odl, suma1(0.0), suma2(0.0);

    wektor3d wsp2;

    for (GeoMapa::iterator it = dat->get_begin(); it !=dat->get_end(); ++it)
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
    return wektor3d( suma1/suma2, 2.5, 0.0);
    else
    return wektor3d( 0.0, 2.5, 0.0);

}

