#include "camera3d.h"

Camera3D::Camera3D(const QVector3D &position, float fovY) :
    m_position(position),
    m_fovY(fovY)
{
}

Camera3D::Camera3D(const QVector3D &position, const QVector3D &EulerAngles, float fovY) :
    m_position(position),
    m_rotation(QQuaternion::fromEulerAngles(EulerAngles)),
    m_fovY(fovY)
{
}

void Camera3D::setFovY(float fovY)
{
    m_fovY = fovY;
}

void Camera3D::setPosition(const QVector3D &position)
{
    m_position = position;
}

void Camera3D::setRotation(const QVector3D &EulerAngles)
{
    m_rotation = QQuaternion::fromEulerAngles(EulerAngles);
}

void Camera3D::setNear(float near)
{
    m_near = near;
}

void Camera3D::setFar(float far)
{
    m_far = far;
}

QPointF Camera3D::screenPointToNormScreenPoint(const QPoint &screenPoint, const QSize &screenSize) const
{
    const float xNorm = 2.0f * (screenPoint.x() + 0.5f) / static_cast<float>(screenSize.width()) - 1.0f;
    const float yNorm = (1.0f - (screenPoint.y() + 0.5f) / static_cast<float>(screenSize.height())) * 2.0f - 1.0f;
    return QPointF(xNorm, yNorm);
}

QVector3D Camera3D::position() const
{
    return m_position;
}

QVector3D Camera3D::EulerAngles() const
{
    return m_rotation.toEulerAngles();
}

QVector3D Camera3D::scale() const
{
    return QVector3D(1.0f, 1.0f, 1.0f);
}

QMatrix4x4 Camera3D::projectionMatrix(const int width, const int height)
{
    const float aspectRatio = width / static_cast<float>(height ? height : 1);

    QMatrix4x4 projectionMatrix;
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(m_fovY, aspectRatio, m_near, m_far);

    return projectionMatrix;
}

QMatrix4x4 Camera3D::viewMatrix()
{
    QMatrix4x4 viewMatrix;

    viewMatrix.setToIdentity();
    viewMatrix.translate(m_position);
    viewMatrix.rotate(m_rotation);
    viewMatrix.scale(1.0f);

    return viewMatrix;
}
