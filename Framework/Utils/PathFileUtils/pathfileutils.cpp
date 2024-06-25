#include "pathfileutils.h"

QString PathFileUtils::filePathDialog(const QString &caption, QFileDialog::AcceptMode acceptMode, const QString &fileFilter, const QString &defaultFileName)
{
    QFileDialog dialog(nullptr, caption);
    dialog.setAcceptMode(acceptMode);
    dialog.selectFile(defaultFileName);
    dialog.setNameFilter(fileFilter);

    if (!dialog.exec())
        return QString();

    return dialog.selectedFiles().at(0);
}
