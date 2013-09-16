#ifndef GEOZASOBY_H
#define GEOZASOBY_H

#include "GeoModel.h"
#include "globalne.h"

typedef std::pair<double,double> KlasaZas;
typedef std::vector<KlasaZas> KlasyZas;

class GeoZasoby
{
public:
    GeoZasoby(Mset *_modelSet, GeoCube * _geoCube);
    ~GeoZasoby();

    wektor3d przelicz_zasoby();
    wektor3d przelicz_zasoby(double _minp, double _maxp);

    std::vector<geo3d> analiza_zasoby();
    std::vector<geo3d> analiza_zasoby(int _ileKlas);

    wektor3d get_zasoby(){return zasoby;}
    void set_klasy(KlasyZas kl){klasyZas = kl;}

private:
    void ustaw_klasy();
    wektor3d policzBlok(wektor3d parametry, double rozmiar);

    Mset *modelSet;
    GeoCube *geoCube;
    wektor3d zasoby;
    std::vector<geo3d> wynikAnalizy;
    KlasyZas klasyZas;
    int ileKlas;
};

#endif // GEOZASOBY_H
