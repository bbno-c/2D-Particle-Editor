#pragma once

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include "camera3d.h"
#include "../GLObject/globject.h"
#include "../View/view.h"

class Viewport3D : public QOpenGLWidget
{
    Q_OBJECT
public:
    Viewport3D(Camera3D *camera, QWidget *parent = nullptr);
    ~Viewport3D();

    void addObject(GLObject *geom);
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    Camera3D *m_camera = nullptr;
    QMatrix4x4 m_projectionMatrix;

    View m_view;

    QVector<GLObject *> m_objects;
};
