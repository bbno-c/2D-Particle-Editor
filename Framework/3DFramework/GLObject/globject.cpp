#include "globject.h"

GLObject::~GLObject()
{
}

QOpenGLShaderProgram *GLObject::makeShaderProgramFromSourceFile(const QString &vertexShaderSourceFile, const QString &fragmentShaderSourceFile)
{
    QOpenGLShaderProgram *shaderProgram = new QOpenGLShaderProgram();

    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderSourceFile)) {
        qCritical() << "Can't link shader";
        delete shaderProgram;
        shaderProgram = nullptr;
        return nullptr;
    }

    if (!shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderSourceFile)) {
        qCritical() << "Can't link shader";
        delete shaderProgram;
        shaderProgram = nullptr;
        return nullptr;
    }

    return shaderProgram;
}

QOpenGLShaderProgram *GLObject::makeShaderProgramFromSourceCode(const QString &vertexShaderSourceCode, const QString &fragmentShaderSourceCode)
{
    QOpenGLShaderProgram *shaderProgram = new QOpenGLShaderProgram();

    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCode)) {
        qCritical() << "Can't create shader";
        delete shaderProgram;
        shaderProgram = nullptr;
        return nullptr;
    }

    if (!shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCode)) {
        qCritical() << "Can't create shader";
        delete shaderProgram;
        shaderProgram = nullptr;
        return nullptr;
    }

    return shaderProgram;
}

bool GLObject::isVisible() const
{
    return m_isVisible;
}

void GLObject::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
}
