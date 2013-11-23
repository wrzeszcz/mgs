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

#ifndef GLWIDGET3D_H
#define GLWIDGET3D_H
#include "GLWidget.h"
///
/// \brief The GLWidget3D class
///
class GLWidget3D: public GLWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GLWidget3D
    /// \param _model
    /// \param _widok
    /// \param parent
    ///
    explicit GLWidget3D(GeoModel *_model,Vset _widok, QWidget *parent = 0 );
    ///
    /// \brief ~GLWidget3D
    ///
    virtual ~GLWidget3D();
    ///
    /// \brief point
    /// \param p
    ///
    void point(wektor3d p);
    ///
    /// \brief set_zoom
    /// \param _zoom
    ///
    void set_zoom(float _zoom){zoom=_zoom;}
    ///
    /// \brief get_zoom
    /// \return
    ///
    float get_zoom(){return zoom;}
    ///
    /// \brief setZ
    /// \param _z
    ///
    void setZ(int _z){z=_z;}

protected:
    ///
    /// \brief paintGL
    ///
    virtual void paintGL();
    ///
    /// \brief mouseMoveEvent
    /// \param event
    ///
    virtual void mouseMoveEvent (QMouseEvent *event);
    ///
    /// \brief wheelEvent
    /// \param event
    ///
    virtual void wheelEvent(QWheelEvent *event);

public slots:
    ///
    /// \brief wczytajObiekty
    ///
    virtual void wczytajObiekty();

private:
    ///
    /// \brief paint_model
    ///
    void paint_model();
    ///
    /// \brief paint_model_zasoby
    /// \param z
    ///
    void paint_model_zasoby(int z);
    ///
    /// \brief paint_dane
    ///
    void paint_dane();
    ///
    /// \brief paint_zakres
    ///
    void paint_zakres();
    ///
    /// \brief paintPkt
    /// \param pkt
    ///
    void paintPkt   (wektor3d pkt);
    ///
    /// \brief paintPkt
    /// \param pkt3
    ///
    void paintPkt   (std::vector<wektor3d> &pkt3);
    ///
    /// \brief paintBlok
    /// \param srod
    /// \param bok
    /// \param kolor
    ///
    void paintBlok  (wektor3d srod, double bok, float kolor);
    ///
    /// \brief paintAxis
    ///
    void paintAxis();
    ///
    /// \brief test_otoczenia
    /// \param a
    /// \param b
    /// \param c
    /// \return
    ///
    bool test_otoczenia(int a, int b, int c);
    ///
    /// \brief zoom
    ///
    GLfloat zoom;
    ///
    /// \brief cube2w
    ///
    Cube2win cube2w;
    ///
    /// \brief v_pkt3dane
    ///
    std::vector <wektor3d> v_pkt3dane;
    ///
    /// \brief v_it
    ///
    std::vector <wektor3d>::iterator v_it;
    ///
    /// \brief z
    ///
    int z;
};



#endif // GLWIDGET3D_H
