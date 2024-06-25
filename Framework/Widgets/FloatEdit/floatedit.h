#pragma once

#include <QLineEdit>

class FloatEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit FloatEdit(QWidget *parent = 0);
    ~FloatEdit();

    float value() const;
    float minimum() const;
    float maximum() const;

    void setValue(float value);
    void setMinimum(float min);
    void setMaximum(float max);
    void setRange(float min, float max);

    void setIncrement(float increment);
    float increment() const;

    QSize sizeHint() const override;
protected:
    typedef long long ValueType;

    ValueType m_value;
    ValueType precision;
    ValueType m_minimum;
    ValueType m_maximum;
    float m_increment;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void focusInEvent(QFocusEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

protected:
    static bool readValue(const QString &s, int precision, ValueType &value);
    static bool decomposeString(const QString &string, QChar &sSign, QString &sInt, QString &sDecimal);
    static bool isStringOfNumbers(const QString &string);

protected:
    ValueType clamp(const ValueType &value) const;
    void setIntValue(const ValueType &value);

protected:
    static QString valueToString(ValueType value, int precision);
    static QString removeTrailingZeros(const QString &string);

protected:
    ValueType precisionMult() const;

protected slots:
    void onEditingFinish();
signals:
    void valueChanged(float value);
};
