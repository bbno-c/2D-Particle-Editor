!CURVE_EDITOR_DIALOG_PRI {

CONFIG += CURVE_EDITOR_DIALOG_PRI

INCLUDEPATH += $$PWD

include($$PWD/../CurveEditor/CurveEditor.pri)

HEADERS += \
    $$PWD/curveeditordialog.h

SOURCES += \
    $$PWD/curveeditordialog.cpp
}
