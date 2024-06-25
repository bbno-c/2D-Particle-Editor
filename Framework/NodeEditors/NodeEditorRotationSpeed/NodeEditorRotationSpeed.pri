!NODE_EDITOR_ROTATION_SPEED_PRI {

CONFIG += NODE_EDITOR_ROTATION_SPEED_PRI

INCLUDEPATH += $$PWD

include($$PWD/../../Widgets/FloatEdit/FloatEdit.pri)
include($$PWD/../../Widgets/RandomFloatEdit/RandomFloatEdit.pri)

HEADERS += \
    $$PWD/nodeeditorrotationspeed.h

SOURCES += \
    $$PWD/nodeeditorrotationspeed.cpp
}
