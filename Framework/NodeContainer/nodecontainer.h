#pragma once

#include <QHash>
#include <QString>

class NodeContainer
{
public:
    NodeContainer() = delete;

    static bool AddNodeToContainer(const QString &nodeName, int nodeId);
    static const QHash<QString, int>& nodesAndIds();

private:
    static QHash<QString, int> m_nodesAndIds;
};
