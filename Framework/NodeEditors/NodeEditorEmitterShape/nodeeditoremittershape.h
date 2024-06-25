#pragma once

#include "nodeeditor.h"

class QComboBox;
class Vector2DEdit;
class FloatEdit;
class QVector2D;

class NodeEditorEmitterShape : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorEmitterShape(QWidget *parent = nullptr);
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private:
    QComboBox *m_shape;
    Vector2DEdit *m_position;
    FloatEdit *m_size;

private slots:
    void onValueEmitterShapeChanged(int value);
    void onValueEmitterPositionChanged();
    void onValueEmitterSizeChanged(float value);
};
