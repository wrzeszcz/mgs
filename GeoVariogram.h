#ifndef GEOVARIOGRAM_H
#define GEOVARIOGRAM_H

#include "GeoDat.h"
#include "globalne.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class GeoVariogram
{
public:
    GeoVariogram(GeoDat *dane, double rozmiar_klasy);
    GeoVariogram(GeoDat *dane);

    void recalc(double rozmiar_klasy);
    void recalc();
    void set_dane(GeoDat *dane, double rozmiar_klasy);
    void set_dane(GeoDat *dane);

    string get_raport();
    void wypisz_dist_delta(string filename);
    std::vector<wektor3d> &get_klasy(){return dist_delta_klas;}

private:

    double auto_rozmiar(const std::vector<wektor3d> &delty, int ile);
    std::vector<wektor3d> dist_delta;
    std::vector<wektor3d> dist_delta_klas;
    std::vector<wektor3d>::iterator gIt;
    GeoDat *dane;
    double rozmiar;
    Odl dist;
};

#endif // GEOVARIOGRAM_H
