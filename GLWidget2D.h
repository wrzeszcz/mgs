#ifndef GLWIDGET2D_H
#define GLWIDGET2D_H
#include "GLWidget.h"
#include "GL/glu.h"
#include "GL/glut.h"
///
/// \brief The GLWidget2D class
///
class GLWidget2D: public GLWidget
{
public:
    ///
    /// \brief GLWidget2D
    /// \param _model
    /// \param _widok
    /// \param parent
    ///
    explicit GLWidget2D(GeoModel *_model,Vset _widok, QWidget *parent = 0 );
    ///
    /// \brief ~GLWidget2D
    ///
    virtual ~GLWidget2D();
    ///
    /// \brief setZ
    /// \param i
    ///
    void setZ(int i){Z=i; updateGL();}

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
    /// \brief slot_point
    /// \param p
    ///
    virtual void slot_point(wektor3d p);
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
    /// \brief paint_dane
    ///
    void paint_dane();
    ///
    /// \brief paint_zakres
    ///
    void paint_zakres();
    ///
    /// \brief RenderString
    /// \param x
    /// \param y
    /// \param rgb
    /// \param text
    ///
    void RenderString(float x, float y, QColor rgb, QString text);
    ///
    /// \brief paintPkt
    /// \param pkt
    /// \param size
    ///
    void paintPkt    (wektor3d pkt, float size);
    ///
    /// \brief paintBlok
    /// \param srod
    /// \param bok
    /// \param kolor
    ///
    void paintBlok  (wektor3d srod, double bok, float kolor);
    ///
    /// \brief paintBlok
    /// \param srod
    /// \param bok
    ///
    void paintBlok  (wektor3d srod, double bok);
    ///
    /// \brief Z
    ///
    int Z;
    ///
    /// \brief cube2w
    ///
    Cube2win cube2w;
};

#endif // GLWIDGET2D_H
