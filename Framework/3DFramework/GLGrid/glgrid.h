#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "globject.h"

class GLGrid : public GLObject
{
public:
    GLGrid(float size, int segmentCount);
    ~GLGrid();

    void draw(const View &view) override;

private:
    void clear();
    void initialize();

    QOpenGLShaderProgram *m_shader = nullptr;

    QOpenGLBuffer m_vertexBuffer;
    QOpenGLBuffer m_indexBuffer;

    QVector<QVector3D> m_vertex;
    QVector<int> m_indices;
};
