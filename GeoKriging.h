#ifndef GEOKRIGING_H
#define GEOKRIGING_H

#include "TNT/tnt.h"
#include "TNT/jama_lu.h"
#include "globalne.h"
#include "GeoVariogramModel.h"
#include <vector>
#include <ostream>
#include <math.h>
#include <algorithm>

///
/// \brief The GeoKriging class
///
class GeoKriging
{
public:
    ///
    /// \brief GeoKriging
    ///
    GeoKriging();
    ///
    /// \brief GeoKriging
    /// \param vario
    /// \param nugget
    /// \param sill
    /// \param range
    /// \param minO
    /// \param maxO
    ///
    GeoKriging(variogram vario, double nugget, double sill, double range, int minO, int maxO);
    ///
    /// \brief GeoKriging
    /// \param m
    /// \param minO
    /// \param maxO
    ///
    GeoKriging(GeoVariogramModel &m , int minO, int maxO);
    ///
    /// \brief GeoKriging
    /// \param s
    ///
    GeoKriging(Set_interpolacja &s);
    ///
    /// \brief o_kriging
    /// \param pkt
    /// \param otoczenie
    /// \return
    ///
    wektor3d o_kriging (wektor3d pkt,std::vector<geo3d> &otoczenie);
    ///
    /// \brief set_parametry
    /// \param vario
    /// \param nugget
    /// \param sill
    /// \param range
    /// \param minO
    /// \param maxO
    ///
    void set_parametry(variogram vario, double nugget, double sill, double range, int minO, int maxO);
    ///
    /// \brief set_variogram
    /// \param v
    ///
    void set_variogram(variogram v){cur_vario = v;}
    ///
    /// \brief set_nugget
    /// \param n
    ///
    void set_nugget(double n){c0 = n;}
    ///
    /// \brief set_sill
    /// \param s
    ///
    void set_sill  (double s){c1 = s;}
    ///
    /// \brief set_range
    /// \param r
    ///
    void set_range (double r){a = r;}
    ///
    /// \brief set_minOt
    /// \param minO
    ///
    void set_minOt(int minO){minOt = minO;}
    ///
    /// \brief set_maxOt
    /// \param maxO
    ///
    void set_maxOt(int maxO){maxOt = maxO;}
    ///
    /// \brief set_geoWariogramModel
    /// \param m
    ///
    void set_geoWariogramModel(GeoVariogramModel &m){variogram_model=m;}
private:
    ///
    /// \brief spr_otoczenie
    /// \param pkt
    /// \param otoczenie
    /// \param max
    ///
    void spr_otoczenie(const wektor3d &pkt,std::vector<geo3d> &otocz, int max);
    ///
    /// \brief cur_vario
    ///
    variogram cur_vario;
    ///
    /// \brief variogram_model
    ///
    GeoVariogramModel variogram_model;
    ///
    /// \brief c0
    ///
    double c0;
    ///
    /// \brief c1
    ///
    double c1;
    ///
    /// \brief a
    ///
    double a;
    ///
    /// \brief minOt
    ///
    int minOt;
    ///
    /// \brief maxOt
    ///
    int maxOt;
    ///
    /// \brief dist
    ///
    Odl dist;
};

#endif // GEOKRIGING_H
