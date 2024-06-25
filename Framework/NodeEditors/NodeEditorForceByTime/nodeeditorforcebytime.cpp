#include "nodeeditorforcebytime.h"

#include "../Vector2DEdit/vector2dedit.h"
#include "stringutils.h"
#include "curveeditordialog.h"

#include <QPushButton>
#include <QVector2D>
#include <QCheckBox>

NodeEditorForceByTime::NodeEditorForceByTime(QWidget *parent) :
    NodeEditor(parent)
{
    m_forceByTimeEdit = new Vector2DEdit();
    m_forceByTimeEdit->setMinimum(-50.0f);
    m_forceByTimeEdit->setMaximum(50.0f);
    addItem(QString("Force By Time:"), m_forceByTimeEdit);

    m_isUseCurve = new QCheckBox();
    addItem(QString("Use Curve:"), m_isUseCurve);

    m_openCurveEditor = new QPushButton("Open Curve Editor");
    addItem(QString("Curve Editor:"), m_openCurveEditor);

    m_curveEditorDialog = new CurveEditorDialog();

    QObject::connect(m_forceByTimeEdit, &Vector2DEdit::valueChanged, this, &NodeEditorForceByTime::onValueChanged);
    QObject::connect(m_isUseCurve, &QCheckBox::clicked, this, &NodeEditorForceByTime::onUseCurveCheckBoxChanged);
    QObject::connect(m_openCurveEditor, &QPushButton::pressed, this, &NodeEditorForceByTime::onCurveEditorButtonPressed);
}

NodeEditorForceByTime::~NodeEditorForceByTime()
{
    delete m_curveEditorDialog;
    m_curveEditorDialog = nullptr;
}

void NodeEditorForceByTime::onValueChanged()
{
    emit nodeEditorWidgetChanged("Force By Time", m_forceByTimeEdit->value());
}

void NodeEditorForceByTime::onUseCurveCheckBoxChanged(bool isUseCurve)
{
    m_forceByTimeEdit->setEnabled(!isUseCurve);
    emit nodeEditorWidgetChanged("Force By Time (curve)", QPointF());
}

void NodeEditorForceByTime::onCurveEditorButtonPressed()
{
    m_curveEditorDialog->show();
}

void NodeEditorForceByTime::resetEditor()
{
    m_forceByTimeEdit->setValue(QVector2D(0.0f, 0.0f));
    m_curveEditorDialog->reset();
}

QJsonObject NodeEditorForceByTime::serialize() const
{
    QJsonObject obj;
    obj["force_by_time"] = StringUtils::QVector2DToQString(m_forceByTimeEdit->value());
    return obj;
}

void NodeEditorForceByTime::deserialize(const QJsonObject& object)
{
    if (!object["force_by_time"].isNull())
        return m_forceByTimeEdit->setValue(StringUtils::QStringToQVector2D(object["force_by_time"].toString()));
}
