TEMPLATE = app
QT -= gui
CONFIG += G_BUILD
include(../g.pri)
TARGET = $${G_NAME}_test
include(libg_files.pri)
DEFINES *= GTEST
LIBS *= -lgtest -lgtest_main -pthread