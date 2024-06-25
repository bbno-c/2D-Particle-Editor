#include "mainwindow.h"

#include <QHBoxLayout>
#include <QMenuBar>
#include <QJsonDocument>

#include <QMessageBox>
#include <QFileDialog>

#include "jsonfileutils.h"
#include "pathfileutils.h"

#include "camera3d.h"
#include "viewport3d.h"
#include "contextnavigation3d.h"

#include "nodeviewer.h"
#include "nodeeditorfactory.h"

#include "glgrid.h"
#include "gltranslatehelper.h"

#include "nodecontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : m_prevSelectedNodeId(-1),
    QMainWindow(parent)
{
    setWindowTitle(m_applicationName.arg(m_notNamedProjectName));

    // Node Container
    NodeContainer::AddNodeToContainer("Life Time", 1);
    NodeContainer::AddNodeToContainer("Emittions Rate", 2);
    NodeContainer::AddNodeToContainer("Start Transformation", 3);
    NodeContainer::AddNodeToContainer("Max Prticles", 4);
    NodeContainer::AddNodeToContainer("Emitter Shape", 5);
    NodeContainer::AddNodeToContainer("Force By Time", 6);
    NodeContainer::AddNodeToContainer("Particle Speed", 7);
    NodeContainer::AddNodeToContainer("Particle Rotation Speed", 8);
    NodeContainer::AddNodeToContainer("Particle Size", 9);
    NodeContainer::AddNodeToContainer("Particle Color", 10);
    NodeContainer::AddNodeToContainer("Particle Trace", 11);

    // Central Widget
    m_centralWidget = new QWidget();
    setCentralWidget(m_centralWidget);

    // Central Layout
    m_centralLayout = new QHBoxLayout();
    m_centralWidget->setLayout(m_centralLayout);

    // Node Viewer
    m_nodeViewer = new NodeViewer(NodeContainer::nodesAndIds());
    m_centralLayout->addWidget(m_nodeViewer);

    // 3D Framework
    m_centralLayout->addWidget(createViewport(), 1);

    // Node Editors
    createNodeEditors();

    // Top Menu
    setMenuBar(createTopMenu());

    // Signals And Slots
    connectSignalsAndSlots();
}

MainWindow::~MainWindow()
{
    delete m_camera3D;
    m_camera3D = nullptr;

    delete m_contextNavigation3D;
    m_contextNavigation3D = nullptr;
}

void MainWindow::onNodeAdded(int nodeId)
{
    qDebug() << "Node added:" << nodeId;
}

void MainWindow::onNodeRemoved(int nodeId)
{
    qDebug() << "Node removed:" << nodeId;

    if (m_nodeEditors.contains(nodeId) && m_nodeEditors[nodeId])
        m_nodeEditors[nodeId]->resetEditor();
}

void MainWindow::onNodeSelected(int nodeId)
{
    if ((nodeId == -1) && (m_prevSelectedNodeId != -1)) {
        m_nodeEditors[m_prevSelectedNodeId]->setVisible(false);
        m_prevSelectedNodeId = -1;
        return;
    }

    if (m_nodeEditors.contains(nodeId) && m_nodeEditors[nodeId] && (m_prevSelectedNodeId != nodeId))
        m_nodeEditors[nodeId]->setVisible(true);

    if ((m_prevSelectedNodeId != -1) && (m_prevSelectedNodeId != nodeId))
        m_nodeEditors[m_prevSelectedNodeId]->setVisible(false);

    m_prevSelectedNodeId = nodeId;
}

void MainWindow::onNodeEditorWidgetChanged(const QString& name, QVariant param)
{
    qDebug() << name << param;
}

QMenuBar* MainWindow::createTopMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);

    QMenu *fileMenu = menuBar->addMenu(tr("File"));

    QAction *saveAction = new QAction(tr("Save"), this);
    saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    fileMenu->addAction(saveAction);

    QAction *loadAction = new QAction(tr("Load"), this);
    loadAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    fileMenu->addAction(loadAction);

    QMenu *aboutMenu = menuBar->addMenu(tr("Window"));
    QAction *aboutAction = new QAction(tr("About"), this);
    aboutMenu->addAction(aboutAction);

    QObject::connect(saveAction, &QAction::triggered, this, &MainWindow::onSaveToFile);
    QObject::connect(loadAction, &QAction::triggered, this, &MainWindow::onLoadFromFile);

    return menuBar;
}

