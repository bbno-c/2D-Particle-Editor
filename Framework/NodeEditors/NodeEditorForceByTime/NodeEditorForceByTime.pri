!NODE_EDITOR_FORCE_BY_TIME_PRI {

CONFIG += NODE_EDITOR_FORCE_BY_TIME_PRI

INCLUDEPATH += $$PWD

include($$PWD/../../Widgets/Vector2DEdit/Vector2DEdit.pri)
include($$PWD/../../Widgets/CurveEditorDialog/CurveEditorDialog.pri)

include($$PWD/../../Utils/StringUtils/StringUtils.pri)

HEADERS += \
    $$PWD/nodeeditorforcebytime.h

SOURCES += \
    $$PWD/nodeeditorforcebytime.cpp
}
