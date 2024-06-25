!GL_OBJECT_PRI {

CONFIG += GL_OBJECT_PRI

INCLUDEPATH += $$PWD

include($$PWD/../View/View.pri)

HEADERS += \
    $$PWD/globject.h

SOURCES += \
    $$PWD/globject.cpp
}
