#pragma once

#include <QObject>
#include <QEvent>
#include <QWheelEvent>
#include <QKeyEvent>

#include "viewport3d.h"
#include "camera3d.h"

class ContextNavigation3D : public QObject
{
    Q_OBJECT
public:
    ContextNavigation3D(Viewport3D *viewport, Camera3D *camera, QObject *parent = nullptr);
    ~ContextNavigation3D();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void cameraZoom(int delta);
    void cameraPan(const QVector2D &mousePosition);
    void cameraRotation(const QVector2D &mousePosition);

private:
    Viewport3D *m_viewport;
    Camera3D *m_camera;

    QVector2D m_startPosition;
    QVector2D m_currentPosition;

    QQuaternion m_rotation;
    QQuaternion m_rotationX;
    QQuaternion m_rotationY;

    const float m_zoomFactorZ;
    const float m_speedPan;
    float m_currentZoomZ;
};
