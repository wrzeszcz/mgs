#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QGLBuffer>
#include <QMouseEvent>
#include "GeoModel.h"
#include "Gradient.h"
///
/// \brief The GLWidget class
///
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    ///
    /// \brief GLWidget
    /// \param parent
    ///
    explicit GLWidget(QWidget *parent = 0);
    ///
    /// \brief GLWidget
    /// \param _model
    /// \param _widok
    /// \param parent
    ///
    explicit GLWidget(GeoModel *_model,Vset _widok, QWidget *parent = 0 );
    ///
    /// \brief ~GLWidget
    ///
    virtual ~GLWidget(){}
    ///
    /// \brief set_scale
    /// \param f
    ///
    void set_scale(float f){scale = f;}
    ///
    /// \brief set_dx
    /// \param f
    ///
    void set_dx(float f){dx = f;}
    ///
    /// \brief set_dy
    /// \param f
    ///
    void set_dy(float f){dy = f;}
    ///
    /// \brief get_scale
    /// \return
    ///
    float get_scale(){return scale;}
    ///
    /// \brief update_model
    ///
    void update_model();

protected:
    ///
    /// \brief initializeGL
    ///
    virtual void initializeGL();
    ///
    /// \brief resizeGL
    /// \param width
    /// \param height
    ///
    virtual void resizeGL(int width, int height);
    ///
    /// \brief paintGL
    ///
    virtual void paintGL();
    ///
    /// \brief mousePressEvent
    /// \param event
    ///
    virtual void mousePressEvent (QMouseEvent *event);
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
    /// \brief slot_set_widok
    ///
    virtual void slot_set_widok(Vset);
    ///
    /// \brief slot_point
    /// \param p
    ///
    virtual void slot_point(wektor3d p);
    ///
    /// \brief wczytajObiekty
    ///
    virtual void wczytajObiekty();

protected:
    ///
    /// \brief paint_model_siatka
    ///
    virtual void paint_model_siatka();
    ///
    /// \brief paint_model_wezly
    ///
    virtual void paint_model_wezly();
    ///
    /// \brief paint_model_zasoby
    ///
    virtual void paint_model_zasoby();
    ///
    /// \brief paint_model
    ///
    virtual void paint_model();
    ///
    /// \brief paint_dane
    ///
    virtual void paint_dane();
    ///
    /// \brief paint_zakres
    ///
    virtual void paint_zakres();
    ///
    /// \brief model
    ///
    GeoModel *model;
    ///
    /// \brief widok
    ///
    Vset     widok;
    ///
    /// \brief cube
    ///
    GeoCube  *cube;
    ///
    /// \brief dane
    ///
    GeoDat   *dane;
    ///
    /// \brief sett
    ///
    Mset     *sett;
    ///
    /// \brief kolor
    ///
    Gradient kolor;
    ///
    /// \brief curPoint
    ///
    wektor3d curPoint;
    ///
    /// \brief scale
    ///
    GLfloat scale;
    ///
    /// \brief dx
    ///
    GLfloat dx;
    ///
    /// \brief dy
    ///
    GLfloat dy;
    ///
    /// \brief dz
    ///
    GLfloat dz;
    ///
    /// \brief rotX
    ///
    GLfloat rotX;
    ///
    /// \brief rotY
    ///
    GLfloat rotY;
    ///
    /// \brief rotZ
    ///
    GLfloat rotZ;
    ///
    /// \brief mouse_pos
    ///
    QPoint  mouse_pos;
    ///
    /// \brief win_size
    ///
    QSize   win_size;
    ///
    /// \brief model_size
    ///
    QSizeF  model_size;
};

#endif // GLWIDGET_H
