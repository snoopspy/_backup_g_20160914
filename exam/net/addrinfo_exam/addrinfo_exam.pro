QT -= gui
CONFIG += console
include(../../../g.pri)
LIBS += -lgflags -pthread
SOURCES *= *.cpp
DESTDIR = $${PWD}/../../../bin
