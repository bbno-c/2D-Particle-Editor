#include "viewport3d.h"
#include <QPainter>

Viewport3D::Viewport3D(Camera3D *camera, QWidget *parent) :
    m_camera(camera),
    m_projectionMatrix(QMatrix4x4()),
    QOpenGLWidget(parent)
{
}

Viewport3D::~Viewport3D()
{
    for (int i = 0; i < m_objects.size(); ++i) {
            delete m_objects[i];
            m_objects[i] = nullptr;
    }

    m_objects.clear();
}

void Viewport3D::addObject(GLObject *geom)
{
    m_objects.push_back(geom);
}

void Viewport3D::initializeGL()
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

    glEnable(GL_DEPTH_TEST);
}

void Viewport3D::resizeGL(int w, int h)
{
    if (m_camera)
        m_projectionMatrix = m_camera->projectionMatrix(w, h);
}

void Viewport3D::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!m_camera)
        return;

    m_view.glFunction = context()->functions();
    m_view.projectionMatrix = m_projectionMatrix;
    m_view.viewMatrix = m_camera->viewMatrix();
    m_view.viewportSize = QSize(width(), height());

    for (int i = 0; i < m_objects.size(); ++i)
        if (m_objects[i] && m_objects[i]->isVisible())
            m_objects[i]->draw(m_view);
}
