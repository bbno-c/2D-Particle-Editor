#pragma once

#include <QOpenGLShaderProgram>
#include "../View/view.h"

class GLObject
{
public:
    explicit GLObject() = default;
    ~GLObject();

    virtual void draw(const View &view) = 0;

    static QOpenGLShaderProgram *makeShaderProgramFromSourceFile(const QString &vertexShaderSourceFile, const QString &fragmentShaderSourceFile);
    static QOpenGLShaderProgram *makeShaderProgramFromSourceCode(const QString &vertexShaderSourceCode, const QString &fragmentShaderSourceCode);

    bool isVisible() const;
    void setIsVisible(bool isVisible);

protected:
    bool m_isVisible = true;
};
