#include "nodecontainer.h"

QHash<QString, int> NodeContainer::m_nodesAndIds;

bool NodeContainer::AddNodeToContainer(const QString &nodeName, int nodeId)
{
    if (m_nodesAndIds.keys().contains(nodeName))
        return false;

    if (m_nodesAndIds.values().contains(nodeId))
        return false;

    m_nodesAndIds.insert(nodeName, nodeId);
    return true;
}

const QHash<QString, int>& NodeContainer::nodesAndIds()
{
    return m_nodesAndIds;
}
