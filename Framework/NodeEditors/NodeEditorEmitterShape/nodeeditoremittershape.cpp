#include "nodeeditoremittershape.h"

#include <QComboBox>

#include "../FloatEdit/floatedit.h"
#include "../Vector2DEdit/vector2dedit.h"
#include "stringutils.h"
#include <QVector2D>

NodeEditorEmitterShape::NodeEditorEmitterShape(QWidget *parent) :
    NodeEditor(parent)
{
    m_shape = new QComboBox();
    m_shape->addItems({"Sphere", "Cone", "Edge"});
    addItem(QString("Emitter Shape:"), m_shape);

    m_position = new Vector2DEdit();
    m_position->setMinimum(-500.0f);
    m_position->setMaximum(500.0f);
    addItem(QString("Emitter Position:"), m_position);

    m_size = new FloatEdit();
    m_size->setRange(0.0f, 200.0f);
    addItem(QString("Emitter Size:"), m_size);

    QObject::connect(m_shape,SIGNAL(currentIndexChanged(int)),this,SLOT(onValueEmitterShapeChanged(int)));
    QObject::connect(m_position, &Vector2DEdit::valueChanged, this, &NodeEditorEmitterShape::onValueEmitterPositionChanged);
    QObject::connect(m_size, &FloatEdit::valueChanged, this, &NodeEditorEmitterShape::onValueEmitterSizeChanged);
}

void NodeEditorEmitterShape::resetEditor()
{
    m_shape->setCurrentIndex(0);
    m_position->setValue(QVector2D(0.0f, 0.0f));
    m_size->setValue(0.0f);
}

void NodeEditorEmitterShape::onValueEmitterShapeChanged(int value)
{
    emit nodeEditorWidgetChanged("Emitter Shape", value);
}

void NodeEditorEmitterShape::onValueEmitterPositionChanged()
{
    emit nodeEditorWidgetChanged("Emitter Position", m_position->value());
}

void NodeEditorEmitterShape::onValueEmitterSizeChanged(float value)
{
    emit nodeEditorWidgetChanged("Emitter Size", value);
}

QJsonObject NodeEditorEmitterShape::serialize() const
{
    QJsonObject obj;
    obj["emitter_shape"] = m_shape->currentIndex();
    obj["emitter_position"] = StringUtils::QVector2DToQString(m_position->value());
    obj["emitter_size"] = m_size->value();
    return obj;
}

void NodeEditorEmitterShape::deserialize(const QJsonObject& object)
{
    if (!object["emitter_shape"].isNull())
        m_shape->setCurrentIndex(object["emitter_shape"].toInt());

    if (!object["emitter_position"].isNull())
        m_position->setValue(StringUtils::QStringToQVector2D(object["emitter_position"].toString()));

    if (!object["emitter_size"].isNull())
        m_size->setValue(object["emitter_size"].toDouble());
}
