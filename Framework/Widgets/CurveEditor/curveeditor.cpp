#include "curveeditor.h"

#include <QPainter>
#include <QMouseEvent>

CurveEditor::CurveEditor(QEasingCurve::Type curveType, int nControlPoints, QWidget *parent)
    : m_curveType(curveType),
    m_nControlPoints(nControlPoints),
    QWidget(parent)
{
    setFixedSize(600, 400);
    createCurvePoints();
}

void CurveEditor::setCurveType(QEasingCurve::Type curveType)
{
    m_curveType = curveType;
    createCurvePoints();
    update();
}

void CurveEditor::reset()
{
    createCurvePoints();
}

void CurveEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int height = this->height();

    // Рисуем фон
    painter.fillRect(0, 0, width, height, Qt::white);

    painter.setPen(Qt::blue);
    painter.drawPolyline(m_curvePoints);

    painter.setPen(Qt::red);
    for (const QPointF &point : m_curvePoints)
        painter.drawEllipse(point, m_pointSize, m_pointSize);
}

void CurveEditor::mousePressEvent(QMouseEvent *event)
{
    for (int i = 0; i < m_curvePoints.size(); ++i) {
        if (QPointF(event->pos() - m_curvePoints[i]).manhattanLength() < m_pointSize) {
            m_isDragging = true;
            m_dragIndex = i;
            return;
        }
    }
}

void CurveEditor::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging) {
        m_curvePoints[m_dragIndex] = event->pos();
        update();
    }
}

void CurveEditor::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isDragging && event->button() == Qt::LeftButton) {
        m_isDragging = false;
        m_dragIndex = -1;
    }
}

void CurveEditor::createCurvePoints()
{
    m_curvePoints.clear();

    QEasingCurve curve(m_curveType);

    for (int i = 0; i < m_nControlPoints; ++i) {
        qreal x = static_cast<qreal>(i) / (m_nControlPoints - 1);
        qreal y = 1 - curve.valueForProgress(x);
        m_curvePoints.append(QPointF(x * width(), y * height()));
    }
}
