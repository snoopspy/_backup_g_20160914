CONFIG -= qt
#include(../../../../g.pri)
INCLUDEPATH += ../../../../src
LIBS += -ldl
SOURCES += *.cpp ../../../../src/sys/malloc/*.cpp
HEADERS += ../../../../src/sys/malloc/*.h
