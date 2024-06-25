!RANDOM_FLOAT_EDIT_PRI {

CONFIG += RANDOM_FLOAT_EDIT_PRI

INCLUDEPATH += $$PWD

include($$PWD/../FloatEdit/FloatEdit.pri)

HEADERS += \
    $$PWD/randomfloatedit.h

SOURCES += \
    $$PWD/randomfloatedit.cpp
}
