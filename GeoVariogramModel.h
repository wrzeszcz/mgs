#ifndef GEOVARIOGRAMMODEL_H
#define GEOVARIOGRAMMODEL_H
#include "globalne.h"

class GeoVariogramModel
{
public:
    GeoVariogramModel();
    GeoVariogramModel(variogram vario, double nugget, double sill, double range);
    double licz_vario(double h);

    void set_param(variogram vario, double nugget, double sill, double range)
     {
         cur_vario_model = vario;
         c0 = nugget;
         c1 = sill;
         a = range;
     }

     void set_variogram(variogram v){cur_vario_model = v;}
     void set_nugget(double n){c0 = n;}
     void set_sill  (double s){c1 = s;}
     void set_range (double r){a = r;}

private:
     variogram cur_vario_model;
     double c0;
     double c1;
     double a;

};

#endif // GEOVARIOGRAMMODEL_H
