#include "contextnavigation3d.h"

ContextNavigation3D::ContextNavigation3D(Viewport3D *viewport, Camera3D *camera, QObject *parent) :
    m_viewport(viewport),
    m_camera(camera),
    m_startPosition(0.0f, 0.0f),
    m_currentPosition(0.0, 0.0),
    m_rotation(),
    m_rotationX(),
    m_rotationY(),
    m_zoomFactorZ(0.25f),
    m_speedPan(1200.0f),
    m_currentZoomZ(0.0f),
    QObject(parent)
{
    m_viewport->installEventFilter(this);

    if (m_camera)
        m_currentZoomZ = m_camera->position().z();
}

ContextNavigation3D::~ContextNavigation3D()
{
    m_viewport->removeEventFilter(this);
}

bool ContextNavigation3D::eventFilter(QObject *watched, QEvent *event)
{
    if (watched != m_viewport)
        return false;

    if (event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        cameraZoom(wheelEvent->delta());
        return true;
    }

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::MiddleButton && (mouseEvent->modifiers() & Qt::ControlModifier))
            m_startPosition = QVector2D(mouseEvent->pos());
        if (mouseEvent->button() == Qt::LeftButton && (mouseEvent->modifiers() & Qt::ControlModifier))
            m_startPosition = QVector2D(mouseEvent->pos());

        return true;
    }

    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->buttons() == Qt::MiddleButton && (mouseEvent->modifiers() & Qt::ControlModifier))
            cameraPan(QVector2D(mouseEvent->localPos()));
        if (mouseEvent->buttons() == Qt::LeftButton && (mouseEvent->modifiers() & Qt::ControlModifier))
            cameraRotation(QVector2D(mouseEvent->localPos()));

        return true;
    }

    return false;
}

void ContextNavigation3D::cameraZoom(const int delta)
{
    m_currentZoomZ = delta > 0 ? m_zoomFactorZ : -m_zoomFactorZ;
    m_camera->setPosition(m_camera->position() + QVector3D(0.0f, 0.0f, m_currentZoomZ));
    m_viewport->update();
}

void ContextNavigation3D::cameraPan(const QVector2D &mousePosition)
{
    QVector2D diff = mousePosition - m_startPosition;
    m_startPosition = mousePosition;

    m_currentPosition += QVector2D(diff.x() / m_speedPan, -diff.y() / m_speedPan);

    m_camera->setPosition(QVector3D(m_currentPosition.x(), m_currentPosition.y(), m_camera->position().z()));
    m_viewport->update();
}

void ContextNavigation3D::cameraRotation(const QVector2D &mousePosition)
{
    QVector2D diff = mousePosition - m_startPosition;
    m_startPosition = mousePosition;

    const float angleX = diff.y() / 2.0f;
    const float angleY = diff.x() / 2.0f;
    QQuaternion rotateX = QQuaternion::fromAxisAndAngle(0.0f, 1.0f, 0.0f, angleY);
    QQuaternion rotateY = QQuaternion::fromAxisAndAngle(1.0f, 0.0f, 0.0f, angleX);

    m_rotationX = rotateX * m_rotationX;
    m_rotation = m_rotationX * m_rotationY;
    m_camera->setRotation(m_rotation.toEulerAngles());

    m_rotationY = rotateY * m_rotationY;
    m_rotation = m_rotationY * m_rotationX;
    m_camera->setRotation(m_rotation.toEulerAngles());

    m_viewport->update();
}
