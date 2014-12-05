#  -*- mode: makefile -*-

PROJECT		= qt
TYPE		= PLUGIN
PLUGIN_DIR	= plugins/Mu
PLUGINSUFFIX	= .so

IPATH		+= $(SRC_ROOT)/pub/gc 
LPATH_LINUX	+= /usr/local/Trolltech/Qt/lib

CXXFILES	= init
LIBS            = MuQt 

LIBS_LINUX      = QtUiTools
LIBS_DARWIN     = QtUiTools
#LIBS_DARWIN     = Qt5UiTools

FPATH += $(QTDIR)/lib
LPATH += $(QTDIR)/lib

FRAMEWORKS_DARWIN_QT5 = QtTest QtCore QtGui QtWebKit QtWidgets QtWebKitWidgets QtOpenGL QtSvg QtNetwork QtXml QtXmlPatterns

FRAMEWORKS_DARWIN_QT4 = QtCore QtGui QtWebKit QtOpenGL QtSvg phonon QtNetwork QtXml QtXmlPatterns

FRAMEWORKS_DARWIN = $(FRAMEWORKS_DARWIN_QT4)

LIBS_LINUX_QT4 = QtCore QtGui QtWebKit QtOpenGL QtNetwork QtSvg
LIBS_LINUX_QT5 = Qt5WebWidgets Qt5Widgets Qt5WebKit Qt5OpenGL Qt5Network Qt5Svg Qt5Test Qt5Gui Qt5Core 

LIBS_LINUX = $(LIBS_LINUX_QT4)

include $(SRC_ROOT)/build/Makefile.master
