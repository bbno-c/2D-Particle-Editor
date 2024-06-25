#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "globject.h"
#include "camera3d.h"

class GLTranslateHelper : public GLObject
{
public:
    enum class Axis {AxisX = 0, AxisY = 1, AxisZ = 2};
    explicit GLTranslateHelper(const Camera3D *camera);
    ~GLTranslateHelper();

    void draw(const View &view) override;

    int pickAxis(const QVector3D &rayOrigin, const QVector3D &rayDirection);

    void setTranslation(const QVector3D &translation);
    void setRotation(const QVector3D &EulerAngle);

private:
    QOpenGLShaderProgram *m_shader = nullptr;
    QOpenGLBuffer m_lineVertexBuffer;
    QOpenGLBuffer m_arrowVertexBuffer;

    const QVector4D m_colorX = QVector4D(1.0f, 0.0f, 0.0f, 1.0f);
    const QVector4D m_colorY = QVector4D(0.0f, 1.0f, 0.0f, 1.0f);
    const QVector4D m_colorZ = QVector4D(0.0f, 0.0f, 1.0f, 1.0f);
    const QVector4D m_selectedColor = QVector4D(0.0f, 1.0f, 1.0f, 1.0f);

    float m_scaleFactor = 0.5f;
    float m_radius = 0.05f;
    float m_height = 0.16f;
    int m_numSegment = 20;
    float m_lineLength = 1.0f;
    float m_pixelError = 0.1f;

    QMatrix4x4 m_modelMatrixArrowX;
    QMatrix4x4 m_modelMatrixArrowY;
    QMatrix4x4 m_modelMatrixArrowZ;

    QMatrix4x4 m_transform;
    QVector3D m_translation;
    QVector3D m_EulerAngle;

    QVector<bool> m_selectedAxis;
    QVector<QVector3D> m_axisCoords;

    const Camera3D *m_camera = nullptr;

    void initialize(const float &radius, const float &height, const int numSegment, const float &length);

    QVector<QVector3D> createBufferArrowVertices(const float &radius, const float &height, const int numSegment);
    QVector<QVector3D> createBufferLineVertices(const float &length);

    // Utils
    float distBetweenLine(const QVector3D &L1P0, const QVector3D &L1P1, const QVector3D &L2P0, const QVector3D &L2P1, const float &eps = 1e-5f);
};
