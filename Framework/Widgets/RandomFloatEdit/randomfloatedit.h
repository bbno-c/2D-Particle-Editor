#pragma once

#include <QWidget>

class FloatEdit;

class RandomFloatEdit : public QWidget
{
    Q_OBJECT
public:
    explicit RandomFloatEdit(QWidget *parent = 0);

    void setRange(float min, float max);

    void setValue(float value);
    float value() const;

signals:
    void valueChanged(float value);

private slots:
    void onLocaValueChanged(float value);

private:
    QVector<FloatEdit*> m_edits;

    float m_value;
};
