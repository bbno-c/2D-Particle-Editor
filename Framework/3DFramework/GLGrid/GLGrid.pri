!GL_GRID_PRI {

CONFIG += GL_GRID_PRI

INCLUDEPATH += $$PWD

include($$PWD/../GLObject/GLObject.pri)

HEADERS += \
    $$PWD/glgrid.h

SOURCES += \
    $$PWD/glgrid.cpp

RESOURCES += \
    $$PWD/gridShaders.qrc
}
