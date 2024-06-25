#include "curveeditordialog.h"

#include <QPaintEvent>
#include <QPainter>
#include <QEasingCurve>
#include <QComboBox>

#include <QHBoxLayout>

#include "curveeditor.h"

CurveEditorDialog::CurveEditorDialog(QWidget *parent) :
    QDialog(parent)
{
    setFixedSize(600, 500);
    setWindowTitle("Easing Curve Editor");

    removeQuestionButton();

    m_easingCurveType = new QComboBox();
    m_easingCurveType->addItem("Linear");
    m_easingCurveType->addItem("InQuad");
    m_easingCurveType->addItem("OutQuad");

    m_curveEditor = new CurveEditor(QEasingCurve::Type::Linear, 50);

    QHBoxLayout *centralLayout = new QHBoxLayout();
    centralLayout->addWidget(m_easingCurveType);
    centralLayout->addWidget(m_curveEditor);
    setLayout(centralLayout);

    QObject::connect(m_easingCurveType,SIGNAL(currentIndexChanged(int)),this,SLOT(onTypeCurveChanged(int)));
}

void CurveEditorDialog::reset()
{
    m_easingCurveType->setCurrentIndex(0);
}

void CurveEditorDialog::onTypeCurveChanged(int curveType)
{
    m_curveEditor->setCurveType(static_cast<QEasingCurve::Type>(curveType));
}

void CurveEditorDialog::removeQuestionButton()
{
    // Remove "Question" button
    Qt::WindowFlags flags = windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    setWindowFlags(flags);
}
