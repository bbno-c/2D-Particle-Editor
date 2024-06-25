!CONTEXT_NAVIGATION_3D_PRI {

CONFIG += CONTEXT_NAVIGATION_3D_PRI

INCLUDEPATH += $$PWD

include($$PWD/../Camera3D/Camera3D.pri)
include($$PWD/../Viewport3D/Viewport3D.pri)

HEADERS += \
    $$PWD/contextnavigation3d.h

SOURCES += \
    $$PWD/contextnavigation3d.cpp
}
