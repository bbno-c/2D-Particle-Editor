#include "randomfloatedit.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QRandomGenerator>

#include "floatedit.h"

RandomFloatEdit::RandomFloatEdit(QWidget *parent) :
    m_value(0.0f),
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    for (int editInd = 0; editInd < 2; ++editInd) {
        FloatEdit *edit = new FloatEdit();
        m_edits << edit;
        layout->addWidget(edit);
        QObject::connect(edit,SIGNAL(valueChanged(float)),this,SLOT(onLocaValueChanged(float)));
    }

    setLayout(layout);
}

void RandomFloatEdit::setRange(float min, float max)
{
    m_edits[0]->setRange(min, max);
    m_edits[1]->setRange(min, max);
}

void RandomFloatEdit::setValue(float value)
{
    m_value = value;
}

float RandomFloatEdit::value() const
{
    return m_value;
}

void RandomFloatEdit::onLocaValueChanged(float value)
{
    FloatEdit *changedEdit = qobject_cast<FloatEdit*>(sender());

    if (changedEdit && (m_edits.indexOf(changedEdit) == 0))
        m_edits[1]->setValue(changedEdit->value() + (2.0f * m_edits[1]->increment()));

    float min = qMin(m_edits[0]->value(), m_edits[1]->value());
    float max = qMax(m_edits[0]->value(), m_edits[1]->value());

    double randomDouble = QRandomGenerator::global()->generateDouble();
    m_value = min + static_cast<float>(randomDouble) * (max - min);

    emit valueChanged(m_value);
}
