#ifndef CUSTOMBUTTONDELEGATE_H
#define CUSTOMBUTTONDELEGATE_H

#pragma once
#include <QStyledItemDelegate>
#include <QPersistentModelIndex>

class HoverButtonDelegate : public QStyledItemDelegate {

Q_OBJECT
public:

    HoverButtonDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void setHoveredIndex(const QModelIndex& index){hovered = index;}

signals:
    void buttonClicked(const QModelIndex& index);

protected:
    bool editorEvent(QEvent* event,
                     QAbstractItemModel* model,
                     const QStyleOptionViewItem& option,
                     const QModelIndex& index) override;

    void paint(QPainter* painter,
               const QStyleOptionViewItem& option,
               const QModelIndex& index) const override;
private:
    QPersistentModelIndex hovered;

    QRect buttonRect(const QStyleOptionViewItem& option) const {
        // A small button area on the right side of the cell
        const int w = 20;
        const int h = option.rect.height() - 6;
        return QRect(option.rect.right() - w - 6,
                     option.rect.top() + 3,
                     w, h);
    }

};

#endif // CUSTOMBUTTONDELEGATE_H
