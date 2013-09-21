#ifndef GEOVARIOGRAM_H
#define GEOVARIOGRAM_H

#include "GeoDat.h"
#include "globalne.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

///
/// \brief The GeoVariogram class
///
class GeoVariogram
{
public:
    ///
    /// \brief GeoVariogram
    /// \param dane
    /// \param rozmiar_klasy
    ///
    GeoVariogram(GeoDat *dane, double rozmiar_klasy);
    ///
    /// \brief GeoVariogram
    /// \param dane
    ///
    GeoVariogram(GeoDat *dane);
    ///
    /// \brief recalc
    /// \param rozmiar_klasy
    ///
    void recalc(double rozmiar_klasy);
    ///
    /// \brief recalc
    ///
    void recalc();
    ///
    /// \brief set_dane
    /// \param dane
    /// \param rozmiar_klasy
    ///
    void set_dane(GeoDat *dane, double rozmiar_klasy);
    ///
    /// \brief set_dane
    /// \param dane
    ///
    void set_dane(GeoDat *dane);
    ///
    /// \brief get_raport
    /// \return
    ///
    string get_raport();
    ///
    /// \brief wypisz_dist_delta
    /// \param filename
    ///
    void wypisz_dist_delta(string filename);
    ///
    /// \brief get_klasy
    /// \return
    ///
    std::vector<wektor3d> &get_klasy(){return dist_delta_klas;}

private:
    ///
    /// \brief auto_rozmiar
    /// \param delty
    /// \param ile
    /// \return
    ///
    double auto_rozmiar(const std::vector<wektor3d> &delty, int ile);
    ///
    /// \brief dist_delta
    ///
    std::vector<wektor3d> dist_delta;
    ///
    /// \brief dist_delta_klas
    ///
    std::vector<wektor3d> dist_delta_klas;
    ///
    /// \brief gIt
    ///
    std::vector<wektor3d>::iterator gIt;
    ///
    /// \brief dane
    ///
    GeoDat *dane;
    ///
    /// \brief rozmiar
    ///
    double rozmiar;
    ///
    /// \brief dist
    ///
    Odl dist;
};

#endif // GEOVARIOGRAM_H
