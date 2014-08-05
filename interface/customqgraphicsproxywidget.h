#ifndef CUSTOMQGRAPHICSPROXYWIDGET_H
#define CUSTOMQGRAPHICSPROXYWIDGET_H
#include <QtGui>
#include "customgraphicsrectitem.h"

class customQGraphicsProxyWidget : public QGraphicsProxyWidget
{
public:
    customQGraphicsProxyWidget(QLabel *label);
    bool selectionActivee;
    customQGraphicsProxyWidget *autre;
    void MymousePressEvent(QMouseEvent* e);
    void MymouseMoveEvent(int x,int y);
    void MymouseReleaseEvent(QMouseEvent *ev);
    customGraphicsRectItem *bordure;
    QLabel *label;
private:
    bool clicEnfonce;



};

#endif // CUSTOMQGRAPHICSPROXYWIDGET_H
