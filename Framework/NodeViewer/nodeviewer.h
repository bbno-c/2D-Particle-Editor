#pragma once

#include <QWidget>
#include "iserializable.h"

class QListView;
class QStringListModel;
class QMouseEvent;
class QItemSelection;

class NodeViewer : public QWidget, public ISerializable
{
    Q_OBJECT
public:
    NodeViewer(QHash<QString, int> nodesAndIds, QWidget *parent = nullptr);

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;

signals:
    void nodeAdded(int nodeId);
    void nodeRemoved(int nodeId);
    void nodeSelected(int nodeId);

private slots:
    void onShowContextMenu(const QPoint &pos);
    void onRemoveNode();
    void onSelectedNodeChanged(const QModelIndex &index);

private:
    QListView *m_listView;
    QStringListModel *m_model;

    QStringList m_nodeNames;

    QHash<QString, int> m_nodesAndIds;
};
