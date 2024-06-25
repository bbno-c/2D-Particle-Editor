#pragma once

#include <QString>
#include <QVector2D>

namespace JsonFileUtils
{
    bool isSaveJsonObjectSuccessfully(const QJsonObject& jsonObject, const QString& filePath, QString &message);
    bool isReadJsonObjectFromFileSuccessfully(const QString& filePath, QJsonObject& jsonObject, QString &message);
}
