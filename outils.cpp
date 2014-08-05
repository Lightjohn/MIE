
/* 
 * File:   Global.cpp
 * Author: light
 * 
 * Created on 3 janvier 2012, 16:14
 */



#include <QtGui/qimage.h>
#include <QtCore/qlist.h>

#include "outils.h"
#include "stdio.h"
#include "traitement/fusion.h"


using namespace std;
position::position(int xx, int yy){
    x=xx;
    y=yy;
}
outils::outils(QClipboard *cp)
{
    rectangleSelectionActive = false;
    pos_press_x = 0;
    pos_press_y = 0;
    pos_release_x = 0;   
    pos_release_y = 0;
    bool_pressed = false;
    bool_deplacement = false;
    bool_release = true;
    rect_selection = new QRect();
    rect_image = new QRect();
    dpl_x = 0;
    dpl_y = 0;
    rec_x = 0;
    rec_y = 0;
    dpl_x_contain = 0;
    dpl_y_contain = 0;
    nombre_appel_move = 0;
    bool_image_gradient = false;

    mat_w = 0;
    mat_h = 0;
    
    copieActivee=false;
    imagefg=NULL;

    val_champ_hauteur = 0;
    val_champ_largeur = 0;
    
    zoomFactor=1.0;
    imageZoomee=new QImage();
    imageTraiteZoomee=new QImage();
     this->cp=cp;
    checkBoxSelection=false;
    checkBoxCiseau=false;
    ciseauX=-1;
    ciseauY=-1;
    ciseauSeuil=1;
    imageTemp = false;
    utiliserRGB = 1;
    
    check_redim = 0;
    check_intelligent = 0;
    decoupagePossible = false;
    redimensionnement=false;
}

outils::~outils()
{
//   delete rect_selection;
//   delete rect_image;
//   delete image;
//   delete image_init;
   //delete chem_parcours_grad;
}
void outils::ouvrir_image_memoire(QString chemin){
    image=NULL;
    image=new QImage(chemin);
    image_init=new QImage(chemin);

    *image=image->convertToFormat(QImage::Format_ARGB32);
    *image_init=image->convertToFormat(QImage::Format_ARGB32);



        width=image->width();
        height=image->height();
     supression_cadre_selection();
    rect_selection->setRect(0,0,0,0);
    rect_image->setRect(0,0,width,height);
    undo.push(*image);
    setImageTraite(image);
    reinitCiseau();
}
int outils::getHeight()
{
        return height;
    }

QImage* outils::getImage()
{
        return image;
}
QImage* outils::getImageFg(){
     return this->imagefg;
}
void outils::setImageFg(QImage *fg){
    imagefg=fg;
}

void outils::setImage(QImage *im){

    //delete image;
    //cout<<"setimage\n";
    if(!redo.isEmpty()){
        undo.clear();
        redo.clear();
        refaireBouton->setEnabled(false);
        actionRef->setEnabled(false);
    }
    supression_cadre_selection();
    rect_selection->setRect(0,0,0,0);
    if(zoomFactor!=1.0){
        if(undo.isEmpty())
            undo.push(*imageZoomee);
         image=im;
        *imageZoomee=image->scaled(QSize(image->width()*zoomFactor,image->height()*zoomFactor));
         undo.push(*imageZoomee);
         width=imageZoomee->width();
         height=imageZoomee->height();

    }else{
        if(undo.isEmpty())
             undo.push(*image);
        image=im;
        undo.push(*im);
        width=im->width();
        height=im->height();


    }

    actionAnnul->setEnabled(true);
    annulBouton->setEnabled(true);
     rect_image->setRect(0,0,width,height);


}
void outils::setImage2(QImage *im){

    //delete image;

    image=im;
    width=im->width();
    height=im->height();

}
void outils::zoom(){
    *imageZoomee=image->scaled(QSize(image->width()*zoomFactor,image->height()*zoomFactor));

    if(imageTemp == true){
        *imageTraiteZoomee = imageTraite->scaled(QSize(image->width()*zoomFactor,image->height()*zoomFactor));
    }


}


