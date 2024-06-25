#include "vectoredit.h"

#include <QKeyEvent>
#include <QHBoxLayout>

#include "floatedit.h"

VectorEdit::VectorEdit(int count, QWidget *parent) :
    m_pCount(count),
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setMargin(0);
    for (int editInd = 0; editInd < m_pCount; ++editInd) {
        FloatEdit *edit = new FloatEdit();
        edits << edit;
        layout->addWidget(edit);
        QObject::connect(edit,SIGNAL(valueChanged(float)),this,SIGNAL(valueChanged()));
    }
    setLayout(layout);
}

VectorEdit::~VectorEdit()
{
}

void VectorEdit::setMinimum(float value)
{
    foreach(FloatEdit *edit, edits)
        edit->setMinimum(value);
}

void VectorEdit::setMaximum(float value)
{
    foreach(FloatEdit *edit, edits)
        edit->setMaximum(value);
}

void VectorEdit::setIncrement(float value)
{
    foreach(FloatEdit *edit, edits)
        edit->setIncrement(value);
}
