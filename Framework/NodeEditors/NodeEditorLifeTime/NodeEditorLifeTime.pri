!NODE_EDITOR_LIFE_TIME_PRI {

CONFIG += NODE_EDITOR_LIFE_TIME_PRI

INCLUDEPATH += $$PWD

include($$PWD/../../Widgets/FloatEdit/FloatEdit.pri)
include($$PWD/../../Widgets/RandomFloatEdit/RandomFloatEdit.pri)

HEADERS += \
    $$PWD/nodeeditorlifetime.h

SOURCES += \
    $$PWD/nodeeditorlifetime.cpp
}