void outils::annuler(){
    QImage tmp;
    if(!undo.isEmpty()){
      tmp=undo.pop();
      redo.push(tmp);
      QImage old;
      old=undo.top();
      *image=old;
      width=old.width();
      height=old.height();

      actionRef->setEnabled(true);
      refaireBouton->setEnabled(true);

    }
    if(undo.count()==1){
        actionAnnul->setEnabled(false);
        annulBouton->setEnabled(false);
    }
 }


void outils::refaire(){
    QImage tmp;
    if(!redo.isEmpty()){
        tmp=redo.pop();
        undo.push(tmp);
        QImage n;
        n=undo.top();
        *image=n;
        width=n.width();
        height=n.height();

    }
    if(!undo.isEmpty()){
        actionAnnul->setEnabled(true);
        annulBouton->setEnabled(true);
    }
    if(redo.isEmpty()){
        actionRef->setEnabled(false);
        refaireBouton->setEnabled(false);
    }

}
void outils::ajouterAnnuler(QImage *im){
    if(!redo.isEmpty()){
        undo.clear();
        redo.clear();
    }
    //aRefaire->setDisabled(true);

   // aAnnuler->setDisabled(false);
    undo.push(*im);
}


QImage* outils::getImage_init()
{
        return image_init;
    }
 int outils::getWidth()
 {
        return width;
    }
 

QStack<QImage> outils::getUndo(){
    return undo;
}
QStack<QImage> outils::getRedo(){
    return redo;
}

void outils::getPixel(int w, int h, int *r,int *g, int *b, int *aa) {
    QColor color;
    color.setRgb(image->pixel(w, h));
    color.getRgb(r, g, b, aa);
}

void outils::getPixelGradient(int x, int y, int *r,int *g, int *b, int *aa) {
    QColor color;
    color.setRgb(get_case(x,y)->pix);
    color.getRgb(r, g, b, aa);
}

QImage* outils::getImageZoomee(){
    return imageZoomee;
}


void outils::setImageZoomee(QImage* im){
   // delete imageZoomee;
    imageZoomee=im;

}
void outils::saveImage(QString a){
    if(!image->save(a)){
        std::cout<<"erreur sauvegarde image";
    }
}

void outils::rgbToYuv(int *r,int *g, int *b) {
    double aa,bb,cc,y=*r, u=*g, v=*b;
    //cout<<"RVBtmp "<<y<<" "<<u<<" "<<v<<"\n";
    aa = 0.299*y + 0.587*u + 0.114*v;
    bb = -0.14713*y -0.28886*u + 0.436*v;
    cc = 0.615*y -0.51498*u -0.10001*v;
    *r = (int) aa;
    *g = (int) bb;
    *b = (int) cc;
}


void outils::yuvToRgb(int*r,int*g, int*b){
    double aa,bb,cc,y=*r, u=*g, v=*b;
    aa = y + 1.13983*v;
    bb = y -0.39465*u -0.58060*v;
    cc = y +2.03211*u;
    *r = (int) aa;
    *g = (int) bb;
    *b = (int) cc;
}

void outils::supression_cadre_selection()
{
    rectitem_selection->setVisible(false);
    rectitem_taille_selection->setVisible(false);
    //rect_selection->setRect(0,0,0,0);
    simpletext1->setVisible(false);
    simpletext2->setVisible(false);
    rectitem_selection->setVisible(false);
//    QList<QGraphicsItem *> list;
//    list = scene->items();
//    while(!list.isEmpty())
//        {scene->removeItem(list.takeFirst());}   
}

qreal outils::getZoomFactor(){
    return zoomFactor;
}

void outils::setZoomFactor(qreal a){
    zoomFactor = a;
}
int outils::makeRGB(int red, int green, int blue, int alpha){
    return ((blue & 0xFF) + ((green & 0xFF) << 8) + ((red & 0xFF) << 16) + (alpha & 0xFF << 24));
}

QImage* outils::getImageTraite(){
    return imageTraite;
}
QImage* outils::getImageTraiteeZoomee(){
    return imageTraiteZoomee;
}

