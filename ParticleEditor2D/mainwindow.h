#pragma once

#include <QMainWindow>
#include <QVariant>

class QHBoxLayout;
class QMenuBar;

class Camera3D;
class Viewport3D;
class ContextNavigation3D;

class NodeViewer;
class NodeEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *m_centralWidget;

    QHBoxLayout *m_centralLayout;

protected slots:
    void onNodeAdded(int nodeId);
    void onNodeRemoved(int nodeId);
    void onNodeSelected(int nodeId);

    void onNodeEditorWidgetChanged(const QString& name, QVariant param);

    void onSaveToFile();
    void onLoadFromFile();

private:
    QMenuBar* createTopMenu();
    Viewport3D *createViewport();
    void createNodeEditors();

    void connectSignalsAndSlots();

private:
    Camera3D *m_camera3D;
    Viewport3D *m_viewport3D;
    ContextNavigation3D *m_contextNavigation3D;

private:
    QHash<int, NodeEditor*> m_nodeEditors;

    int m_prevSelectedNodeId;

private:
    QString m_applicationName = "Particle Editor 2D (%1)";
    QString m_notNamedProjectName = "untitled";

private:
    NodeViewer *m_nodeViewer;
};
