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

#include "GeoCube.h"
//------------------------------------------------------------------------------
GeoCube::GeoCube(wektor3d start, double blok, wektor3i dim):
    cube(0),
    start3d(start),
    dim3i(dim),
    spacing(blok)
{
    inicjuj();
    reset_min_max();
}
//------------------------------------------------------------------------------
 GeoCube::~GeoCube()
 {
     wyczysc();
 }
//------------------------------------------------------------------------------
void GeoCube::wyczysc()
{
    if(cube)
    {
        for (int a=0; a < dim3i.x; ++a)
        {
            for (int b=0; b < dim3i.y; ++b)
            {
                delete[] cube[a][b];
                cube[a][b]=NULL;
            }
            delete[] cube[a];
            cube[a]=NULL;
        }
        delete[] cube;
        cube = NULL;
    }
    dim3i = wektor3i(0,0,0);
    spacing = 0.0;
    start3d = wektor3d(0.0,0.0,0.0);
}
//------------------------------------------------------------------------------
void GeoCube::inicjuj()
{
    if(cube) wyczysc();
    int a(0),b(0);
    try
    {
    cube = new wektor3d**[dim3i.x];
    for (a=0; a < dim3i.x; ++a)
    {
        cube [a] = new wektor3d*[dim3i.y];
        for (b=0; b < dim3i.y; ++b) cube[a][b]= new wektor3d[dim3i.z];
    }
    }
    catch (std::exception &ex)
    {
       dim3i.x=a;
       dim3i.y=b;
       wyczysc();
    }
}
//------------------------------------------------------------------------------
void GeoCube::wypiszLok(ostream &os, bool tylkoXYZ, double limit)
{
    if (tylkoXYZ)
    {
    for(int a=0; a<dim3i.x;++a)
        for(int b=0; b<dim3i.y;++b)
            for(int c=0; c<dim3i.z;++c)
                if(cube [a][b][c].x>limit)
                os << a << " " << b << " " << c << " ";
    }
    else
    {
        for(int a=0; a<dim3i.x;++a)
            for(int b=0; b<dim3i.y;++b)
                for(int c=0; c<dim3i.z;++c)
                    if(cube [a][b][c].x>limit)
                    os<<a<<" "<<b<<" "<<c<<" "<<cube[a][b][c].x<<endl;
    }
}
//------------------------------------------------------------------------------
void GeoCube::wypiszGlo(ostream &os, bool tylkoXYZ, double limit, string sep)
{
    os.setf(ios::fixed);
    os.precision(6);
    if(tylkoXYZ)
    {
    for(int a=0; a<dim3i.x;++a)
        for(int b=0; b<dim3i.y;++b)
            for(int c=0; c<dim3i.z;++c)
                if(cube [a][b][c].x>limit)
                {
                os << (a*spacing+start3d.x) << sep
                     << (b*spacing+start3d.y) << sep
                     << (c*spacing+start3d.z)  << sep;
                }
     }
     else
    {
            for(int a=0; a<dim3i.x;++a)
                for(int b=0; b<dim3i.y;++b)
                    for(int c=0; c<dim3i.z;++c)
                        if(cube [a][b][c].x > limit)
                        {
                        os << (a*spacing+start3d.x) << sep
                           << (b*spacing+start3d.y) << sep
                           << (c*spacing+start3d.z) << sep
                           <<  cube [a][b][c].x << sep
                           <<  cube [a][b][c].y << sep
                           <<  cube [a][b][c].z << endl;
                        }
    }
}
//------------------------------------------------------------------------------
void GeoCube::wypiszGlo(ostream &os, string sep)
{
    os.setf(ios::fixed);
    os.precision(6);
    for(int a=0; a<dim3i.x;++a)
        for(int b=0; b<dim3i.y;++b)
            for(int c=0; c<dim3i.z;++c)
                {
                os << (a*spacing+start3d.x) << sep
                   << (b*spacing+start3d.y) << sep
                   << (c*spacing+start3d.z) << sep
                   <<  cube [a][b][c].x << sep
                   <<  cube [a][b][c].y << sep
                   <<  cube [a][b][c].z << endl;
                }
}
//------------------------------------------------------------------------------
void GeoCube::wypiszGlo(vector<wektor3d> &vec, double limit, wektor3d ofs)
{
    for(int a=0; a<dim3i.x;++a)
        for(int b=0; b<dim3i.y;++b)
            for(int c=0; c<dim3i.z;++c)
                if(cube [a][b][c].x>limit)
                {
                    vec.push_back(wektor3d(a,b,c)*spacing+start3d-ofs);
                }
}
//------------------------------------------------------------------------------
wektor3d GeoCube::getRekLok(wektor3i poz)
{
    if (poz.x<dim3i.x && poz.y<dim3i.y && poz.z<dim3i.z)
    return cube[poz.x][poz.y][poz.z];
    else return wektor3d();
}
//--------------------------------------------------------------------
wektor3d GeoCube::getRekGlo(wektor3d poz)
{
    wektor3i lokal;
    lokal.x = (int)((poz.x-start3d.x)/spacing);
    lokal.y = (int)((poz.y-start3d.y)/spacing);
    lokal.z = (int)((poz.z-start3d.z)/spacing);
    return getRekLok(lokal);
}
//------------------------------------------------------------------------------
wektor3d GeoCube::getRek(wektor3i poz)
{
    return cube[poz.x][poz.y][poz.z];
}
//------------------------------------------------------------------------------
void GeoCube::setRekLok(wektor3i poz, wektor3d dane)
{
    cube[poz.x][poz.y][poz.z]=dane;

        wektor3d tmp = cube[poz.x][poz.y][poz.z];

        if(tmp.x == NULLDAT)return;

        if         (tmp.x > w_max.x) w_max.x = tmp.x;
       if ( tmp.x < w_min.x) w_min.x = tmp.x;

        if        (tmp.y > w_max.y) w_max.y = tmp.y;
        if (tmp.y < w_min.y) w_min.y = tmp.y;

        if         (tmp.z > w_max.z) w_max.z = tmp.z;
         if ( tmp.z < w_min.z) w_min.z = tmp.z;

}
//------------------------------------------------------------------------------
void GeoCube::setRekGlo(wektor3d poz, wektor3d dane)
{
    wektor3i lokal;
    lokal.x = (int)((poz.x-start3d.x)/spacing);
    lokal.y = (int)((poz.y-start3d.y)/spacing);
    lokal.z = (int)((poz.z-start3d.z)/spacing);
    setRekLok(lokal,dane);
}
//------------------------------------------------------------------------------
wektor3d GeoCube::getRek(int a,int b, int c)
{
    return cube[a][b][c];
}
//------------------------------------------------------------------------------
void GeoCube::min_max(wektor3d &min, wektor3d &max)
{
    min_max();
    min = w_min;
    max = w_max;
}
//------------------------------------------------------------------------------
void GeoCube::min_max()
{
    if(!cube)return;

    w_max = w_min = cube[0][0][0];

    wektor3d tmp;

    for(int a=0; a < dim3i.x; ++a)
        for(int b=0; b < dim3i.y; ++b)
            for(int c=0; c < dim3i.z; ++c)
            {
                tmp = cube[a][b][c];

                if      (tmp.x > w_max.x) w_max.x = tmp.x;
                else if ( tmp.x < w_min.x) w_min.x = tmp.x;

                if      (tmp.y > w_max.y) w_max.y = tmp.y;
                else if (tmp.y < w_min.y) w_min.y = tmp.y;

                if      (tmp.z > w_max.z) w_max.z = tmp.z;
                else if ( tmp.z < w_min.z) w_min.z = tmp.z;

            }
}
//------------------------------------------------------------------------------
void GeoCube::reset_min_max()
{
    w_max = wektor3d(NULLDAT,NULLDAT,NULLDAT);
    w_min = wektor3d(-1.0*NULLDAT,-1.0*NULLDAT,-1.0*NULLDAT);
}
//------------------------------------------------------------------------------