void outils::setImageTraite(QImage *imageTrait){
    imageTraite = imageTrait;
    imageTemp = true;
    if(zoomFactor!=1.0){
        *imageTraiteZoomee=imageTraite->scaled(QSize(image->width()*zoomFactor,imageTraite->height()*zoomFactor));
         width=imageTraiteZoomee->width();
         height=imageTraiteZoomee->height();
    }else{
        width=imageTraite->width();
        height=imageTraite->height();
    }
    
    supression_cadre_selection();
    rect_selection->setRect(0,0,0,0);
    rect_image->setRect(0,0,width,height);
}
void outils::copier(){
    QImage *selection;

    if(rectangleSelectionActive){
        int x=rect_selection->x();
        int y=rect_selection->y();
        int w=rect_selection->width();
        int h=rect_selection->height();
        selection=new QImage(QSize(w,h),QImage::Format_ARGB32);
        QColor c;
        int r,g,b,a;
        int m=0,n=0;
        for(int i=x;i<x+w;i++){
            n=0;
            for(int j=y;j<y+h;j++){
                getPixel(i,j,&r,&g,&b,&a);
                c.setRgb(r,g,b,a);
                selection->setPixel(m,n,c.rgba());
                n++;
            }
            m++;
        }
    cp->setImage(*selection);

    }else if(!rectangleSelectionActive && fg->selectionActivee){
        const QPixmap *p;
        p=fg->label->pixmap();
        if(p!=0){
            QImage i;
            i=p->toImage();
            cp->setImage(i);
        }
    }else if(!rectangleSelectionActive && bg->selectionActivee){
       const QPixmap *p;
        p=bg->label->pixmap();
        if(p!=0){
            QImage i;
            i=p->toImage();
            cp->setImage(i);
        }
    }
}
void outils::couper(){
    if(rectangleSelectionActive){
     copier();
     int x=rect_selection->x();
     int y=rect_selection->y();
     int w=rect_selection->width();
     int h=rect_selection->height();
     QColor c;
     for(int i=x;i<x+w;i++){

         for(int j=y;j<y+h;j++){

             c.setRgb(255,255,255,255);
             image->setPixel(i,j,c.rgba());

         }
     }
    }else if(!rectangleSelectionActive && fg->selectionActivee){
    const QPixmap *p;
    p=fg->label->pixmap();
    if(p!=0){
        QImage i;
        i=p->toImage();
        cp->setImage(i);
        fg->label->clear();
        fg->label->repaint();

    }
    }else if(!rectangleSelectionActive && bg->selectionActivee){
    const QPixmap *p;
     p=bg->label->pixmap();
     if(p!=0){
           QImage i;
           i=p->toImage();
           cp->setImage(i);
           bg->label->clear();
           bg->label->repaint();

      }
    }

}
int outils::coller(){
    QImage selection;

    selection=cp->image(QClipboard::Clipboard);

    fusion *fus=new fusion(this);
    if(rectangleSelectionActive){
        int x=rect_selection->x();
        int y=rect_selection->y();
        QColor c;

        QRgb* a=(QRgb*)selection.scanLine(0);
        c.setRgb(*a);
        int alpha=c.alpha();
        fus->fusionner(&selection,image,QPoint(x,y),alpha);
        return 0;
    }
    else if(!rectangleSelectionActive && fg->selectionActivee){
        *imagefg=selection;
        return 1;
    }else if(!rectangleSelectionActive && bg->selectionActivee){
        *image=selection;
        return 2;
    }
    return 5;
}

void outils::init_podium(int nb_places, int taille_chem)
{
    
    /*Podium est une matrice qui contient tout les chemins,
     * pod[i][0] contient le poids du chemin
     * et pod[i][j] contient le chemin associé.
     */
    podium_l = taille_chem + 1;
    podium_h = nb_places;
    chemin_parcour_actuel = 0;
    
    podium = new int* [podium_h];
    for(int i = 0 ; i < podium_h ; i++)
      {
        podium[i] = new int[podium_l];
        podium[i][0] = 0x7FFFFFFF;
        for(int j = 1 ; j < podium_l ; j++)
            {podium[i][j] = -1;}
      }   
}

