#include "customgraphicsrectitem.h"

customGraphicsRectItem::customGraphicsRectItem(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    fontColor=new QColor(128,128,128,0);
    brush=new QBrush((const QColor&)*fontColor,Qt::SolidPattern);
    border=new QPen(Qt::DashDotLine);
    border->setWidth(3);
}
   void customGraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

       painter->setPen((const QPen&)*border);
       painter->setBrush((const QBrush&)*brush);
       painter->drawRect(rect());


   }
