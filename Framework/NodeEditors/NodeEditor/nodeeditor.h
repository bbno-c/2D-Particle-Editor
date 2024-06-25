#pragma once

#include <QWidget>
#include <QVariant>

#include "iserializable.h"

class QFormLayout;

class NodeEditor : public QWidget, public ISerializable
{
    Q_OBJECT
public:
    virtual ~NodeEditor() {}
    virtual void resetEditor() = 0;

signals:
    void nodeEditorWidgetChanged(const QString &paramName, QVariant param);

protected:
    explicit NodeEditor(QWidget *parent = nullptr);
    void addItem(QString name, QWidget *widget, Qt::AlignmentFlag widgetAlignment = Qt::AlignBaseline);

protected:
    QFormLayout *m_layout;

private:
    void insertParam(int row, QString paramTitle, QWidget *widget, Qt::AlignmentFlag widgetAlignment = Qt::AlignBaseline);
};
