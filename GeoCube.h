#ifndef GEOCUBE_H
#define GEOCUBE_H

#include <cstdlib>
#include <ostream>
#include <exception>
#include <vector>
#include "globalne.h"

using namespace std;
///
/// \brief Klasa GeoCube
///
class GeoCube
{
public:
    ///
    /// \brief GeoCube
    /// \param start
    /// \param blok
    /// \param dim
    ///
    GeoCube(wektor3d start, double blok, wektor3i dim);
    ~GeoCube();
    ///
    /// \brief wyczysc
    ///
    void wyczysc();
    ///
    /// \brief getRekLok
    /// \param poz
    /// \return
    ///
    wektor3d getRekLok(wektor3i  poz);
    ///
    /// \brief getRekGlo
    /// \param poz
    /// \return
    ///
    wektor3d getRekGlo(wektor3d poz);
    ///
    /// \brief getRek
    /// \param poz
    /// \return
    ///
    wektor3d getRek(wektor3i poz);
    ///
    /// \brief getRek
    /// \param a
    /// \param b
    /// \param c
    /// \return
    ///
    wektor3d getRek(int a,int b, int c);
    ///
    /// \brief setRekLok
    /// \param poz
    /// \param dane
    ///
    void setRekLok(wektor3i poz, wektor3d dane);
    ///
    /// \brief setRekGlo
    /// \param poz
    /// \param dane
    ///
    void setRekGlo(wektor3d poz, wektor3d dane);
    ///
    /// \brief wypiszLok
    /// \param os
    /// \param tylkoXYZ
    /// \param limit
    ///
    void wypiszLok(ostream& os, bool tylkoXYZ, double limit);
    ///
    /// \brief wypiszGlo
    /// \param os
    /// \param tylkoXYZ
    /// \param limit
    ///
    void wypiszGlo(ostream& os, bool tylkoXYZ, double limit);
    ///
    /// \brief wypiszGlo
    /// \param vec
    /// \param limit
    /// \param ofset
    ///
    void wypiszGlo(vector<wektor3d> &vec, double limit, wektor3d ofset);
    ///
    /// \brief getStart
    /// \return
    ///
    wektor3d getStart(){return start3d;}
    ///
    /// \brief getSize
    /// \return
    ///
    wektor3i getSize() {return dim3i;}
    ///
    /// \brief size_x
    /// \return
    ///
    int size_x(){return dim3i.x;}
    ///
    /// \brief size_y
    /// \return
    ///
    int size_y(){return dim3i.y;}
    ///
    /// \brief size_z
    /// \return
    ///
    int size_z(){return dim3i.z;}
    ///
    /// \brief size
    /// \return
    ///
    int size(){return dim3i.x * dim3i.y * dim3i.z;}
    ///
    /// \brief getSpac
    /// \return
    ///
    double getSpac() {return spacing;}
    ///
    /// \brief get_max
    /// \return
    ///
    wektor3d get_max(){return w_max;}
    ///
    /// \brief get_min
    /// \return
    ///
    wektor3d get_min(){return w_min;}
    ///
    /// \brief min_max
    /// \param min
    /// \param max
    ///
    void min_max(wektor3d &min, wektor3d &max);
    ///
    /// \brief min_max
    ///
    void min_max();
    ///
    /// \brief reset_min_max
    ///
    void reset_min_max();

private:
    ///
    /// \brief cube
    ///
    wektor3d ***cube;
    ///
    /// \brief start3d
    ///
    wektor3d start3d;
    ///
    /// \brief dim3i
    ///
    wektor3i   dim3i;
    ///
    /// \brief spacing
    ///
    double   spacing;
    ///
    /// \brief inicjuj
    ///
    void   inicjuj(); 
    ///
    /// \brief w_max
    ///
    wektor3d w_max;
    ///
    /// \brief w_min
    ///
    wektor3d w_min;
};
//------------------------------------------------------------------------------
#endif // GEOCUBE_H