#pragma once

#include <QWidget>
#include <QEasingCurve>

class CurveEditor : public QWidget
{
    Q_OBJECT
public:
    CurveEditor(QEasingCurve::Type curveType, int nControlPoints, QWidget *parent = nullptr);

    void setCurveType(QEasingCurve::Type curveType);
    void reset();

protected:
    void paintEvent(QPaintEvent *event) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void createCurvePoints();

private:
    QVector<QPointF> m_curvePoints;
    QEasingCurve::Type m_curveType;
    int m_nControlPoints;

private:
    bool m_isDragging;
    int m_dragIndex;

    const int m_pointSize = 5;
};
