#include "nodeeditorrotationspeed.h"

#include "../FloatEdit/floatedit.h"
#include "../RandomFloatEdit/randomfloatedit.h"

NodeEditorRotationSpeed::NodeEditorRotationSpeed(QWidget *parent) :
    NodeEditor(parent)
{
    m_rotationSpeed = new FloatEdit();
    m_rotationSpeed->setRange(-50.0f, 50.0f);
    addItem(QString("Rotation Speed:"), m_rotationSpeed);

    m_randomRotationSpeed = new RandomFloatEdit();
    m_randomRotationSpeed->setRange(-50.0f, 50.0f);
    addItem(QString("Particle Rotation Speed Random Range:"), m_randomRotationSpeed);

    QObject::connect(m_rotationSpeed, &FloatEdit::valueChanged, this, &NodeEditorRotationSpeed::onValueFloatEditChanged);
    QObject::connect(m_randomRotationSpeed, &RandomFloatEdit::valueChanged, this, &NodeEditorRotationSpeed::onValueFloatRandomEditChanged);
}

void NodeEditorRotationSpeed::resetEditor()
{
    m_rotationSpeed->setRange(0.0f, 5.0f);
    m_rotationSpeed->setValue(0.0f);

    m_randomRotationSpeed->setRange(0.0f, 5.0f);
    m_randomRotationSpeed->setValue(0.0f);
}

void NodeEditorRotationSpeed::onValueFloatEditChanged(float value)
{
    emit nodeEditorWidgetChanged("Particle Speed", value);
}

void NodeEditorRotationSpeed::onValueFloatRandomEditChanged(float value)
{
    m_rotationSpeed->setValue(value);
}

QJsonObject NodeEditorRotationSpeed::serialize() const
{
    QJsonObject obj;
    obj["rotation_speed"] = m_rotationSpeed->value();
    return obj;
}

void NodeEditorRotationSpeed::deserialize(const QJsonObject& object)
{
    if (!object["rotation_speed"].isNull())
        m_rotationSpeed->setValue(object["rotation_speed"].toDouble());
}
