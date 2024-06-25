#pragma once

#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QSize>

struct View
{
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;

    QOpenGLFunctions *glFunction;

    QSize viewportSize;
};
