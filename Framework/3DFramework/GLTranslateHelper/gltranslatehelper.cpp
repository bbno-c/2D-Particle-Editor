#include "gltranslatehelper.h"
#include <cmath>

GLTranslateHelper::GLTranslateHelper(const Camera3D *camera) :
    m_lineVertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_arrowVertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_camera(camera)
{
    m_modelMatrixArrowX.setToIdentity();
    m_modelMatrixArrowX.translate(m_height, 0.0f, 0.0f);
    m_modelMatrixArrowX.rotate(QQuaternion::fromEulerAngles(QVector3D(0.0f, 90.0f, 0.0f)));
    m_modelMatrixArrowX.scale(0.25f);

    m_modelMatrixArrowY.setToIdentity();
    m_modelMatrixArrowY.translate(0.0f, m_height, 0.0f);
    m_modelMatrixArrowY.rotate(QQuaternion::fromEulerAngles(QVector3D(-90.0f, 0.0f, 0.0f)));
    m_modelMatrixArrowY.scale(0.25f);

    m_modelMatrixArrowZ.setToIdentity();
    m_modelMatrixArrowZ.translate(0.0f, 0.0f, m_height);
    m_modelMatrixArrowZ.scale(0.25f);

    m_selectedAxis.fill(false, 3);

    initialize(m_radius, m_height, m_numSegment, 1.0f);
}

GLTranslateHelper::~GLTranslateHelper()
{
}

void GLTranslateHelper::draw(const View &view)
{
    QVector4D colorX = m_selectedAxis[static_cast<int>(Axis::AxisX)] ? m_selectedColor : m_colorX;
    QVector4D colorY = m_selectedAxis[static_cast<int>(Axis::AxisY)] ? m_selectedColor : m_colorY;
    QVector4D colorZ = m_selectedAxis[static_cast<int>(Axis::AxisZ)] ? m_selectedColor : m_colorZ;

    QMatrix4x4 modelMatrixLine;
    modelMatrixLine.setToIdentity();

    m_transform.setToIdentity();
    m_transform.translate(m_translation);
    m_transform.rotate(QQuaternion::fromEulerAngles(m_EulerAngle));
    m_transform.scale(abs(m_camera->position().z()) * m_scaleFactor);

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);

    m_shader->bind();
    m_shader->setUniformValue("u_viewMatrix", view.viewMatrix);
    m_shader->setUniformValue("u_projectionMatrix", view.projectionMatrix);

    m_lineVertexBuffer.bind();

        int vertexLoc = m_shader->attributeLocation("a_vertex");
        m_shader->enableAttributeArray(vertexLoc);
        m_shader->setAttributeBuffer(vertexLoc, GL_FLOAT, 0, 3, 0);

        modelMatrixLine.scale(m_lineLength);
        m_shader->setUniformValue("u_modelMatrix", m_transform * modelMatrixLine);

        m_shader->setUniformValue("u_color", colorX);
        view.glFunction->glDrawArrays(GL_LINES, 0, 2);
        m_shader->setUniformValue("u_color", colorY);
        view.glFunction->glDrawArrays(GL_LINES, 2, 2);
        m_shader->setUniformValue("u_color", colorZ);
        view.glFunction->glDrawArrays(GL_LINES, 4, 2);
        m_shader->disableAttributeArray(vertexLoc);

    m_lineVertexBuffer.release();

    m_arrowVertexBuffer.bind();

        vertexLoc = m_shader->attributeLocation("a_vertex");
        m_shader->enableAttributeArray(vertexLoc);
        m_shader->setAttributeBuffer(vertexLoc, GL_FLOAT, 0, 3, 0);

        m_shader->setUniformValue("u_modelMatrix", m_transform * m_modelMatrixArrowX);
        m_shader->setUniformValue("u_color", colorX);
        view.glFunction->glDrawArrays(GL_TRIANGLES, 0, m_numSegment * 3);

        m_shader->setUniformValue("u_modelMatrix", m_transform * m_modelMatrixArrowY);
        m_shader->setUniformValue("u_color", colorY);
        view.glFunction->glDrawArrays(GL_TRIANGLES, 0, m_numSegment * 3);

        m_shader->setUniformValue("u_modelMatrix", m_transform * m_modelMatrixArrowZ);
        m_shader->setUniformValue("u_color", colorZ);
        view.glFunction->glDrawArrays(GL_TRIANGLES, 0, m_numSegment * 3);
        m_shader->disableAttributeArray(vertexLoc);

    m_arrowVertexBuffer.release();

    m_shader->release();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LINE_SMOOTH);
}

