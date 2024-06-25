#pragma once

#include "nodeeditor.h"

class FloatEdit;
class RandomFloatEdit;

class NodeEditorLifeTime : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorLifeTime(QWidget *parent = nullptr);
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private:
    FloatEdit *m_floatEdit;
    RandomFloatEdit *m_randomFloatEdit;

private slots:
    void onValueFloatEditChanged(float value);
    void onValueFloatRandomEditChanged(float value);
};
