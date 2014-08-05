/* 
 * File:   customGraphicsView.h
 * Author: Adri
 *
 * Created on 5 janvier 2012, 15:16
 */

#ifndef CUSTOMGRAPHICSVIEW_H
#define	CUSTOMGRAPHICSVIEW_H

#include "fenetrePrincipale.h"
#include "QGraphicsView"
#include "QMouseEvent"
#include "QGraphicsScene"
#include "QGraphicsRectItem"
#include <iostream>
#include "outils.h"
#include "QBrush"
#include "QPen"
#include "QColor"
#include "QRect"
#include "QGraphicsSimpleTextItem"
#include <math.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qchar.h>
#include "traitement/ciseau.h"

class customGraphicsView :public QGraphicsView
{
public:
    
   customGraphicsView(QGraphicsScene* scene,fenetrePrincipale *fen,outils *tool);
   virtual ~customGraphicsView();
   void mouseMoveEvent(QMouseEvent *a);
   void mousePressEvent(QMouseEvent *a);
   void mouseReleaseEvent(QMouseEvent *a);
   QPushButton *boutonRogner;
   bool imageSelectionnee;
   int clicx,clicy;
   fenetrePrincipale *fenetre;
private:
    
    
    outils *tool;
    QGraphicsRectItem *rectitem_selection;
    QGraphicsRectItem *rectitem_taille_selection;
    
    QGraphicsSimpleTextItem *simpletext1;
    QGraphicsSimpleTextItem *simpletext2;
    
    QPen *pen_rec_sel;
    QPen *pen_rec_taille_sel;
    QColor *color_transp;
    QBrush *brush_rec_sel;
    QBrush *brush_rec_taille_sel;
    QRect *rec_sel;
    QRect *rec_taille_sel;
     int *r;
     int *v;
     int *b;
     int *a;
    QGraphicsScene *scene;

};

#endif	/* CUSTOMGRAPHICSVIEW_H */

