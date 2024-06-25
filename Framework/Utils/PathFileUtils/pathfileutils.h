#pragma once

#include <QString>
#include <QFileDialog>

namespace PathFileUtils
{
    QString filePathDialog(const QString &caption, QFileDialog::AcceptMode acceptMode, const QString &fileFilter, const QString &defaultFileName = QString());
}
