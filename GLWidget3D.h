#ifndef GLWIDGET3D_H
#define GLWIDGET3D_H
#include "GLWidget.h"

class GLWidget3D: public GLWidget
{
    Q_OBJECT
public:
    explicit GLWidget3D(GeoModel *_model,Vset _widok, QWidget *parent = 0 );
     ~GLWidget3D();
    void point(wektor3d p);
    void set_zoom(float _zoom){zoom=_zoom;}

protected:
    virtual void paintGL();
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

public slots:
    virtual void wczytajObiekty();

private:
    void paint_model();
    void paint_model_zasoby(int z);
    void paint_dane();
    void paint_zakres();

    void paintPkt   (wektor3d pkt);
    void paintPkt   (std::vector<wektor3d> &pkt3);
    void paintBlok  (wektor3d srod, double bok, float kolor);
    void paintAxis();
    bool test_otoczenia(int a, int b, int c);

    GLfloat zoom;
    Cube2win cube2w;

    std::vector <wektor3d> v_pkt3dane;
    std::vector <wektor3d>::iterator v_it;
};



#endif // GLWIDGET3D_H
