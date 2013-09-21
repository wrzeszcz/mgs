#ifndef GEOZASOBY_H
#define GEOZASOBY_H

#include "GeoModel.h"
#include "globalne.h"
///
/// \brief KlasaZas
///
typedef std::pair<double,double> KlasaZas;
///
/// \brief KlasyZas
///
typedef std::vector<KlasaZas> KlasyZas;
///
/// \brief The GeoZasoby class
///
class GeoZasoby
{
public:
    ///
    /// \brief GeoZasoby
    /// \param _modelSet
    /// \param _geoCube
    ///
    GeoZasoby(Mset *_modelSet, GeoCube * _geoCube);
    ///
    /// \brief ~GeoZasoby
    ///
    virtual ~GeoZasoby();
    ///
    /// \brief przelicz_zasoby
    /// \return
    ///
    wektor3d przelicz_zasoby();
    ///
    /// \brief przelicz_zasoby
    /// \param _minp
    /// \param _maxp
    /// \return
    ///
    wektor3d przelicz_zasoby(double _minp, double _maxp);
    ///
    /// \brief analiza_zasoby
    /// \return
    ///
    std::vector<geo3d> analiza_zasoby();
    ///
    /// \brief analiza_zasoby
    /// \param _ileKlas
    /// \return
    ///
    std::vector<geo3d> analiza_zasoby(int _ileKlas);
    ///
    /// \brief get_zasoby
    /// \return
    ///
    wektor3d get_zasoby(){return zasoby;}
    ///
    /// \brief set_klasy
    /// \param kl
    ///
    void set_klasy(KlasyZas kl){klasyZas = kl;}

private:
    ///
    /// \brief ustaw_klasy
    ///
    void ustaw_klasy();
    ///
    /// \brief policzBlok
    /// \param parametry
    /// \param rozmiar
    /// \return
    ///
    wektor3d policzBlok(wektor3d parametry, double rozmiar);
    ///
    /// \brief modelSet
    ///
    Mset *modelSet;
    ///
    /// \brief geoCube
    ///
    GeoCube *geoCube;
    ///
    /// \brief zasoby
    ///
    wektor3d zasoby;
    ///
    /// \brief wynikAnalizy
    ///
    std::vector<geo3d> wynikAnalizy;
    ///
    /// \brief klasyZas
    ///
    KlasyZas klasyZas;
    ///
    /// \brief ileKlas
    ///
    int ileKlas;
};

#endif // GEOZASOBY_H
