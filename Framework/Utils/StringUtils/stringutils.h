#pragma once

#include <QString>
#include <QVector2D>

namespace StringUtils
{
    QString QVector2DToQString(const QVector2D &vector);
    QVector2D QStringToQVector2D(const QString &string);
}
