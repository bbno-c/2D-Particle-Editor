#include "nodeeditormaxparticles.h"

#include "../IntEdit/intedit.h"

#include <QDebug>

NodeEditorMaxParticles::NodeEditorMaxParticles(QWidget *parent) :
    NodeEditor(parent)
{
    m_maxParticles = new IntEdit();
    m_maxParticles->setRange(0, 1500);
    addItem(QString("Max Particles:"), m_maxParticles);

    QObject::connect(m_maxParticles, &IntEdit::valueChanged, this, &NodeEditorMaxParticles::onValueMaxParticlesChanged);
}

void NodeEditorMaxParticles::resetEditor()
{
    m_maxParticles->setValue(0);
}

void NodeEditorMaxParticles::onValueMaxParticlesChanged(int value)
{
    emit nodeEditorWidgetChanged("Max Particles", value);
}

QJsonObject NodeEditorMaxParticles::serialize() const
{
    QJsonObject obj;
    obj["max_particles"] = m_maxParticles->value();
    return obj;
}

void NodeEditorMaxParticles::deserialize(const QJsonObject& object)
{
    if (!object["max_particles"].isNull())
        m_maxParticles->setValue(object["max_particles"].toInt());
}
