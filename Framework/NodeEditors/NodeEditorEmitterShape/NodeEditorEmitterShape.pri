!NODE_EDITOR_EMITTER_SHAPE_PRI {

CONFIG += NODE_EDITOR_EMITTER_SHAPE_PRI

INCLUDEPATH += $$PWD

include($$PWD/../../Widgets/Vector2DEdit/Vector2DEdit.pri)
include($$PWD/../../Widgets/FloatEdit/FloatEdit.pri)

include($$PWD/../../Utils/StringUtils/StringUtils.pri)

HEADERS += \
    $$PWD/nodeeditoremittershape.h

SOURCES += \
    $$PWD/nodeeditoremittershape.cpp
}
