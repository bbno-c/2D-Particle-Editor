#pragma once

#include "nodeeditor.h"

class QPushButton;
class CurveEditorDialog;

class NodeEditorParticleSizeByTime : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorParticleSizeByTime(QWidget *parent = nullptr);
    ~NodeEditorParticleSizeByTime();
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private slots:
    void onCurveEditorButtonPressed();

private:
    QPushButton *m_openCurveEditor;

    CurveEditorDialog *m_curveEditorDialog;
};
