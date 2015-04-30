TEMPLATE = lib
CONFIG += G_BUILD
include(../g.pri)
TARGET = $${G_NAME}
CONFIG += staticlib
DESTDIR = $${PWD}

SOURCES += \
	../src/sys/memleak/*.cpp \
	../src/sys/procinfo/*.cpp
	
HEADERS += \
	../src/sys/memleak/*.h \
	../src/sys/procinfo/*.h
