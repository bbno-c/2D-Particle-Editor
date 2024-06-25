#include "nodeeditorparticlecolor.h"

#include "curveeditordialog.h"

#include <QPushButton>
#include <QPalette>

#include <QColorDialog>

NodeEditorParticleColor::NodeEditorParticleColor(QWidget *parent) :
    NodeEditor(parent)
{
    m_startColorButton = new QPushButton();
    m_startColorButton->setStyleSheet(QString("background-color: %1").arg(QColor(Qt::red).name()));
    addItem(QString("Start Color:"), m_startColorButton);

    m_endColorButton = new QPushButton();
    m_endColorButton->setStyleSheet(QString("background-color: %1").arg(QColor(Qt::red).name()));
    addItem(QString("End Color:"), m_endColorButton);

    m_rgbCurveEditor = new QPushButton("RGB");
    addItem(QString("RGB Curve Editor:"), m_rgbCurveEditor);

    m_alphaCurveEditor = new QPushButton("Alpha");
    addItem(QString("Alpha Curve Editor:"), m_alphaCurveEditor);

    m_startColorDialog = new QColorDialog();
    m_endColorDialog = new QColorDialog();

    m_curveEditorDialogRGB = new CurveEditorDialog();
    m_curveEditorDialogAlpha = new CurveEditorDialog();

    QObject::connect(m_startColorButton, &QPushButton::clicked, this, &NodeEditorParticleColor::onStartColorButtonPressed);
    QObject::connect(m_endColorButton, &QPushButton::clicked, this, &NodeEditorParticleColor::onEndColorButtonPressed);

    QObject::connect(m_startColorDialog, &QColorDialog::colorSelected, this, &NodeEditorParticleColor::onStartColorChanged);
    QObject::connect(m_endColorDialog, &QColorDialog::colorSelected, this, &NodeEditorParticleColor::onEndColorChanged);

    QObject::connect(m_rgbCurveEditor, &QPushButton::pressed, this, &NodeEditorParticleColor::onCurveEditorRGBButtonPressed);
    QObject::connect(m_alphaCurveEditor, &QPushButton::pressed, this, &NodeEditorParticleColor::onCurveEditorAlphaButtonPressed);
}

NodeEditorParticleColor::~NodeEditorParticleColor()
{
    delete m_curveEditorDialogRGB;
    m_curveEditorDialogRGB = nullptr;

    delete m_curveEditorDialogAlpha;
    m_curveEditorDialogAlpha = nullptr;
}

void NodeEditorParticleColor::onCurveEditorRGBButtonPressed()
{
    m_curveEditorDialogRGB->show();
}

void NodeEditorParticleColor::onCurveEditorAlphaButtonPressed()
{
    m_curveEditorDialogAlpha->show();
}

void NodeEditorParticleColor::resetEditor()
{
    onStartColorChanged(QColor(Qt::red));
    onEndColorChanged(QColor(Qt::red));
}

void NodeEditorParticleColor::onStartColorChanged(const QColor &color)
{
    m_startColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
    m_startColor = color;

    emit nodeEditorWidgetChanged("Start Color", color);
}

void NodeEditorParticleColor::onEndColorChanged(const QColor &color)
{
    m_endColorButton->setStyleSheet(QString("background-color: %1").arg(color.name()));
    m_endColor = color;

    emit nodeEditorWidgetChanged("End Color", color);
}

void NodeEditorParticleColor::onStartColorButtonPressed()
{
    m_startColorDialog->show();
}

void NodeEditorParticleColor::onEndColorButtonPressed()
{
    m_endColorDialog->show();
}

QJsonObject NodeEditorParticleColor::serialize() const
{
    QJsonObject obj;
    obj["start_color"] = m_startColor.name();
    obj["end_color"] = m_endColor.name();
    return obj;
}

void NodeEditorParticleColor::deserialize(const QJsonObject& object)
{
    if (!object["start_color"].isNull())
        onStartColorChanged(QColor(object["start_color"].toString()));

    if (!object["end_color"].isNull())
        onEndColorChanged(QColor(object["end_color"].toString()));
}
