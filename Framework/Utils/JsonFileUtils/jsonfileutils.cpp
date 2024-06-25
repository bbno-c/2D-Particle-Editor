#include "jsonfileutils.h"

#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

bool JsonFileUtils::isSaveJsonObjectSuccessfully(const QJsonObject& jsonObject, const QString& filePath, QString &message)
{
    QJsonDocument jsonDoc(jsonObject);
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly)) {
        message = QString("Failed to open file for writing: %1").arg(filePath);
        return false;
    }

    file.write(jsonDoc.toJson());
    file.close();

    message = QString("JSON object saved to file: %1").arg(filePath);
    return true;
}

bool JsonFileUtils::isReadJsonObjectFromFileSuccessfully(const QString& filePath, QJsonObject& jsonObject, QString &message)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly)) {
        message = QString("Failed to open file for reading: %1").arg(filePath);
        jsonObject = QJsonObject();
        return false;
    }

    QByteArray jsonData = file.readAll();

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);

    if (jsonDoc.isNull()) {
        message = QString("Failed to parse JSON data: %1").arg(error.errorString());
        jsonObject = QJsonObject();
        return false;
    }

    if (!jsonDoc.isObject()) {
        message = QString("JSON data is not an object");
        jsonObject = QJsonObject();
        return false;
    }

    message = QString("JSON object read from file: %1").arg(filePath);
    jsonObject = jsonDoc.object();
    return true;
}
