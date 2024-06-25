#pragma once

#include <QDialog>

class QComboBox;
class CurveEditor;

class CurveEditorDialog : public QDialog
{
    Q_OBJECT
public:
    CurveEditorDialog(QWidget *parent = nullptr);

    void reset();

protected slots:
    void onTypeCurveChanged(int curveType);

private:
    void removeQuestionButton();

private:
    QComboBox *m_easingCurveType;
    CurveEditor *m_curveEditor;
};
