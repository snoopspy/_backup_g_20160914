CONFIG -= qt
CONFIG += gstacktrace
include(../../../../g.pri)
LIBS += -lglog -lgtest -lgtest_main
SOURCES += *.cpp
