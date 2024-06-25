#include "vector2dedit.h"

#include <QVector2D>

#include "floatedit.h"

Vector2DEdit::Vector2DEdit(QWidget *parent) :
    VectorEdit(2, parent)
{
}

QVector2D Vector2DEdit::value() const
{
    QVector2D value;
    for (int i = 0; i < m_pCount; ++i)
        value[i] = edits[i]->value();
    return value;
}

void Vector2DEdit::setValue(const QVector2D &value)
{
    for (int i = 0; i < m_pCount; ++i)
        edits[i]->setValue(value[i]);
}
