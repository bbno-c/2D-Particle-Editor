!NODE_VIEWER_PRI {

CONFIG += NODE_VIEWER_PRI

INCLUDEPATH += $$PWD

include($$PWD/../ISerializable/ISerializable.pri)

HEADERS += \
    $$PWD/nodeviewer.h

SOURCES += \
    $$PWD/nodeviewer.cpp
}
