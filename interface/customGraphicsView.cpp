/* 
 * File:   customGraphicsView.cpp
 * Author: Adri
 * 
 * Created on 5 janvier 2012, 15:16
 */


#include "customGraphicsView.h"


customGraphicsView::customGraphicsView(QGraphicsScene* sc,fenetrePrincipale *fen, outils *tool) : QGraphicsView(sc)
{
    this->tool = tool;
    this->fenetre =fen;
    rectitem_selection = new QGraphicsRectItem();
    rectitem_taille_selection = new QGraphicsRectItem();
    simpletext1 = new  QGraphicsSimpleTextItem(); 
    simpletext2 = new  QGraphicsSimpleTextItem();
    pen_rec_sel = new QPen(Qt::white,1, Qt::SolidLine);
    color_transp = new QColor(255,255,255,128);
    brush_rec_sel = new QBrush(*color_transp);
    rec_sel = new QRect();
    rec_taille_sel = new QRect();
    pen_rec_taille_sel = new QPen(Qt::gray,3, Qt::SolidLine);
    brush_rec_taille_sel = new QBrush(Qt::white);
    
    tool->rectitem_selection = this->rectitem_selection;
    tool->rectitem_taille_selection = this->rectitem_taille_selection;
    tool->simpletext1 = this->simpletext1;
    tool->simpletext2 = this->simpletext2;
    scene=sc;
    imageSelectionnee=false;
    clicx=0;
    clicy=0;
    
}   