int GLTranslateHelper::pickAxis(const QVector3D &rayOrigin, const QVector3D &rayDirection)
{
    m_selectedAxis.fill(false, 3);
    float minDist = std::numeric_limits<float>::max();

    int nearestAxis = -1;

    for (int axisInd = 0; axisInd < 3; ++axisInd) {

        QVector3D axisStart = m_axisCoords[axisInd * 2];
        QVector3D axisEnd = m_axisCoords[axisInd * 2 + 1];

        float distance = distBetweenLine(axisStart, axisEnd, rayOrigin, rayDirection);
        if (distance < minDist) {
            nearestAxis = axisInd;
            minDist = distance;
        }
    }

    qDebug() << minDist;

    if (minDist > m_pixelError)
        return -1;

    m_selectedAxis[nearestAxis] = true;
    return nearestAxis;
}

void GLTranslateHelper::setTranslation(const QVector3D &translation)
{
    m_translation = translation;
}

void GLTranslateHelper::setRotation(const QVector3D &EulerAngle)
{
    m_EulerAngle = EulerAngle;
}

void GLTranslateHelper::initialize(const float &radius, const float &height, const int numSegment, const float &length)
{
    QVector<QVector3D> lineVertices = createBufferLineVertices(height);
    m_lineVertexBuffer.create();
    m_lineVertexBuffer.bind();
    m_lineVertexBuffer.allocate(lineVertices.constData(), lineVertices.size() * sizeof(QVector3D));
    m_lineVertexBuffer.release();

    QVector<QVector3D> arrowVertices = createBufferArrowVertices(radius, height, numSegment);
    m_arrowVertexBuffer.create();
    m_arrowVertexBuffer.bind();
    m_arrowVertexBuffer.allocate(arrowVertices.constData(), arrowVertices.size() * sizeof(QVector3D));
    m_arrowVertexBuffer.release();

    m_shader = makeShaderProgramFromSourceFile(":/translationVertexShader.vsh", ":/translationFragmentShader.fsh");
}

QVector<QVector3D> GLTranslateHelper::createBufferArrowVertices(const float &radius, const float &height, const int numSegment)
{
    QVector<QVector3D> vertices;

    QVector3D pick = QVector3D(0.0f, 0.0f, height);
    const float angleStep =  2 * M_PI / (float)(numSegment);

    for (int segmentInd = 0; segmentInd < numSegment; ++segmentInd) {
        vertices.push_back(QVector3D(radius * cos(segmentInd * angleStep), radius * sin(segmentInd * angleStep), 0.0f));
        vertices.push_back(QVector3D(radius * cos((segmentInd + 1) * angleStep), radius * sin((segmentInd + 1) * angleStep), 0.0f));
        vertices.push_back(pick);
    }

    return vertices;
}

QVector<QVector3D> GLTranslateHelper::createBufferLineVertices(const float &length)
{
    QVector<QVector3D> lineVertices;

    lineVertices.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    lineVertices.push_back(QVector3D(length, 0.0f, 0.0f));

    lineVertices.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    lineVertices.push_back(QVector3D(0.0f, length, 0.0f));

    lineVertices.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    lineVertices.push_back(QVector3D(0.0f, 0.0f, length));

    m_axisCoords = lineVertices;

    return lineVertices;
}

float GLTranslateHelper::distBetweenLine(const QVector3D &L1P0, const QVector3D &L1P1, const QVector3D &L2P0, const QVector3D &L2P1, const float &eps)
{
    QVector3D u = L1P1 - L1P0;
    QVector3D v = L2P1 - L2P0;
    QVector3D w = L1P0 - L2P0;

    float a = QVector3D::dotProduct(u,u);
    float b = QVector3D::dotProduct(u,v);
    float c = QVector3D::dotProduct(v,v);
    float d = QVector3D::dotProduct(u,w);
    float e = QVector3D::dotProduct(v,w);
    float D = a*c - b*b;
    float sc, tc;

    if (D < eps) {          // the lines are almost parallel
        sc = 0.0;
        tc = (b>c ? d/b : e/c);    // use the largest denominator
    } else {
        sc = (b*e - c*d) / D;
        tc = (a*e - b*d) / D;
    }

    QVector3D dP = w + (sc * u) - (tc * v);
    return std::sqrt(QVector3D::dotProduct(dP,dP));
}
