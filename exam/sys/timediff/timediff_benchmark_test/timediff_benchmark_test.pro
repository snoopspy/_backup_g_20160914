QT -= gui
CONFIG += console
QMAKE_CXXFLAGS += -std=c++11
win32:LIBS += -lwinmm
SOURCES += *.cpp
DESTDIR = $${PWD}/../../../../bin
