QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/../Framework/3DFramework/ContextNavigation3D/ContextNavigation3D.pri)
include($$PWD/../Framework/3DFramework/GLGrid/GLGrid.pri)
include($$PWD/../Framework/3DFramework/GLTranslateHelper/GLTranslateHelper.pri)

include($$PWD/../Framework/Utils/ISerializable/ISerializable.pri)
include($$PWD/../Framework/Utils/JsonFileUtils/JsonFileUtils.pri)
include($$PWD/../Framework/Utils/PathFileUtils/PathFileUtils.pri)

include($$PWD/../Framework/NodeEditors/NodeEditor/NodeEditor.pri)
include($$PWD/../Framework/NodeViewer/NodeViewer.pri)
include($$PWD/../Framework/NodeContainer/NodeContainer.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
