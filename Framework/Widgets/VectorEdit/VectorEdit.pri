!VECTOR_EDIT_PRI {

CONFIG += VECTOR_EDIT_PRI

INCLUDEPATH += $$PWD

include($$PWD/../FloatEdit/FloatEdit.pri)

HEADERS += \
    $$PWD/vectoredit.h

SOURCES += \
    $$PWD/vectoredit.cpp
}
