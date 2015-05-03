TEMPLATE = lib
QT += widgets
CONFIG += G_BUILD
include(../g.pri)
TARGET = $${G_NAME}
CONFIG += staticlib
DESTDIR = $${PWD}
include(libgfiles.pri)
