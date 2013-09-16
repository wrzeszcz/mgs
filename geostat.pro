#-------------------------------------------------
#
# Marek Wrzeszcz
#
#-------------------------------------------------

QT       += core gui\
	    opengl\

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = geostat
TEMPLATE = app

SOURCES += main.cpp\
    GProSet.cpp \
    GProTree.cpp \
    GeoCube.cpp \
    GeoModel.cpp \
    GMainWin.cpp \
    GeoDat.cpp \
    GeoVariogram.cpp \
    GeoKriging.cpp \
    GProDialog.cpp \
    GeoWidget.cpp \
    GeoVariogramModel.cpp \
    GeoWidgetDane.cpp \
    GeoWidgetRaport.cpp \
    GeoWidgetVariogram.cpp \
    GraphWidget.cpp \
    GeoWidget2D.cpp \
    GLWidget.cpp \
    GeoWidget3D.cpp \
    GLWidget2D.cpp \
    GLWidget3D.cpp \
    Gradient.cpp \
    GeoZasoby.cpp

HEADERS  += \
    GProSet.h \
    GProTree.h \
    GeoCube.h \
    GeoModel.h \
    GMainWin.h \
    globalne.h \
    GeoDat.h \
    GeoVariogram.h \
    GeoKriging.h \
    GProDialog.h \
    GeoWidget.h \
    GeoVariogramModel.h \
    GeoWidgetDane.h \
    GeoWidgetRaport.h \
    GeoWidgetVariogram.h \
    GraphWidget.h \
    GeoWidget2D.h \
    GLWidget.h \
    GeoWidget3D.h \
    GLWidget2D.h \
    GLWidget3D.h \
    Gradient.h \
    GeoZasoby.h

RC_FILE = geostat.txt

RESOURCES += \
    geostat.qrc

LIBS += -L/usr/local/lib -lGLU
LIBS += -lglut