void outils::podium_backup()
{   
    podium_base = new int* [podium_h];
    for(int i = 0 ; i < podium_h ; i++)
      {
        podium_base[i] = new int[podium_l];
        for(int j = 0 ; j < podium_l ; j++)
            {podium_base[i][j] = podium[i][j];}
      }
    
}

void outils::podium_recup()
{
 for(int i = 0 ; i < podium_h ; i++)
      {
    for(int j = 0 ; j < podium_l ; j++)
        {podium[i][j] = podium_base[i][j];}
      }   
 
// int **matrix_tmp = new int*[imageGradient->height()];
//    for(int i = 0 ; i < imageGradient->height() ; i++)   
//    {
//        matrix_tmp[i] = new int [imageGradient->width()];
//        
//        for(int j = 0 ; j < imageGradient->width() ; j++)
//        {
//            matrix_tmp[i][j] = matrix_base[i][j];
//        }
//    }
// 
// matrix = matrix_tmp;
// mat_h = imageGradient->height();
// mat_w = imageGradient->width();
 
}

void outils::delete_podium()
{
    for(int i = 0; i < podium_h; i++)
     {
        delete podium[i];

    }
    delete podium;
}


void outils::add_podium(int *chem,int poids)
{
    
    bool paschem = true;
    int min = 0x7FFFFFFF;
    int pos = 0;
    for(int i = 0 ; i < podium_h ; i++)
    {
         if(podium[i][0] < min){min = podium[i][0]; pos = i;}
         
        if(podium[i][0] == 0x7FFFFFFF)
        {
           // std::cout << "ajout podium en position "<< i << std::endl; 
           
            podium[i][0]  = poids;
            for(int j = 1 ; j < podium_l ; j++)
            {podium[i][j] = chem[j-1];}
            paschem = false;
            break;
        }
    }
    
     if(paschem) {
         
          podium[pos][0]  = poids;
            for(int j = 1 ; j < podium_l ; j++)
            {podium[pos][j] = chem[j-1];}
          paschem = false;
     }
    
//    if(paschem)
//    {
//    std::cout << "ERREUR : plus de place libre dans podium" << std::endl;
//    
//    }
    
//    for(int i = 0 ; i < podium_h ; i++)
//    {
//        std::cout << "apres ajout "<<i<< " : "<< podium[i][0] << std::endl; 
//    }
//    std::cout << std::endl;
    
   
}

/*
 * Retourne le chemin le plus court et le supprime de la liste.
 */
int* outils::get_podium()
{
    chem_parcours_grad = new int[podium_l-1];
    
    int max = 0x7FFFFFFF;
    int num = 0;
    for(int i = 0 ; i < podium_h ; i++)
      {
       // std::cout << "\npod["<<i<<"] = " << podium[i][0] << " ";
        
//        for(int j = 1 ; j < podium_l ; j++)
//        {
//            std::cout << podium[i][j] << " ";
//        }
        
        if(max >= podium[i][0])// && podium[i][0] >= 0)
            {
            max = podium[i][0];
            num = i;
            }
      }
   // std::cout << "\npoids min : " << podium[num][0] << "("<<num<<")"<< std::endl;
    if(podium[num][0] == 0x7FFFFFFF)
         {
          std::cout << "ERREUR : plus de chemin a recuperer ! "<< std::endl;
        }
    
    //std::cout << " chem recupere : ";
    
    for(int i = 1 ; i < podium_l ; i++)
      {
        chem_parcours_grad[i-1] = podium[num][i];
       // std::cout << chem_parcours_grad[i-1] << " ";
      //podium[num][i] = -1999; 
      }
    
   // std::cout << std::endl;
    
    podium[num][0] = 0x7FFFFFFF;
 
//    for(int i = 0 ; i < podium_l-1 ; i++)
//      {
//        if(chem_parcours_grad[i] < 0 || chem_parcours_grad[i] >= matrice_w)
//           {
//            //std::cout << "ERREUR : recuperation chemin faux ! ("<<chem_parcours_grad[i]<<")" << std::endl;
//           // break;
//            chem_parcours_grad[i] -= 1; 
//           }
//      }
    
    return chem_parcours_grad;
  }
    

