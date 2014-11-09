################################################################################
#    Copyright (C) 2013  Marek Wrzeszcz
#    mail: marek.wrzeszcz@hotmail.com
#
#    This file is part of the MGEOSTAT.
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
################################################################################

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MGS
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
    GeoZasoby.cpp \
    GProAnaliza.cpp \
    GraphColumnWidget.cpp

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
    GeoZasoby.h \
    GProAnaliza.h \
    GraphColumnWidget.h

RC_FILE = geostat.txt

RESOURCES += \
    geostat.qrc

LIBS += -L/usr/local/lib -lGLU




