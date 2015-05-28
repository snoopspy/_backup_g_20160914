CONFIG -= qt
include(../../../g.pri)
LIBS += -lgtest -lgtest_main -pthread
DESTDIR = ../../bin
SOURCES += *.cpp
