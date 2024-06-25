#include "glgrid.h"

GLGrid::GLGrid(float size, int segmentCount) :
    m_vertexBuffer(QOpenGLBuffer::VertexBuffer),
    m_indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    Q_ASSERT(segmentCount != 0);

    const float segmentSize = size / segmentCount;
    for (int segmentInd = 0; segmentInd < segmentCount * 2 + 1; ++ segmentInd) {
        m_vertex << QVector3D(-size + segmentInd * segmentSize, -0.8f, -size);
        m_vertex << QVector3D(-size + segmentInd * segmentSize, -0.8f, size);

        m_indices.push_back(m_indices.size());
        m_indices.push_back(m_indices.size());
    }

    for (int segmentInd = 0; segmentInd < segmentCount * 2 + 1; ++ segmentInd) {
        m_vertex << QVector3D(-size, -0.8f, -size + segmentInd * segmentSize);
        m_vertex << QVector3D(size, -0.8f, -size + segmentInd * segmentSize);

        m_indices.push_back(m_indices.size());
        m_indices.push_back(m_indices.size());
    }

    initialize();
}

GLGrid::~GLGrid()
{
    clear();
}

void GLGrid::draw(const View &view)
{
    m_shader->bind();

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();

    m_shader->setUniformValue("u_viewMatrix", view.viewMatrix);
    m_shader->setUniformValue("u_projectionMatrix", view.projectionMatrix);
    m_shader->setUniformValue("u_modelMatrix", modelMatrix);

    m_vertexBuffer.bind();

    int vertexLoc = m_shader->attributeLocation("a_vertex");
    m_shader->enableAttributeArray(vertexLoc);
    m_shader->setAttributeBuffer(vertexLoc, GL_FLOAT, 0, 3, 0);

    m_indexBuffer.bind();
    glLineWidth(1.0f);
    view.glFunction->glDrawElements(GL_LINES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    m_indexBuffer.release();

    m_shader->disableAttributeArray(vertexLoc);

    m_vertexBuffer.release();
    m_shader->release();
}

void GLGrid::clear()
{
    if (m_vertexBuffer.isCreated())
        m_vertexBuffer.destroy();

    if (m_indexBuffer.isCreated())
        m_indexBuffer.destroy();

    delete m_shader;
    m_shader = nullptr;

}

void GLGrid::initialize()
{
    m_vertexBuffer.create();
    m_vertexBuffer.bind();
    m_vertexBuffer.allocate(m_vertex.constData(), m_vertex.size() * sizeof(QVector3D));
    m_vertexBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(m_indices.constData(), m_indices.size() * sizeof(int));
    m_indexBuffer.release();

    m_shader = makeShaderProgramFromSourceFile(":/gridVertexShader.vsh", ":/gridFragmentShader.fsh");
}
