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
#include <iostream>
//------------------------------------------------------------------------------
Gradient::Gradient():
    k(QColor(0,0,0))
{

}
//------------------------------------------------------------------------------
QColor Gradient::get_kolor(double poz)
{
    if ( poz > 1.0 ) poz = 1.0;// poz - int(poz);
    if (poz < 0.0) poz = 0.0;

    int pixelDistance = (int)( poz * 1792.0 );
    unsigned int red, green, blue;

    if (pixelDistance < 256)
    {   // BLACK to BLUE
        red = 0;
        green = 0;
        blue = pixelDistance;
    }
    else if (pixelDistance < 512)
    {   // BLUE to CYAN
        red = 0;
        green = pixelDistance - 256;
        blue = 255;
    }
    else if (pixelDistance < 768)
    {   // CYAN to GREEN
        red = 0;
        green = 255;
        blue = 255 - (pixelDistance - 512);
    }
    else if (pixelDistance < 1024)
    {   //GREEN to YELLOW
        red = (pixelDistance - 768);
        green = 255;
        blue = 0;
    }
    else if (pixelDistance < 1280)
    {   // YELLOW to RED
        red = 255;
        green= 255-(pixelDistance - 1024);
        blue = 0;
    }
    else if (pixelDistance < 1536)
    {   //  RED to MAGENTA
        red = 255;
        green= 0;
        blue = pixelDistance - 1280;
    }
    else
    {   // MAGENTA to WHITE
        red = 255;
        green = pixelDistance - 1536;
        blue = 255;
    }

    if(red > 255 || green > 255 || blue > 255)
    {
        std::cout<<red<<" "<<green<<" "<<blue<<" "<< pixelDistance << std::endl;
    }
    return QColor(red, green, blue);
}
//------------------------------------------------------------------------------
