TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../../GeoZasoby.cpp \
    ../../GeoVariogramModel.cpp \
    ../../GeoVariogram.cpp \
    ../../GeoModel.cpp \
    ../../GeoKriging.cpp \
    ../../GeoDat.cpp \
    ../../GeoCube.cpp


HEADERS += \
    ../../globalne.h \
    ../../GeoZasoby.h \
    ../../GeoVariogramModel.h \
    ../../GeoVariogram.h \
    ../../GeoModel.h \
    ../../GeoKriging.h \
    ../../GeoDat.h \
    ../../GeoCube.h


