#include "customqgraphicsproxywidget.h"
#include "iostream"
customQGraphicsProxyWidget::customQGraphicsProxyWidget(QLabel *label)
{
    this->label=label;
    selectionActivee=false;
    clicEnfonce=false;
    bordure=new customGraphicsRectItem(this);
    this->setWidget(this->label);

}
void customQGraphicsProxyWidget::MymousePressEvent(QMouseEvent* ev){

   // scene->setFocusItem(proxy);
        clicEnfonce=true;
        this->selectionActivee=true;
        autre->selectionActivee=false;

        if(selectionActivee){
            bordure->setRect(0,0,label->width(),label->height());
            autre->bordure->hide();
            bordure->show();
        }

}

void customQGraphicsProxyWidget::MymouseMoveEvent(int x,int y){
    if(clicEnfonce){

        this->setPos(x,y);

    }

}
void customQGraphicsProxyWidget::MymouseReleaseEvent(QMouseEvent *ev){

    clicEnfonce=false;

}
