#include "spinboxdelegate.h"

using namespace sbd;

SpinBoxDelegate::SpinBoxDelegate(QObject *parent) : QStyledItemDelegate(parent) {
    parent = nullptr;
}

QWidget * SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QSpinBox *spinBox = new QSpinBox(parent);
    spinBox->setMinimum(0);   // Set your desired minimum
    spinBox->setMaximum(100); // Set your desired maximum
    return spinBox;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
    spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QSpinBox *spinBox = static_cast<QSpinBox *>(editor);
    spinBox->interpretText();
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    editor->setGeometry(option.rect);
}
