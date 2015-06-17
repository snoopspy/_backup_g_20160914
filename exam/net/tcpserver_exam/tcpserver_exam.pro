QT -= gui
CONFIG += console
include(../../../g.pri)
LIBS += -lgflags
SOURCES += *.cpp
DESTDIR = $${PWD}/../../../bin
