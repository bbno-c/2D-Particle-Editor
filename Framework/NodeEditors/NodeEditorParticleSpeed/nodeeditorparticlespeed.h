#pragma once

#include "nodeeditor.h"

class FloatEdit;
class RandomFloatEdit;

class NodeEditorParticleSpeed : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorParticleSpeed(QWidget *parent = nullptr);
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private:
    FloatEdit *m_particleSpeed;
    RandomFloatEdit *m_randomParticleSpeed;

private slots:
    void onValueFloatEditChanged(float value);
    void onValueFloatRandomEditChanged(float value);
};
