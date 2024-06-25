#include "nodeeditor.h"

#include <QLabel>
#include <QFormLayout>

NodeEditor::NodeEditor(QWidget *parent) :
    QWidget(parent),
    m_layout(nullptr)
{
    m_layout = new QFormLayout();
    m_layout->setLabelAlignment(Qt::AlignRight);
    m_layout->setHorizontalSpacing(12);
    m_layout->setMargin(0);

    setLayout(m_layout);
}

void NodeEditor::addItem(QString name, QWidget *widget, Qt::AlignmentFlag widgetAlignment)
{
    insertParam(m_layout->rowCount(), name, widget, widgetAlignment);
}

void NodeEditor::insertParam(int row, QString paramTitle, QWidget *widget, Qt::AlignmentFlag widgetAlignment)
{
    QLabel *label = new QLabel(paramTitle);
    label->setAlignment(Qt::AlignRight | Qt::AlignCenter);

    m_layout->insertRow(row, label, widget);
    m_layout->setAlignment(widget, widgetAlignment);
}
