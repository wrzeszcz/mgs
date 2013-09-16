#include "Gradient.h"

Gradient::Gradient():
    k(QColor(0,0,0))
{

}

QColor Gradient::get_kolor(double position)
{
    if (position>1)position = position-int(position);
    float R, G, B;
    int nmax = 6;

    double m = nmax * position;
    int    n = int(m);
    double f = m-n;
    float  t = float(f*255.0);

    switch(n)
    {
       case 0: {
          R = 255;
          G = t;
          B = 0;
           break;
        };
       case 1: {
          R = 255 - t;
          G = 255;
          B = 0;
           break;
        };

        case 2: {
          R = 0;
          G = 255;
          B = t;
           break;
        };
       case 3: {
          R = 0;
          G = 255 - t;
          B = 255;
           break;
        };

        case 4: {
          R = t;
          G = 0;
          B = 255;
           break;
        };
       case 5: {
          R = 255;
          G = 0;
          B = 255 - t;
           break;
        };

    }; // case

    return QColor(R,G,B);
}
