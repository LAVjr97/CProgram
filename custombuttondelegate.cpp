#include "custombuttondelegate.h"

#include <QApplication>
#include <QMouseEvent>
#include <QStyle>

void HoverButtonDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    // Paint normal cell (text, selection, etc.)
    QStyledItemDelegate::paint(painter, option, index);

    // Only draw the "button" if this cell is hovered
    if (hovered.isValid() && hovered == index) {
        QStyleOptionButton btn;
        btn.rect = buttonRect(option);
        btn.text = "Action"; // or "Edit"/"Open"/"..."
        btn.state = QStyle::State_Enabled | QStyle::State_Raised;

        QApplication::style()->drawControl(QStyle::CE_PushButton, &btn, painter);
    }
}

bool HoverButtonDelegate::editorEvent(QEvent* event, QAbstractItemModel*, const QStyleOptionViewItem& option, const QModelIndex& index)
{
    // Only react on mouse release inside the button rect
    if (event->type() == QEvent::MouseButtonRelease) {
        auto* me = static_cast<QMouseEvent*>(event);
        if (buttonRect(option).contains(me->pos())) {
            emit buttonClicked(index);
            return true; // handled
        }
    }
    return false;
}
