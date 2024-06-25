#include "floatedit.h"

#include <QKeyEvent>
#include <QtMath>
#include <limits.h>

FloatEdit::FloatEdit(QWidget *parent) :
    m_value(0),
    precision(6),
    m_minimum(0 * precisionMult()),
    m_maximum(100 * precisionMult()),
    m_increment(0.1),
    QLineEdit(parent)
{
    setFocusPolicy(Qt::WheelFocus);
    setText(removeTrailingZeros(valueToString(m_value, precision)));
    QObject::connect(this, SIGNAL(editingFinished()), this, SLOT(onEditingFinish()));
}

FloatEdit::~FloatEdit()
{
}

float FloatEdit::value() const
{
    return m_value / double(precisionMult());
}

float FloatEdit::minimum() const
{
    return m_minimum / double(precisionMult());
}

float FloatEdit::maximum() const
{
    return m_maximum / double(precisionMult());
}

void FloatEdit::setValue(float value)
{
    const ValueType val = value * precisionMult();
    setIntValue(val);
}

void FloatEdit::setMinimum(float min)
{
    m_minimum = min * precisionMult();
    m_maximum = qMax(m_minimum, m_maximum);
}

void FloatEdit::setMaximum(float max)
{
    m_maximum = max * precisionMult();
    m_minimum = qMin(m_minimum, m_maximum);
}

void FloatEdit::setRange(float min, float max)
{
    Q_ASSERT(min <= max);
    m_minimum = min * precisionMult();
    m_maximum = max * precisionMult();
}

QSize FloatEdit::sizeHint() const
{
    return QSize(60, 20);
}

void FloatEdit::setIncrement(float increment)
{
    m_increment = increment;
}

float FloatEdit::increment() const
{
    return m_increment;
}

void FloatEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
    if ((event->key() == Qt::Key_Return) || (event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Escape)) {
        QWidget *widget = this->window();
        if (widget == nullptr)
            return;

        widget->setFocus();
    }
}

void FloatEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    selectAll();
}

bool FloatEdit::readValue(const QString &s, int precision, ValueType &value)
{
    QChar sSign;
    QString sInt;
    QString sDecimal;

    if (!decomposeString(s, sSign, sInt, sDecimal))
        return false;

    int valueInt = 0;

    if (!sInt.isEmpty()) {
        bool converted;
        valueInt = sInt.toInt(&converted);
        if (!converted)
            return false;
    }

    int valueDecimal = 0;

    if (!sDecimal.isEmpty()) {
        sDecimal = sDecimal.mid(0, precision);
        bool converted;
        valueDecimal = sDecimal.toInt(&converted);
        if (!converted)
            return false;
    }

    const int sign = (sSign == '-' ? -1 : 1);
    value = sign * (qAbs(valueInt) * pow(10.0, precision) + valueDecimal * pow(10.0, precision - sDecimal.length()));
    return true;
}

bool FloatEdit::decomposeString(const QString &string, QChar &sSign, QString &sInt, QString &sDecimal)
{
    sSign = QChar();
    QString s = string;
    s = s.trimmed();

    if (s.isEmpty())
        return false;

    const int dotPos = s.indexOf('.');
    const bool hasDot = (dotPos != -1);

    if (hasDot) {
        sInt = s.mid(0, dotPos);
        sDecimal = s.mid(dotPos + 1);
    } else {
        sInt = s;
        sDecimal = QString();
    }

    if (hasDot && sDecimal.isEmpty())
        return false;

    if (!sDecimal.isEmpty() && !isStringOfNumbers(sDecimal))
        return false;

    if (sInt.isEmpty())
        return true;

    const QChar first = sInt[0];
    if ((first == '-') || (first == '+')) {
        sSign = first;
        sInt = sInt.mid(1);
    }
    return isStringOfNumbers(sInt);
}

bool FloatEdit::isStringOfNumbers(const QString &string)
{
    foreach(const QChar &c, string)
        if (!c.isNumber())
            return false;

    return true;
}

FloatEdit::ValueType FloatEdit::clamp(const ValueType &value) const
{
    return qMin(m_maximum, qMax(m_minimum, value));
}

void FloatEdit::setIntValue(const ValueType &value)
{
    const ValueType val = clamp(value);
    setText(removeTrailingZeros(valueToString(val, precision)));

    if (val == m_value)
        return;

    m_value = val;

    emit valueChanged(this->value());
}

QString FloatEdit::valueToString(ValueType value, int precision)
{
    QString s = QString::number(qAbs(value)).rightJustified(precision + 1, '0');
    s.insert(s.length() - precision, ".");
    const QString sign = (value < 0 ? "-" : "");
    s = sign + s;
    return s;
}

QString FloatEdit::removeTrailingZeros(const QString &string)
{
    for (int i = string.length() - 1; i >= 0; --i) {
        const QChar c = string[i];
        if ((c == '.') || (c == ','))
            return string.mid(0, i);
        if (c != '0')
            return string.mid(0, i + 1);
    }
    return string;
}

void FloatEdit::wheelEvent(QWheelEvent *event)
{
    if (!hasFocus()) {
        QLineEdit::wheelEvent(event);
        return;
    }

    const int delta = (event->delta() >= 0) * 2 - 1;
    const ValueType valueDst = clamp(m_value + delta * ValueType(m_increment * precisionMult()));

    setIntValue(valueDst);
    selectAll();

    event->accept();
}

FloatEdit::ValueType FloatEdit::precisionMult() const
{
    return pow(10.0, precision);
}

void FloatEdit::onEditingFinish()
{
    ValueType value = m_value;

    if (readValue(text(), precision, value))
        value = clamp(value);

    setIntValue(value);
}
