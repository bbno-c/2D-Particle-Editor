#pragma once

#include "nodeeditor.h"

class FloatEdit;
class RandomFloatEdit;

class NodeEditorRotationSpeed : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorRotationSpeed(QWidget *parent = nullptr);
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private:
    FloatEdit *m_rotationSpeed;
    RandomFloatEdit *m_randomRotationSpeed;

private slots:
    void onValueFloatEditChanged(float value);
    void onValueFloatRandomEditChanged(float value);
};
