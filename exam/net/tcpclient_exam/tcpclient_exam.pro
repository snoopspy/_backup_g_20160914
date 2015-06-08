CONFIG -= qt
include(../../../g.pri)
LIBS += -lgflags
SOURCES += *.cpp
DESTDIR = $${PWD}/../../../bin
