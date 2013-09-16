#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLBuffer>
#include <QMouseEvent>
#include "GeoModel.h"
#include "Gradient.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    explicit GLWidget(GeoModel *_model,Vset _widok, QWidget *parent = 0 );
    virtual ~GLWidget(){}

    void set_scale(float f){scale = f;}
    void set_dx(float f){dx = f;}
    void set_dy(float f){dy = f;}

    float get_scale(){return scale;}

    void update_model();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
signals:
    
public slots:
    virtual void slot_set_widok(Vset);
    virtual void slot_point(wektor3d p);
    virtual void wczytajObiekty();

protected:
    virtual void paint_model_siatka();
    virtual void paint_model_wezly();
    virtual void paint_model_zasoby();
    virtual void paint_model();
    virtual void paint_dane();
    virtual void paint_zakres();


    GeoModel *model;
    Vset     widok;
    GeoCube  *cube;
    GeoDat   *dane;
    Mset     *sett;
    Gradient kolor;

    wektor3d curPoint;

    GLfloat scale;
    GLfloat dx;
    GLfloat dy;
    GLfloat dz;
    GLfloat rotX;
    GLfloat rotY;
    GLfloat rotZ;

    QPoint  mouse_pos;
    QSize   win_size;
    QSizeF  model_size;
};

#endif // GLWIDGET_H
