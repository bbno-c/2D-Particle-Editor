#include "intedit.h"

#include <QKeyEvent>

IntEdit::IntEdit(QWidget *parent) :
    m_value(0),
    m_minValue(0),
    m_maxValue(100),
    m_increment(1),
    QLineEdit(parent)
{
    setFocusPolicy(Qt::WheelFocus);
    setText(intToString(m_value));
    QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(onEditingFinish()));
}

IntEdit::~IntEdit()
{
}

int IntEdit::value() const
{
    return m_value;
}

int IntEdit::minimum() const
{
    return m_minValue;
}

int IntEdit::maximum() const
{
    return m_maxValue;
}

void IntEdit::setValue(int value)
{
    setText(intToString(value));

    if (value == m_value)
        return;

    m_value = value;

    emit valueChanged(m_value);
}

void IntEdit::setMinimum(int min)
{
    m_minValue = min;
    m_maxValue = qMax(m_minValue, m_maxValue);
}

void IntEdit::setMaximum(int max)
{
    m_maxValue = max;
    m_minValue = qMin(m_minValue, m_maxValue);
}

void IntEdit::setRange(int min, int max)
{
    Q_ASSERT(min <= max);
    m_minValue = min;
    m_maxValue = max;
}

void IntEdit::setIncrement(int increment)
{
    m_increment = increment;
}

QSize IntEdit::sizeHint() const
{
    return QSize(60, 20);
}

void IntEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
    if ((event->key() == Qt::Key_Return) || (event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Escape)) {
        QWidget *widget = this->window();
        if (widget == nullptr)
            return;
        widget->setFocus();
    }
}

void IntEdit::wheelEvent(QWheelEvent *event)
{
    if (!hasFocus()) {
        QLineEdit::wheelEvent(event);
        return;
    }
    const int delta = (event->delta() >= 0) * 2 - 1;
    const int valueDst = clamp(m_value + delta * m_increment);

    if (valueDst == value())
        return;

    setValue(valueDst);
    selectAll();
    event->accept();
}

bool IntEdit::readIntValue(const QString &s, int &value)
{
    bool converted;
    const int val = s.toInt(&converted);

    if (!converted)
        return false;

    value = val;
    return true;
}

QString IntEdit::intToString(int value)
{
    return QString::number(value);
}

int IntEdit::clamp(int value) const
{
    return qMin(m_maxValue, qMax(m_minValue, value));
}

void IntEdit::onEditingFinish()
{
    int value = m_value;

    if (readIntValue(text(), value))
        value = clamp(value);

    setValue(value);
}
