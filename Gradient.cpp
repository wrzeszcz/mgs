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

#include "Gradient.h"
//------------------------------------------------------------------------------
Gradient::Gradient():
    k(QColor(0,0,0))
{

}
//------------------------------------------------------------------------------
QColor Gradient::get_kolor(double position)
{
    if (position > 1) position = position - int(position);
    float R(0.0), G(0.0), B(0.0);
    int nmax = 6;

    double m = nmax * position;
    int    n = int(m);
    double f = m-n;
    float  t = float(f*255.0);

    switch(n)
    {
        case 0:
        {
            R = 255;
            G = t;
            B = 0;
            break;
        };
       case 1:
        {
            R = 255 - t;
            G = 255;
            B = 0;
            break;
        };
        case 2:
        {
            R = 0;
            G = 255;
            B = t;
            break;
        };
       case 3:
        {
            R = 0;
            G = 255 - t;
            B = 255;
            break;
        };
        case 4:
        {
            R = t;
            G = 0;
            B = 255;
            break;
        };
       case 5:
        {
            R = 255;
            G = 0;
            B = 255 - t;
            break;
        };
        default:
            break;

    }; // case

    return QColor(R,G,B);
}
//------------------------------------------------------------------------------
