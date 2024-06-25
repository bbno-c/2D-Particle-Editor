#pragma once

#include "nodeeditor.h"

class IntEdit;

class NodeEditorEmitterRate : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorEmitterRate(QWidget *parent = nullptr);
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private slots:
    void onValueChanged(int value);

private:
    IntEdit *m_intEdit;
};
