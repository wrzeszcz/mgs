#ifndef IMAT3_H
#define IMAT3_H

class IMat3
{
public:

    virtual ~IMat3();

    virtual void inicjuj(int dx, int dy, int dz) = 0;

    virtual void resize(int dx, int dy, int dz) = 0;

    virtual void clear() = 0;



};

#endif // IMAT3_H
