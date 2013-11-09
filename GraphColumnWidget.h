#ifndef GRAPHCOLUMNWIDGET_H
#define GRAPHCOLUMNWIDGET_H

#include <QWidget>
#include "globalne.h"
#include <QMouseEvent>
#include <QSize>

class GraphColumnWidget : public QWidget
{
public:
    explicit GraphColumnWidget(QWidget *parent = 0);

    void set_data(std::vector<geo3d> &data);

protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    std::vector<geo3d> dane;
    double max_masa;
    QSize border;
    QSize area;
};

#endif // GRAPHCOLUMNWIDGET_H
