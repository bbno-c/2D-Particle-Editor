!VIEWPORT_3D {

CONFIG += VIEWPORT_3D

INCLUDEPATH += $$PWD

include($$PWD/../Camera3D/Camera3D.pri)
include($$PWD/../GLObject/GLObject.pri)

HEADERS += \
    $$PWD/viewport3d.h

SOURCES += \
    $$PWD/viewport3d.cpp

}