void customGraphicsView::mouseMoveEvent(QMouseEvent *event)
{ QPointF scenefg=tool->fg->pos();

    int x = mapToScene(event->pos()).x()/tool->getZoomFactor();
    int y = mapToScene(event->pos()).y()/tool->getZoomFactor();


    if(tool->checkBoxSelection){
        if(imageSelectionnee){
            int decalx=x-tool->fg->scenePos().x();
            int decaly=y-tool->fg->scenePos().y();



            tool->fg->MymouseMoveEvent(tool->fg->pos().x()+(x-clicx),tool->fg->pos().y()+(y-clicy));
            clicx=x;
            clicy=y;


         }

    }else{
      x = mapToScene(event->pos()).x();
      y = mapToScene(event->pos()).y();
      tool->nombre_appel_move++;
      bool bool_in_im = true;

     //si on est en dehors de l'image
     QImage *im;
     if(tool->getZoomFactor()!=1.0){
         im=tool->getImageZoomee();

     }else{
         im=tool->getImage();
     }
     if(x < 0 || y < 0 || x > im->width() || y > im->height())
        {bool_in_im = false;}


    // si on est dans l'image
   if(bool_in_im){
         QString s;
     
         r = new int;
         v = new int;
         b = new int;
         a = new int;
         

         QColor color;
         color.setRgb(im->pixel(abs(x), abs(y)));
         color.getRgb(r, v, b, a);
        //tool->getPixel(x,y,r,v,b,a);
         //coordonnee sur X
         s.append("X : ");
         s.append(QString::number(x));
         s.append("   ");
         tool->lab_x->setText(s);
         
         //coordonnee sur Y
         s = "Y : ";
         s.append(QString::number(y));
         s.append("   ");
         tool->lab_y->setText(s);
         if(tool->utiliserRGB){
            //composante rouge
            s = "<font color=\"#FF0000\">R : ";
            s.append(QString::number(*r));
            s.append("   </font>");
            tool->lab_r->setText(s);

            //composante verte
            s = "<font color=\"#419F2E\">V : ";
            s.append(QString::number(*v));
            s.append("   </font>");
            tool->lab_v->setText(s);

            //composante bleue
            s = "<font color=\"#0000FF\">B : ";
            s.append(QString::number(*b));
            s.append("   </font>");
            tool->lab_b->setText(s);
            
            //milieu
     
            QColor col(*r,*v,*b,*a);
            QBrush br(col);
            QPen p(col,1, Qt::SolidLine);
            tool->scene_ap->addRect((qreal)1,(qreal)1,(qreal)25,(qreal)25,p,br);
            
         }else{
            QColor col(*r,*v,*b,*a);
            QBrush br(col);
            QPen p(col,1, Qt::SolidLine);
            tool->scene_ap->addRect((qreal)1,(qreal)1,(qreal)25,(qreal)25,p,br);
            tool->rgbToYuv(r,v,b); 
            //composante rouge
            s = "<font color=\"#FF0000\">Y : ";
            s.append(QString::number(*r));
            s.append("   </font>");
            tool->lab_r->setText(s);

            //composante verte
            s = "<font color=\"#419F2E\">U : ";
            s.append(QString::number(*v));
            s.append("   </font>");
            tool->lab_v->setText(s);

            //composante bleue
            s = "<font color=\"#0000FF\">V : ";
            s.append(QString::number(*b));
            s.append("   </font>");
            tool->lab_b->setText(s);
            
            //milieu
            

         }         
       } 
  
     
     //si la selection est activee et click presse et que l'on ne déplace pas le cadre


     if(tool->rectangleSelectionActive && !tool->bool_deplacement && tool->bool_pressed && bool_in_im && tool->rect_image->contains(tool->pos_press_x,tool->pos_press_y))

     {

         tool->supression_cadre_selection();
         tool->rect_selection->setRect(0,0,0,0);
         
 /******************* rectangle de selection *****************************************/
         int l = x-tool->pos_press_x;
         int h = y-tool->pos_press_y;
  
         //si Hauteur ou Largeur est <0 ou >0
         
         if(h < 0 && l > 0)
            {rec_sel->setRect(tool->pos_press_x,tool->pos_press_y+h,l,-h);
            }
         else if(l < 0 && h > 0)
            {rec_sel->setRect(tool->pos_press_x+l,tool->pos_press_y,-l,h);}
         else if(l < 0 && h < 0)
            {rec_sel->setRect(tool->pos_press_x+l,tool->pos_press_y+h,-l,-h);}
         else
            {rec_sel->setRect(tool->pos_press_x,tool->pos_press_y,l,h);}
         boutonRogner->setEnabled(true);
         
         rectitem_selection = tool->scene->addRect(*rec_sel,*pen_rec_sel,*brush_rec_sel);
         tool->rectitem_selection = this->rectitem_selection;
      
 /***************** rectangle taille de selection *************************************/
         
         rec_taille_sel->setRect(x+20,y,125,20);
         rectitem_taille_selection = tool->scene->addRect(*rec_taille_sel,*pen_rec_taille_sel,*brush_rec_taille_sel);
         tool->rectitem_taille_selection = this->rectitem_taille_selection;
         
         QString s1("L : ");
         s1.append(QString::number(abs(l)));
         
         QString s2("H : ");
         s2.append(QString::number(abs(h)));
         
         simpletext1 = tool->scene->addSimpleText(s1);
         simpletext1->setPos(x+30,y+2);
         simpletext2 = tool->scene->addSimpleText(s2);
         simpletext2->setPos(x+85,y+2);
         tool->simpletext1 = this->simpletext1;
         tool->simpletext2 = this->simpletext2;
     }
     
     /************ deplacement du rectangle ************/
     else if(tool->rectangleSelectionActive && tool->bool_pressed && tool->bool_deplacement)
     {
         
         tool->supression_cadre_selection();
       //  std::cout << tool->rect_image->width() << std::endl;
         tool->dpl_x = x-tool->pos_press_x;
         tool->dpl_y = y-tool->pos_press_y;

        // std::cout <<  tool->dpl_y << std::endl;

         if((tool->rec_x+tool->dpl_x) > 0 && (tool->rec_x+tool->dpl_x) < (im->width() - tool->rect_selection->width()))
         {
             
          tool->dpl_x_contain = tool->dpl_x;
         }
         
        if((tool->rec_y+tool->dpl_y) > 0 && (tool->rec_y+tool->dpl_y) < (im->height() - tool->rect_selection->height()))
         { 
          tool->dpl_y_contain = tool->dpl_y;
         }
          
          rec_sel->setRect(tool->rec_x+tool->dpl_x_contain,tool->rec_y+tool->dpl_y_contain,tool->rect_selection->width(),tool->rect_selection->height());
          tool->rect_selection = rec_sel;
          rectitem_selection = tool->scene->addRect(*rec_sel,*pen_rec_sel,*brush_rec_sel);
          tool->rectitem_selection = this->rectitem_selection; 
        
      }
    }
}

void customGraphicsView::mousePressEvent(QMouseEvent *a)
{
    int x = mapToScene(a->pos()).x()/tool->getZoomFactor();
    int y = mapToScene(a->pos()).y()/tool->getZoomFactor();
    if(tool->checkBoxSelection){
        QPointF scenefg=tool->fg->pos();
        QPointF scenebg=tool->bg->pos();

        clicx=x;
        clicy=y;
        if((x<(scenefg.x()+(tool->fg->label->width()/tool->getZoomFactor()))) && (x>scenefg.x()) && (y<(scenefg.y()+(tool->fg->label->height()/tool->getZoomFactor()))) && (y>scenefg.y())){
            imageSelectionnee=true;
            tool->fg->MymousePressEvent(a);
            tool->fg->setVisible(false);
            tool->fg->setVisible(true);

        }else if((x<(scenebg.x()+(tool->bg->label->width()/tool->getZoomFactor()))) && (x>scenebg.x()) && (y<(scenebg.y()+(tool->bg->label->height()/tool->getZoomFactor()))) && (y>scenebg.y())){

            tool->bg->MymousePressEvent(a);
            tool->fg->setVisible(false);
            tool->fg->setVisible(true);
        }

    }

    else{
        tool->bool_pressed = true;
        tool->bool_release = false;

        if(tool->rectangleSelectionActive)
        {
            tool->pos_press_x = mapToScene(a->pos()).x();
            tool->pos_press_y = mapToScene(a->pos()).y();

            std::cout<< "x:" << tool->pos_press_x << std::endl;
            std::cout<< "y:" << tool->pos_press_y << std::endl;

            if(tool->rect_selection->contains(tool->pos_press_x,tool->pos_press_y))
            {
                tool->bool_deplacement = true;
            }
            else{tool->bool_deplacement = false;boutonRogner->setEnabled(false);}

        }
    }
    if(tool->checkBoxCiseau) {
        int x = mapToScene(a->pos()).x()/tool->getZoomFactor();
        int y = mapToScene(a->pos()).y()/tool->getZoomFactor();
        if (tool->ciseauX == -1) {
            tool->ciseauX = x;
            tool->ciseauY = y;
        } else {
            ciseau cis(tool);
            cis.contour(tool->ciseauX, tool->ciseauY, x, y,tool->ciseauSeuil);
            tool->ciseauX = x ;
            tool->ciseauY = y;
        }
        fenetre->updateImageAffiche();
    }
    
}

