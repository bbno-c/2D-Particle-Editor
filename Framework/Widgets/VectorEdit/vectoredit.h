#pragma once

#include <QWidget>

class FloatEdit;

class VectorEdit : public QWidget
{
    Q_OBJECT
public:
    explicit VectorEdit(int count, QWidget *parent = 0);
    virtual ~VectorEdit();

    void setMinimum(float value);
    void setMaximum(float value);
    void setIncrement(float value);
protected:
    int m_pCount;
    QVector<FloatEdit*> edits;

signals:
    void valueChanged();
};
