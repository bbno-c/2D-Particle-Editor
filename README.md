# 2D Particle Editor

2D Particle Editor - небольшой редактор 2D частиц, написанный при помощи QtCreator.

Редактор партиклов построен на системе Node. 

Node - конкретное свойство системы партикла - время жизни, например. У каждой Node есть свой NodeEditor, для задания различных характеристик.

### Описание GUI

Разделено на 3 области (NodeViewer (1), Viewport (2), NodeEditor (3)).

NodeViewer - виджет для управления нодами (добавление, выделение, удаление).

### Описание Viewport

CTRL + Right Mouse Button - поворот камеры
CTRL + Middle Mouse Button - panning камеры

### Добавление новой функциональности

Для добавления новой Node необходимо написать NodeEditor для редактирования ее свойства.

Для добавления новой ноды необходимо добавить ее название и номер в *NodeContainer*.

```cpp
NodeContainer::AddNodeToContainer("Life Time", 1);
```

Имя и номер должны быть уникальными, иначе не получится добавить.

Для добавления своего NodeEditor необходимо:
<ol>
    <li>
        Добавить CustomEditor в папку NodeEditors;
    </li>
    <li>
        Добавить CustomEditor.pri в NodeEditors.pri;
    </li>
    <li>
        Переопределить resetEditor() (вызывается при удалении Node из NodeViewer), serialize и deserialize, а также передать сигнал об изменении параметра <b>emit nodeEditorWidgetChanged("Life Time", value);</b>
    </li>
    <li>
        В файле NodeFacroty.h добавить в switch-case блок;
    </li>
</ol>

Node и NodeEditors готовы к использованию.

```h
class CustomNodeEditor : public NodeEditor
{
    Q_OBJECT
public:
    explicit CustomNodeEditor(QWidget *parent = nullptr);
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;
};
```

```h
class CustomNodeEditor : public NodeEditor
{
    Q_OBJECT
public:
    explicit CustomNodeEditor(QWidget *parent = nullptr);
    void resetEditor() override;

public:
    QJsonObject serialize() const override;
    void deserialize(const QJsonObject& object) override;
};
```

```cpp
CustomNodeEditor::CustomNodeEditor(QWidget *parent) :
    NodeEditor(parent)
{
    m_floatEdit = new FloatEdit;
    m_floatEdit->setRange(0.0f, 5.0f);
    addItem(QString("Custom Param:"), m_floatEdit);

    QObject::connect(m_floatEdit, &FloatEdit::valueChanged, this, &NodeEditorLifeTime::onValueFloatEditChanged);
}

void CustomNodeEditor::resetEditor()
{
    m_floatEdit->setRange(0.0f, 5.0f);
    m_floatEdit->setValue(0.0f);
}

void CustomNodeEditor::onValueFloatEditChanged(float value)
{
    emit nodeEditorWidgetChanged("Custom Param", value);
}
```

```cpp
    #include "nodeeditortcustom.h"

    case 12:
        return new CustomNode(parent);
```