void customGraphicsView::mouseReleaseEvent(QMouseEvent *a)
{
    int x = mapToScene(a->pos()).x()/tool->getZoomFactor();
    int y = mapToScene(a->pos()).y()/tool->getZoomFactor();
    if(tool->checkBoxSelection){
        QPointF scenefg=tool->fg->pos();
        QPointF scenebg=tool->bg->pos();

        imageSelectionnee=false;
       if((x<(scenefg.x()+(tool->fg->label->width()/tool->getZoomFactor()))) && (x>scenefg.x()) && (y<(scenefg.y()+(tool->fg->label->height()/tool->getZoomFactor()))) && (y>scenefg.y())){
            tool->fg->MymouseReleaseEvent(a);
       }else if((x<(scenebg.x()+(tool->bg->label->width()/tool->getZoomFactor()))) && (x>scenebg.x()) && (y<(scenebg.y()+(tool->bg->label->height()/tool->getZoomFactor()))) && (
                    y>scenebg.y())){

            tool->bg->MymouseReleaseEvent(a);
        }
       tool->fg->setVisible(false);
       tool->fg->setVisible(true);

    }else{

        tool->bool_pressed = false;
        tool->bool_release = true;

        if(tool->rectangleSelectionActive)
        {
            tool->pos_release_x = mapToScene(a->pos()).x();
            tool->pos_release_y = mapToScene(a->pos()).y();

            int l = tool->pos_release_x - tool->pos_press_x;
            int h = tool->pos_release_y - tool->pos_press_y;

            if(l != 0 && h != 0 && !tool->bool_deplacement && tool->rect_image->contains(tool->pos_press_x,tool->pos_press_y))
            {
                if(l < 0 && h > 0)
                {
                    tool->rect_selection->setRect(tool->pos_press_x+l,tool->pos_press_y,-l,h);
                    tool->rec_x = tool->pos_press_x+l;
                    tool->rec_y = tool->pos_press_y;
                }
                if(l > 0 && h < 0)
                {
                    tool->rect_selection->setRect(tool->pos_press_x,tool->pos_press_y+h,l,-h);
                    tool->rec_x = tool->pos_press_x;
                    tool->rec_y = tool->pos_press_y+h;
                }
                if(l < 0 && h < 0)
                {
                    tool->rect_selection->setRect(tool->pos_press_x+l,tool->pos_press_y+h,-l,-h);
                    tool->rec_x = tool->pos_press_x+l;
                    tool->rec_y = tool->pos_press_y+h;
                }
                if(l > 0 && h > 0)
                {
                    tool->rect_selection->setRect(tool->pos_press_x,tool->pos_press_y,l,h);
                    tool->rec_x = tool->pos_press_x;
                    tool->rec_y = tool->pos_press_y;
                }

            }

            //si on clique sans glissement et que l'on n'est pas dans une zone selectionnee on delete la selection
            if(l == 0 && h == 0 && !tool->rect_selection->contains(mapToScene(a->pos()).x(),mapToScene(a->pos()).y()))
            {

                tool->supression_cadre_selection();
                tool->rect_selection->setRect(0,0,0,0);
                tool->bool_deplacement = false;
            }
            if(l != 0 && h != 0 && tool->bool_deplacement)
            {//std::cout << "lalalou ! "<<std::endl;
                tool->rec_x = tool->rect_selection->x();
                tool->rec_y = tool->rect_selection->y();
            }

        }
    }
}

customGraphicsView::~customGraphicsView()
{
//    delete(tool);
//    delete(rectitem_selection);
//    delete(rectitem_taille_selection);
//    delete(simpletext1);
//    delete(simpletext2);
//    delete(pen_rec_sel);
//    delete(pen_rec_taille_sel);
//    delete(color_transp);
//    delete(brush_rec_sel);
//    delete(brush_rec_taille_sel);
//    delete(rec_sel);
//    delete(rec_taille_sel);  
//    delete r;
//    delete v;
//    delete b;
//    delete a;
}
