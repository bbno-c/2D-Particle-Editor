!NODE_EDITOR_PRI {

CONFIG += NODE_EDITOR_PRI

INCLUDEPATH += $$PWD

include($$PWD/../../Utils/ISerializable/ISerializable.pri)

include($$PWD/../NodeEditorLifeTime/NodeEditorLifeTime.pri)
include($$PWD/../NodeEditorEmitterRate/NodeEditorEmitterRate.pri)
include($$PWD/../NodeEditorStartTransformation/NodeEditorStartTransformation.pri)
include($$PWD/../NodeEditorMaxParticles/NodeEditorMaxParticles.pri)
include($$PWD/../NodeEditorEmitterShape/NodeEditorEmitterShape.pri)
include($$PWD/../NodeEditorForceByTime/NodeEditorForceByTime.pri)
include($$PWD/../NodeEditorParticleSpeed/NodeEditorParticleSpeed.pri)
include($$PWD/../NodeEditorRotationSpeed/NodeEditorRotationSpeed.pri)
include($$PWD/../NodeEditorParticleSizeByTime/NodeEditorParticleSizeByTime.pri)
include($$PWD/../NodeEditorParticleColor/NodeEditorParticleColor.pri)
include($$PWD/../NodeEditorTrailType/NodeEditorTrailType.pri)

HEADERS += \
    $$PWD/nodeeditor.h \
    $$PWD/nodeeditorfactory.h

SOURCES += \
    $$PWD/nodeeditor.cpp
}
