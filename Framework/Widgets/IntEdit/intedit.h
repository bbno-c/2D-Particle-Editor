#pragma once

#include <QLineEdit>

class IntEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit IntEdit(QWidget *parent = 0);
    ~IntEdit();

    int value() const;
    int minimum() const;
    int maximum() const;

    void setValue(int value);
    void setMinimum(int min);
    void setMaximum(int max);

    void setRange(int min, int max);

    void setIncrement(int increment);

    QSize sizeHint() const override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

protected:
    int m_value;

    int m_minValue;
    int m_maxValue;

    int m_increment;

private:
    static bool readIntValue(const QString &s, int &value);
    static QString intToString(int value);
    int clamp(int value) const;

protected slots:
    void onEditingFinish();

signals:
    void valueChanged(int value);
};
