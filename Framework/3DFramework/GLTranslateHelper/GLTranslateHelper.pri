!GL_TRANSLATE_HELPER_PRI {

CONFIG += GL_TRANSLATE_HELPER_PRI

INCLUDEPATH += $$PWD

include($$PWD/../GLObject/GLObject.pri)

HEADERS += \
    $$PWD/gltranslatehelper.h

SOURCES += \
    $$PWD/gltranslatehelper.cpp

RESOURCES += \
    $$PWD/translationShader.qrc
}
