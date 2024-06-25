#include "stringutils.h"

#include <QStringList>

#include <QDebug>

QString StringUtils::QVector2DToQString(const QVector2D &vector)
{
    return QString("%1, %2").arg(QString::number(vector.x())).arg(QString::number(vector.y()));
}

QVector2D StringUtils::QStringToQVector2D(const QString &string)
{
    if (string.isEmpty())
        return QVector2D();

    QStringList parts = string.split(',', QString::SkipEmptyParts);

    if (parts.size() != 2)
        return QVector2D();

    bool okX, okY;
    float x = parts[0].trimmed().toFloat(&okX);
    float y = parts[1].trimmed().toFloat(&okY);

    if (!okX || !okY)
        return QVector2D();

    return QVector2D(x, y);
}
