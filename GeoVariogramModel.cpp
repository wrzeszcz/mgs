/*******************************************************************************
**  Copyright (C) 2013  Marek Wrzeszcz
**  mail: marek.wrzeszcz@hotmail.com
**
**  This file is part of the MGEOSTAT.
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "GeoVariogramModel.h"
//------------------------------------------------------------------------------
GeoVariogramModel::GeoVariogramModel():
    cur_vario_model(EXPONENTIAL),
    c0(0.0),
    c1(0.1),
    a(50.0)
{
}
//------------------------------------------------------------------------------
GeoVariogramModel::GeoVariogramModel(variogram vario, double nugget, double sill, double range):
    cur_vario_model(vario),
    c0(nugget),
    c1(sill),
    a(range)
{

}
//------------------------------------------------------------------------------
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
        if(h==0.0) return ret=0.0;
        ret = c0 + c1 * (1 - exp( (-3*h*h) / (a*a) ) );
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
//------------------------------------------------------------------------------
