!VECTOR_2D_EDIT_PRI {

CONFIG += VECTOR_2D_EDIT_PRI

INCLUDEPATH += $$PWD

include($$PWD/../VectorEdit/VectorEdit.pri)

HEADERS += \
    $$PWD/vector2dedit.h

SOURCES += \
    $$PWD/vector2dedit.cpp
}
