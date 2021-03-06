#------------------------------------------------------------------------------
# c++11
#------------------------------------------------------------------------------
QMAKE_CXXFLAGS *= -std=c++11
QMAKE_LFLAGS += -pthread

#------------------------------------------------------------------------------
# debug and release
#------------------------------------------------------------------------------
CONFIG(debug, debug|release) DEFINES *= _DEBUG
CONFIG(release, debug|release) DEFINES *= _RELEASE

#------------------------------------------------------------------------------
# G_NAME
#------------------------------------------------------------------------------
G_NAME = g
android-g++:                  G_NAME = $${G_NAME}_android
CONFIG(qt): contains(QT, gui) G_NAME = $${G_NAME}_gui
CONFIG(debug, debug|release)  G_NAME = $${G_NAME}_d

#------------------------------------------------------------------------------
# G_DIR
#------------------------------------------------------------------------------
G_DIR = $${PWD}
INCLUDEPATH += $${G_DIR}
INCLUDEPATH += $${G_DIR}/g
!CONFIG(G_BUILD) {
	PRE_TARGETDEPS *= $${G_DIR}/lib/lib$${G_NAME}.a
	LIBS *= -L$${G_DIR}/lib -l$${G_NAME}
}

#------------------------------------------------------------------------------
# mingw
#------------------------------------------------------------------------------
mingw: DEFINES *= __USE_MINGW_ANSI_STDIO=1

#------------------------------------------------------------------------------
# common libs
#------------------------------------------------------------------------------
LIBS *= -levent -lglog

#------------------------------------------------------------------------------
# gstacktrace
#------------------------------------------------------------------------------
CONFIG(gstacktrace) {
	QMAKE_LFLAGS *= -rdynamic
}
