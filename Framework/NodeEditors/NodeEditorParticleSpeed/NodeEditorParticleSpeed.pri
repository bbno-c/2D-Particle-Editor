!NODE_EDITOR_PARTICLE_SPEED_PRI {

CONFIG += NODE_EDITOR_PARTICLE_SPEED_PRI

INCLUDEPATH += $$PWD

include($$PWD/../../Widgets/FloatEdit/FloatEdit.pri)
include($$PWD/../../Widgets/RandomFloatEdit/RandomFloatEdit.pri)

HEADERS += \
    $$PWD/nodeeditorparticlespeed.h

SOURCES += \
    $$PWD/nodeeditorparticlespeed.cpp
}
