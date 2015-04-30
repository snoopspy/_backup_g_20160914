#------------------------------------------------------------------------------
# Debug and Release
#------------------------------------------------------------------------------
CONFIG(debug, debug|release)   DEFINES += _DEBUG
CONFIG(release, debug|release) DEFINES += _RELEASE

#------------------------------------------------------------------------------
# G_NAME
#------------------------------------------------------------------------------
G_NAME = g
android-g++:                 G_NAME = $${G_NAME}_android
contains(QT, gui)            G_NAME = $${G_NAME}_gui
CONFIG(debug, debug|release) G_NAME = $${G_NAME}_d

message("G_NAME="$${G_NAME}) # gilgil temp 2015.04.27
message("DEFINES="$${DEFINES}) # gilgil temp 2015.04.27
message("CONFIG="$${CONFIG}) # gilgil temp 2015.04.27

#------------------------------------------------------------------------------
# G_DIR
#------------------------------------------------------------------------------
G_DIR = $${PWD}
INCLUDEPATH += $${G_DIR}/src
!CONFIG(G_BUILD) {
	PRE_TARGETDEPS +=  $${G_DIR}/lib/lib$${G_NAME}.a
	LIBS           += -L$${G_DIR}/lib -l$${G_NAME}
	LIBS           += -l$${G_NAME}
}

#------------------------------------------------------------------------------
# mingw
#------------------------------------------------------------------------------
mingw: DEFINES += __USE_MINGW_ANSI_STDIO=1
