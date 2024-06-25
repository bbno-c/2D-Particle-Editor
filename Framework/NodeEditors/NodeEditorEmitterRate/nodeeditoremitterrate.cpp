#include "nodeeditoremitterrate.h"

#include "../IntEdit/intedit.h"

NodeEditorEmitterRate::NodeEditorEmitterRate(QWidget *parent) :
    NodeEditor(parent)
{
    m_intEdit = new IntEdit;
    m_intEdit->setRange(0, 150);
    addItem(QString("Emitter Rate:"), m_intEdit);

    QObject::connect(m_intEdit, &IntEdit::valueChanged, this, &NodeEditorEmitterRate::onValueChanged);
}

void NodeEditorEmitterRate::onValueChanged(int value)
{
    emit nodeEditorWidgetChanged("Emitter Rate", value);
}

void NodeEditorEmitterRate::resetEditor()
{
    m_intEdit->setRange(0, 150);
    m_intEdit->setValue(0);
}

QJsonObject NodeEditorEmitterRate::serialize() const
{
    QJsonObject obj;
    obj["emitter_rate"] = m_intEdit->value();
    return obj;
}

void NodeEditorEmitterRate::deserialize(const QJsonObject& object)
{
    if (!object["emitter_rate"].isNull())
        m_intEdit->setValue(object["emitter_rate"].toInt());
}
