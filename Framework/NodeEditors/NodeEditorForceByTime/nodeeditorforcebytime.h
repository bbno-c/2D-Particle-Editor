#pragma once

#include "nodeeditor.h"

class Vector2DEdit;
class QPushButton;
class QCheckBox;
class CurveEditorDialog;

class NodeEditorForceByTime : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorForceByTime(QWidget *parent = nullptr);
    ~NodeEditorForceByTime();

    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private slots:
    void onValueChanged();
    void onUseCurveCheckBoxChanged(bool isUseCurve);

    void onCurveEditorButtonPressed();

private:
    Vector2DEdit *m_forceByTimeEdit;
    QPushButton *m_openCurveEditor;
    QCheckBox *m_isUseCurve;

    CurveEditorDialog *m_curveEditorDialog;
};
