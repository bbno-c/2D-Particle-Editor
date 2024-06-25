#pragma once

#include <QJsonObject>

class ISerializable {
public:
    virtual ~ISerializable() {}
    virtual QJsonObject serialize() const = 0;
    virtual void deserialize(const QJsonObject& object) = 0;
};
