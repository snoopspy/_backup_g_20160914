CONFIG -= qt
include(../../../../g.pri)
QMAKE_CXXFLAGS *= -g
QMAKE_LFLAGS *= -g
#INCLUDEPATH += ../../../../src
#LIBS += -ldl
#SOURCES += *.cpp ../../../../src/sys/malloc/*.cpp
#HEADERS += ../../../../src/sys/malloc/*.h
SOURCES += *.cpp
