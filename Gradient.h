#ifndef GRADIENT_H
#define GRADIENT_H
#include <QColor>

class Gradient
{
public:
    Gradient();
    QColor get_kolor(double poz);
private:
    QColor k;
};

#endif // GRADIENT_H
