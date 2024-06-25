#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <cmath>

class Camera3D
{
public:
    Camera3D() = default;
    Camera3D(const QVector3D &position, float fovY);
    Camera3D(const QVector3D &position, const QVector3D &EulerAngles, float fovY);

    void setFovY(float fovY);
    void setPosition(const QVector3D &position);
    void setRotation(const QVector3D &EulerAngles);
    void setNear(float near);
    void setFar(float far);

    QPointF screenPointToNormScreenPoint(const QPoint &screenPoint, const QSize &screenSize) const;

    QVector3D position() const;
    QVector3D EulerAngles() const;
    QVector3D scale() const;

    QMatrix4x4 projectionMatrix(int width, int height);
    QMatrix4x4 viewMatrix();

private:
    QVector3D m_position;
    QQuaternion m_rotation;
    float m_fovY = 45.f;

    float m_near = 1e-3f;
    float m_far = 1e4f;
};
