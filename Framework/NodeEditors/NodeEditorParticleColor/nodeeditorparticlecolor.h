#pragma once

#include "nodeeditor.h"

class QPushButton;
class QColorDialog;
class QColor;
class CurveEditorDialog;

class NodeEditorParticleColor : public NodeEditor
{
    Q_OBJECT
public:
    explicit NodeEditorParticleColor(QWidget *parent = nullptr);
    ~NodeEditorParticleColor();
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

private:
    QPushButton *m_startColorButton;
    QPushButton *m_endColorButton;

    QPushButton *m_rgbCurveEditor;
    QPushButton *m_alphaCurveEditor;

    QColorDialog *m_startColorDialog;
    QColorDialog *m_endColorDialog;

    QColor m_startColor;
    QColor m_endColor;

    CurveEditorDialog *m_curveEditorDialogRGB;
    CurveEditorDialog *m_curveEditorDialogAlpha;

private slots:
    void onStartColorChanged(const QColor &color);
    void onEndColorChanged(const QColor &color);

    void onStartColorButtonPressed();
    void onEndColorButtonPressed();

    void onCurveEditorRGBButtonPressed();
    void onCurveEditorAlphaButtonPressed();
};
