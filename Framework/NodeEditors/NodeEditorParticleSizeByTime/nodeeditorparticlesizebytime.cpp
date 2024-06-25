#include "nodeeditorparticlesizebytime.h"

#include "curveeditordialog.h"

#include <QPushButton>
#include <QPalette>

NodeEditorParticleSizeByTime::NodeEditorParticleSizeByTime(QWidget *parent) :
    NodeEditor(parent)
{
    m_openCurveEditor = new QPushButton("Curve Editor");
    addItem(QString("Curve Editor:"), m_openCurveEditor);

    m_curveEditorDialog = new CurveEditorDialog();

    QObject::connect(m_openCurveEditor, &QPushButton::pressed, this, &NodeEditorParticleSizeByTime::onCurveEditorButtonPressed);
}

NodeEditorParticleSizeByTime::~NodeEditorParticleSizeByTime()
{
    delete m_curveEditorDialog;
    m_curveEditorDialog = nullptr;
}

void NodeEditorParticleSizeByTime::onCurveEditorButtonPressed()
{
    m_curveEditorDialog->show();
}

void NodeEditorParticleSizeByTime::resetEditor()
{
    m_curveEditorDialog->reset();
}

QJsonObject NodeEditorParticleSizeByTime::serialize() const
{
    return QJsonObject();
}

void NodeEditorParticleSizeByTime::deserialize(const QJsonObject& object)
{
}
