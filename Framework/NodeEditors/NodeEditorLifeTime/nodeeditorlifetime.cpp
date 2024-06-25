#include "nodeeditorlifetime.h"

#include "../FloatEdit/floatedit.h"
#include "../RandomFloatEdit/randomfloatedit.h"

#include <QDebug>

NodeEditorLifeTime::NodeEditorLifeTime(QWidget *parent) :
    NodeEditor(parent)
{
    m_floatEdit = new FloatEdit;
    m_floatEdit->setRange(0.0f, 5.0f);
    addItem(QString("Life Time:"), m_floatEdit);

    m_randomFloatEdit = new RandomFloatEdit();
    m_randomFloatEdit->setRange(0.0f, 5.0f);
    addItem(QString("Life Time Random Range:"), m_randomFloatEdit);

    QObject::connect(m_floatEdit, &FloatEdit::valueChanged, this, &NodeEditorLifeTime::onValueFloatEditChanged);
    QObject::connect(m_randomFloatEdit, &RandomFloatEdit::valueChanged, this, &NodeEditorLifeTime::onValueFloatRandomEditChanged);
}

void NodeEditorLifeTime::resetEditor()
{
    m_floatEdit->setRange(0.0f, 5.0f);
    m_floatEdit->setValue(0.0f);

    m_randomFloatEdit->setRange(0.0f, 5.0f);
    m_floatEdit->setValue(0.0f);
}

void NodeEditorLifeTime::onValueFloatEditChanged(float value)
{
    emit nodeEditorWidgetChanged("Life Time", value);
}

void NodeEditorLifeTime::onValueFloatRandomEditChanged(float value)
{
    m_floatEdit->setValue(value);
}

QJsonObject NodeEditorLifeTime::serialize() const
{
    QJsonObject obj;
    obj["life_time"] = m_floatEdit->value();
    return obj;
}

void NodeEditorLifeTime::deserialize(const QJsonObject& object)
{
    if (!object["life_time"].isNull())
        m_floatEdit->setValue(object["life_time"].toDouble());
}
