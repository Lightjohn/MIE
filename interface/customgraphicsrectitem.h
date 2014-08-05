#ifndef CUSTOMGRAPHICSRECTITEM_H
#define CUSTOMGRAPHICSRECTITEM_H

#include <QGraphicsRectItem>
#include <QColor>
#include <QBrush>
#include <QPen>
#include <QPainter>
class customGraphicsRectItem : public QGraphicsRectItem
{
public:
    customGraphicsRectItem(QGraphicsItem *parent);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QColor *fontColor;
    QBrush *brush;
    QPen *border;
};

#endif // CUSTOMGRAPHICSRECTITEM_H
