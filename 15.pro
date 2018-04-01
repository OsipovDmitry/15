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
    src/gamewidget.h

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
	src/main.cpp

RESOURCES += \
		15.qrc