Viewport3D* MainWindow::createViewport()
{
    m_camera3D = new Camera3D(QVector3D(0.0f, 0.0f, -50.0f), 45.0f);
    m_camera3D->setRotation(QVector3D(0.5f, -90.0f, -24.0f));

    m_viewport3D = new Viewport3D(m_camera3D);
    m_viewport3D->addObject(new GLGrid(20, 5.0f));
    m_viewport3D->addObject(new GLTranslateHelper(m_camera3D));

    m_contextNavigation3D = new ContextNavigation3D(m_viewport3D, m_camera3D);
    return m_viewport3D;
}

void MainWindow::createNodeEditors()
{
    foreach(const QString &name, NodeContainer::nodesAndIds().keys())
    {
        const int nodeId = NodeContainer::nodesAndIds()[name];

        NodeEditor *m_editor = NodeEditorFactory::create(nodeId);

        if (m_editor) {
            m_nodeEditors.insert(nodeId, m_editor);
            m_centralLayout->addWidget(m_editor);
            m_editor->setVisible(false);
        }
    }
}

void MainWindow::connectSignalsAndSlots()
{
    QObject::connect(m_nodeViewer, &NodeViewer::nodeAdded, this, &MainWindow::onNodeAdded);
    QObject::connect(m_nodeViewer, &NodeViewer::nodeRemoved, this, &MainWindow::onNodeRemoved);
    QObject::connect(m_nodeViewer, &NodeViewer::nodeSelected, this, &MainWindow::onNodeSelected);

    for (auto it = m_nodeEditors.begin(); it != m_nodeEditors.end(); ++it)
        QObject::connect(it.value(), &NodeEditor::nodeEditorWidgetChanged, this, &MainWindow::onNodeEditorWidgetChanged);
}

void MainWindow::onSaveToFile()
{
    QString filePath = PathFileUtils::filePathDialog("Save file", QFileDialog::AcceptSave, "JSON Files (*.json)", QString("%1.json").arg(m_notNamedProjectName));

    if (filePath.isEmpty())
        return;

    setWindowTitle(m_applicationName.arg(filePath));

    QJsonObject nodeViewerStates = m_nodeViewer->serialize();

    QJsonObject nodeEditorsStates;
    for (auto it = m_nodeEditors.begin(); it != m_nodeEditors.end(); ++it)
        nodeEditorsStates[QString::number(it.key())] = it.value()->serialize();

    QJsonObject resultObject;
    resultObject["node_viewer"] = nodeViewerStates;
    resultObject["node_editors"] = nodeEditorsStates;

    QString message;
    bool isSaveSuccessfully = JsonFileUtils::isSaveJsonObjectSuccessfully(resultObject, filePath, message);

    QMessageBox::information(nullptr, isSaveSuccessfully ? "Info" : "Error", message);
}

void MainWindow::onLoadFromFile()
{
    QString filePath = PathFileUtils::filePathDialog("Save file", QFileDialog::AcceptOpen, "JSON Files (*.json)");

    if (filePath.isEmpty())
        return;

    QJsonObject loadedJsonObject;
    QString message;
    bool isReadSuccessfully = JsonFileUtils::isReadJsonObjectFromFileSuccessfully(filePath, loadedJsonObject, message);

    QMessageBox::information(nullptr, isReadSuccessfully ? "Info" : "Error", message);

    QJsonObject nodeViewerStates = loadedJsonObject["node_viewer"].toObject();
    QJsonObject nodeEditorsStates = loadedJsonObject["node_editors"].toObject();

    if (nodeViewerStates.isEmpty() || nodeEditorsStates.isEmpty()) {
        QMessageBox::warning(nullptr, "Error", "Wrong project format!");
        return;
    }

    m_nodeViewer->deserialize(nodeViewerStates);

    for (auto it = nodeEditorsStates.constBegin(); it != nodeEditorsStates.constEnd(); ++it)
    {
        int nodeId = it.key().toInt();
        QJsonObject object = it.value().toObject();

        if (m_nodeEditors.contains(nodeId) && m_nodeEditors[nodeId])
            m_nodeEditors[nodeId]->deserialize(object);
    }

    setWindowTitle(m_applicationName.arg(filePath));
}
