TEMPLATE = lib
CONFIG += G_BUILD
include(../g.pri)
TARGET = $${G_NAME}
CONFIG += staticlib
DESTDIR = $${PWD}

SOURCES += \
	../src/sys/memleak/*.cpp
	
HEADERS += \
	../src/sys/memleak/*.h
