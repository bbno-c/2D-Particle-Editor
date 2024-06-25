#include "mainwindow.h"

#include <QApplication>
#include <QOffscreenSurface>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

    QOpenGLContext *glContextGlobal = QOpenGLContext::globalShareContext();

    QOffscreenSurface *glSurface = new QOffscreenSurface();
    glSurface->create();
    QOpenGLContext *glContext = new QOpenGLContext();
    glContext->setShareContext(glContextGlobal);
    glContext->create();
    glContext->makeCurrent(glSurface);

    MainWindow w;
    w.show();
    w.resize(1280, 720);

    return a.exec();
}