void outils::get_deb_chem(int *tab)
{
    for(int i = 0 ; i < podium_h ; i++)
      {tab[i] = podium[i][0];}
}

/*Supprime les chemins qui avaient un pixels en commun avec le chem passé en parametre
 *et stoquent le début de ce chemin dans un tableau pour pouvoir les recalculer apres
 * decalle aussi de 1 Px sur la gauche tout les chemins qui sont sur la droite de chem
 */
 int* outils::maj_podium_del(int *chem)
 {
     int *chem_try_again = new int[podium_h];
     int nb = 0;
     //init a -1
     //for(int i = 0 ; i < podium_h ; i++){chem_try_again[i] = -1600;}
     
     
     for(int i = 0 ; i < podium_h ; i++)
     {
       //  std::cout << " apres maj del ";
         if(podium[i][0] != 0x7FFFFFFF && chem[podium_l-2] == podium[i][podium_l-1] && podium[i][1] < matrice_w)
         {
           //  std::cout <<"chem_x : "<< podium[i][1] << " i : "<< i << " poids : "<< podium[i][0] << std::endl;
           chem_try_again[nb+1] = podium[i][1];
                 nb++;
//                  for(int k = 1 ; k < podium_l ; k++)
//                    {
//                      podium[i][k] = -1; 
//                    }
    
                 podium[i][0] = 0x7FFFFFFF;
         }
         // std::cout << podium[i][0] << " ";
         for(int j = 1 ; j < podium_l ; j++)
         {
             //si le chem actuel est a droite de chem de base on le decalle de 1 Px
              if(/*podium[i][0] != 0x7FFFFFFF && */chem[j-1] < podium[i][j])
             {podium[i][j] -= 1;}
         //     std::cout << podium[i][j] << " ";
         }
         
       //  std::cout << "\n";
         
     }//la 1ere valeur contient le nombre de chemin a refaire et le reste contient 
     //le 1er pixel pour commencer
     
 chem_try_again[0] = nb;
// std::cout << nb << " chemins a ajouter (reduction)" << std::endl;
     
     return chem_try_again;
 }
 
 int* outils::maj_podium_add(int *chem)
 {
  int *chem_try_again = new int[podium_h];
     int nb = 0;
     //init a -1
     //for(int i = 0 ; i < podium_h ; i++){chem_try_again[i] = -2999;}
     
   //pour chaque chemin
     for(int i = 0 ; i < podium_h ; i++)
     {
        // std::cout << " apres maj add ";
         if(podium[i][0] != 0x7FFFFFFF && chem[podium_l-2] == podium[i][podium_l-1])
         {
           chem_try_again[nb+1] = podium[i][1];
                 nb++;
//                  for(int k = 1 ; k < podium_l ; k++)
//                    {
//                      podium[i][k] = -1; 
//                    }
    
                 podium[i][0] = 0x7FFFFFFF;
         }
       //  std::cout << podium[i][0] << " ";
         //pour chaque case du chemin
         for(int j = 1 ; j < podium_l ; j++)
         {
             
             //si le chem actuel est a droite de chem de base on le decalle de 1 Px
             if(/*podium[i][0] != 0x7FFFFFFF && */podium[i][j] > chem[j-1])
             {podium[i][j] += 1;}
           //   std::cout << podium[i][j] << " ";
         }
         // std::cout << "\n";
         
         
     }//la 1ere valeur contient le nombre de chemin a refaire et le reste contient 
     //le 1er pixel pour commencer
     
     
     chem_try_again[nb+1] = chem[0];
     nb++;
     if(chem[0]+1 < matrice_w)
     {
     chem_try_again[nb+1] = chem[0]+1;
     nb++;
     }
     if(chem[0]+2 < matrice_w)
     {
     chem_try_again[nb+1] = chem[0]+2;
     nb++;
     }
 
     chem_try_again[0] = nb;
    //  std::cout << nb << " chemins a ajouter (agrandissement)" << std::endl;
     return chem_try_again;
 }
 
  int outils::nombre_chemin(int hauteur, int largeur, int nb_chem)
 {
     int res = 0;
     for(int i = 0 ; i < nb_chem ; i++)
       {
         if(podium[i][hauteur+1] == largeur)
           {res++;}
       }
     return res;
 }
 
  void outils::setImageGradient(QImage* image)
 {
     imageGradient = image;
 }
 
 QImage* outils::getImageGradient()
 {
     return imageGradient;
 }
 
 int outils::min(int i,int j)
 {
     if(i < 0 || j < 0)
     {std::cout << "ERREUR : nombre negatif ("<<i<<","<<j<<")"<<std::endl;
     return -1;
     }
     if(i > j)
       {return j;}
     
     else 
       {return i;}
     
 }

 
 void outils::init_matrice_case()
 {
     matrice_case = new cases* [image->height()];
     matrice_tab = new cases** [image->height()];
     matrice_h = image->height();
     matrice_w = image->width();
     
     matrice_tab_h = image->height();
     matrice_tab_w = image->width();
     
//     std::cout << "matrice_h : " << matrice_h <<std::endl;
//     std::cout << "matrice_w : " << matrice_w <<std::endl;
     
      
     for(int i = 0 ; i < image->height() ; i++)
     {
         matrice_tab[i] = new cases* [image->width()];
         matrice_case[i] = new cases(0,i,image->pixel(0,i));
         matrice_tab[i][0] = matrice_case[i];
         matrice_case[i]->case_tab = 0;
         matrice_case[i]->precedent = NULL;
         matrice_case[i]->grad = -1;

         cases *tmp = matrice_case[i];
         for(int j = 1 ; j < image->width() ; j++)
         {
              
             cases *c = new cases(j,i,image->pixel(j,i));
             matrice_tab[i][j] = c;
             c->case_tab = j;
             
             
            // std::cout << "matrice["<<i<<","<<j<<"] = "<<matrice_tab[i][j]<<std::endl;
             c->precedent = tmp;
             tmp->suivant = c;
             c->grad = -1;
             tmp = tmp->suivant;
         }
         tmp->suivant = NULL;
     }
//      std::cout << "matrice_h : " << matrice_h <<std::endl;
//     std::cout << "matrice_w : " << matrice_w <<std::endl;
 }
 
 cases * outils::_get_cases(int x, int y)
 {
    //std::cout << "ERREUR : utilisation _get_cases ("<<x<<","<<y<<")"  << std::endl;
     cases *c = matrice_case[y];
     while(c->x != x)
     {
         c = c->suivant;
         if(c->suivant == NULL)
           {
             break;
           }
        
     }
     return c;
     
 }

 cases * outils::get_case(int x, int y)
 {   
     
     
     cases *c;
     if(x < 0 || x > matrice_w)
      {
         
       // std::cout << "ERREUR : parametre x non valable ("<<x<<","<<y<<")" << std::endl;
        
         return get_case(matrice_w-1,y);
      }
     
     //return _get_cases(x,y);

     
     if(matrice_tab_w <= x)
        {c = matrice_tab[y][matrice_tab_w-1];}
     
     else
     {c = matrice_tab[y][x];}
         
            if(c->x == x)
            {return c;}
         
            //else if(c->x < 0)
            else if(c == NULL)
              {
                return _get_cases(x,y);
                
              }
         
            else if(c->x > x)
            {
                while(c->x != x)
                  {
                    //std::cout << "precedent ! x : " << x << " c->x : " << c->x << std::endl;
                    c = c->precedent;
                    if(c == NULL) {return _get_cases(x,y);}
                  }
               // std::cout << std::endl;
                return c;
            }
         
            else if(c->x < x)
            {
                while(c->x != x)
                {
                   // std::cout << "suivant ! x : " << x << " c->x : " << c->x << std::endl;
                    c = c->suivant;
                    if(c == NULL) {return _get_cases(x,y);}
                }
               // std::cout << std::endl;
                return c;
            }
            
        
     
      std::cout << "ERREUR : get_cases , retour null ("<<x<<","<<y<<")" << std::endl;
     return NULL;
     
 }
 
void outils::reinitCiseau(){
    decoupagePossible =false;
    imageTemp =false;
    ciseauX=-1;
    ciseauY=-1;
}
