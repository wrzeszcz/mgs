#ifndef GEOVARIOGRAMMODEL_H
#define GEOVARIOGRAMMODEL_H
#include "globalne.h"
///
/// \brief The GeoVariogramModel class
///
class GeoVariogramModel
{
public:
    ///
    /// \brief GeoVariogramModel
    ///
    GeoVariogramModel();
    ///
    /// \brief GeoVariogramModel
    /// \param vario
    /// \param nugget
    /// \param sill
    /// \param range
    ///
    GeoVariogramModel(variogram vario, double nugget, double sill, double range);
    ///
    /// \brief licz_vario
    /// \param h
    /// \return
    ///
    double licz_vario(double h);
    ///
    /// \brief set_param
    /// \param vario
    /// \param nugget
    /// \param sill
    /// \param range
    ///
    void set_param(variogram vario, double nugget, double sill, double range)
     {
         cur_vario_model = vario;
         c0 = nugget;
         c1 = sill;
         a = range;
     }
    ///
    /// \brief set_variogram
    /// \param v
    ///
    void set_variogram(variogram v){cur_vario_model = v;}
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

private:
    ///
    /// \brief cur_vario_model
    ///
    variogram cur_vario_model;
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
};

#endif // GEOVARIOGRAMMODEL_H
