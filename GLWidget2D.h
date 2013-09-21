#ifndef GLWIDGET2D_H
#define GLWIDGET2D_H
#include "GLWidget.h"
#include "GL/glu.h"
#include "GL/glut.h"

class GLWidget2D: public GLWidget
{
public:
    explicit GLWidget2D(GeoModel *_model,Vset _widok, QWidget *parent = 0 );
    ~GLWidget2D();
    void setZ(int i){Z=i; updateGL();}

protected:
    virtual void paintGL();
    //void paintEvent(QPaintEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

public slots:
    virtual void slot_point(wektor3d p);
    virtual void wczytajObiekty();

private:
    void paint_model();
    void paint_dane();
    void paint_zakres();

    void RenderString(float x, float y, QColor rgb, QString text);
    void paintPkt    (wektor3d pkt, float size);
    void paintBlok  (wektor3d srod, double bok, float kolor);
    void paintBlok  (wektor3d srod, double bok);
    int Z;
    Cube2win cube2w;
};

#endif // GLWIDGET2D_H
