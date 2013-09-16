#include "GeoVariogramModel.h"

GeoVariogramModel::GeoVariogramModel():
    cur_vario_model(EXPONENTIAL),
    c0(0.0),
    c1(0.1),
    a(50.0)
{
}
GeoVariogramModel::GeoVariogramModel(variogram vario, double nugget, double sill, double range):
    cur_vario_model(vario),
    c0(nugget),
    c1(sill),
    a(range)
{

}
double GeoVariogramModel::licz_vario(double h)
{
    double ret;
    switch(cur_vario_model)
    {
    case EXPONENTIAL:
        if(h==0.0) return ret=0.0;
        else ret = c0 + c1 * (1 - exp(-3*h/a));
        break;
    case GAUSSIAN:
        ret = c0 + c1 * (1 - exp(-3*h*h/a/a));
        break;
    case SPHERICAL:
        if ( h < a )
            ret = c0 + c1 * (1.5*h/a - 0.5*(h/a)*(h/a)*(h/a));
        else
            ret = c0 + c1;
        break;
    default:
        ret = 0.0;
        break;
    }
    return ret;
}
