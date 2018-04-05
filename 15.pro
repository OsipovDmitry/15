TEMPLATE = app
QT += opengl
CONFIG += c++11

HEADERS += \
    src/graphicscontroller.h \
    src/graphicsscene.h \
    src/graphicsmesh.h \
    src/graphicsmaterial.h \
    src/graphicsmodel.h \
    src/abstractgame.h \
	src/meshdata.h \
    src/game15.h \
	src/game15abstractscene.h \
	src/game15scenegame.h \
    src/gamewidget.h \
    src/game15scenemenu.h \
    src/game15sceneselectlevel.h \
    src/game15scenevictory.h \
    src/graphicsscenelayer.h \
    src/shaderdata.h

SOURCES += \
    src/graphicscontroller.cpp \
    src/graphicsmesh.cpp \
    src/graphicsmodel.cpp \
    src/graphicsscene.cpp \
    src/graphicsmaterial.cpp \
	src/abstractgame.cpp \
	src/gamewidget.cpp \
	src/game15.cpp \
	src/game15abstractscene.cpp \
	src/game15scenegame.cpp \
	src/main.cpp \
    src/game15scenemenu.cpp \
    src/game15sceneselectlevel.cpp \
    src/game15scenevictory.cpp \
    src/graphicsscenelayer.cpp

RESOURCES += \
		15.qrc
