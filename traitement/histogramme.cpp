/* 
 * File:   histogramme.cpp
 * Author: light
 * 
 * Created on 6 janvier 2012, 14:40
 */

#include "histogramme.h"

histogramme::histogramme(outils *o) {

    outil = o;
    reiinit();
}
//rgb = bool pour dire si utilisation de la convention rgb

void histogramme::calculHistogramme(int rgb) {
    reiinitTab();
    QImage *temp;
    if(!outil->imageTemp){
        temp = outil->getImage();

    }else{
        temp = outil->getImageTraite();
    }

    QColor color;
    int *r = new int, *v = new int, *b = new int, *a = new int;
    for (int i = 0; i < temp->width(); i++) {
        for (int j = 0; j < temp->height(); j++) {

            color.setRgb(temp->pixel(i, j));
            color.getRgb(r, v, b, a);
            if (!rgb) {
                outil->rgbToYuv(r, v, b);
                //std::cout<<*r<<" " <<*v<<" "<<*b<<"\n";
            }
            tabBlue[*b]++;
            tabGreen[*v]++;
            tabRed[*r]++;
        }
    }
    trouverMax();
    //affichage();
}

void histogramme::trouverMax() {
    int moyr = 0, moyg = 0, moyb = 0;
    for (int i = 0; i < 256; i++) {
        if (tabBlue[i] > nombreMoy) {
            moyb += tabBlue[i];
        }
        if (tabRed[i] > nombreMoy) {
            moyr += tabRed[i];
        }
        if (tabGreen[i] > nombreMoy) {
            moyg += tabGreen[i];
        }

    }
    moyb = moyb / 256;
    moyr = moyr / 256;
    moyg = moyg / 256;
    nombreMoy = (moyb + moyr + moyg) / 3;
    if(nombreMoy==0){nombreMoy++;}
}

histogramme::~histogramme() {
}
//il y a des valeurs par défaut !!!
//ATTENTION YUV necessite une hauteur max plus grande (>=5);
//alors que RGB se contente des valeurs par defauts

QGraphicsScene* histogramme::getHistogrammes(int hauteurMax, int longueurGraphe, int hauteurGraphe) {

    QGraphicsScene *scene = new QGraphicsScene();
    QColor *color_black = new QColor(0, 0, 0, 150);
    QColor *color_red = new QColor(255, 0, 0, 150);
    QColor *color_blue = new QColor(0, 0, 255, 150);
    QColor *color_green = new QColor(0, 255, 0, 150);
    //QBrush brush_rec_sel = new QBrush(*color_transp);
    QPen penn(*color_black, 1, Qt::SolidLine);
    QPen penr(*color_red, 1, Qt::SolidLine);
    QPen peng(*color_green, 1, Qt::SolidLine);
    QPen penb(*color_blue, 1, Qt::SolidLine);

    //int longueurGraphe = 1;int hauteurMax = 3;int hauteurGraphe = 50;
    scene->addLine(- 256, 0,- 256, -hauteurMax*hauteurGraphe,penn);
    for (int i = 0; i < 256 * longueurGraphe; i = i + longueurGraphe) {

        if (tabRed[i / longueurGraphe] > hauteurMax * nombreMoy) {
            scene->addLine(i - 256, 0, i - 256, -hauteurMax*hauteurGraphe, penr);
        } else {
            scene->addLine(i - 256, 0, i - 256, -tabRed[i / longueurGraphe] * hauteurGraphe / nombreMoy, penr);
        }

        if (tabGreen[i / longueurGraphe] > hauteurMax * nombreMoy) {
            scene->addLine(i - 256, 0, i - 256, -hauteurMax*hauteurGraphe, peng);
        } else {
            scene->addLine(i - 256, 0, i - 256, -tabGreen[i / longueurGraphe] * hauteurGraphe / nombreMoy, peng);
        }

        if (tabBlue[i / longueurGraphe] > hauteurMax * nombreMoy) {
            scene->addLine(i - 256, 0, i - 256, -hauteurMax*hauteurGraphe, penb);
        } else {

            scene->addLine(i - 256, 0, i - 256, -tabBlue[i / longueurGraphe] * hauteurGraphe / nombreMoy, penb);

        }
    }
    scene->addLine(0, 0,0, -hauteurMax*hauteurGraphe,penn);
    
    return scene;
}

void histogramme::modifHistogrammeClarte(int modif){
    QColor color;
    QImage *imageOut = new QImage(image->width(),image->height(),image->format());
    int *r = new int, *v = new int, *b = new int, *a = new int;
    
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            
            color.setRgb(image->pixel(i, j));
            color.getRgb(r, v, b, a);
            *r+=modif;*v+=modif;*b+=modif;
            if(*r>255){*r=255;}if(*r<0){*r=0;}
            if(*v>255){*v=255;}if(*v<0){*v=0;}
            if(*b>255){*b=255;}if(*b<0){*b=0;}
            //cout<<*r<<" "<<*v<<" "<<*b<<"\n";
            color.setRgb(*r,*v,*b,*a);
            imageOut->setPixel(i,j,color.rgb());
            
        }
    }
    outil->setImageTraite(imageOut);
}

void histogramme::modifHistogrammeContraste(int min, int max){
    QColor color;
    QImage *imageOut = new QImage(image->width(),image->height(),image->format());
    int *r = new int, *v = new int, *b = new int, *a = new int;
    int temp;
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            
            color.setRgb(image->pixel(i, j));
            color.getRgb(r, v, b, a);
            
            temp = max-min;
            if(temp == 0){temp =1;}
            *r = 255*(*r-min)/(temp);
            *v = 255*(*v-min)/(temp);
            *b = 255*(*b-min)/(temp);

            if(*r>255){*r=255;}if(*r<0){*r=0;}
            if(*v>255){*v=255;}if(*v<0){*v=0;}
            if(*b>255){*b=255;}if(*b<0){*b=0;}
            //cout<<*r<<" "<<*v<<" "<<*b<<"\n";
            color.setRgb(*r,*v,*b,*a);
            imageOut->setPixel(i,j,color.rgb());
            
        }
    }
    outil->setImageTraite(imageOut);
}

void histogramme::modifHistogrammeClarteIndiv(int modifR,int modifV,int modifB){
    QColor color;
    QImage *imageOut = new QImage(image->width(),image->height(),image->format());
    int *r = new int, *v = new int, *b = new int, *a = new int;
    
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            
            color.setRgb(image->pixel(i, j));
            color.getRgb(r, v, b, a);

            *r+=modifR;*v+=modifV;*b+=modifB;
            if(*r>255){*r=255;}if(*r<0){*r=0;}
            if(*v>255){*v=255;}if(*v<0){*v=0;}
            if(*b>255){*b=255;}if(*b<0){*b=0;}

            //cout<<*r<<" "<<*v<<" "<<*b<<"\n";
            color.setRgb(*r,*v,*b,*a);
            imageOut->setPixel(i,j,color.rgb());
            
        }
    }
    outil->setImageTraite(imageOut);
}
void histogramme::affichage() {
    int i;
    for (i = 0; i < 256; i++) {
        std::cout << tabBlue[i] << " ";
    }
    for (i = 0; i < 256; i++) {
        std::cout << tabGreen[i] << " ";
    }
    for (i = 0; i < 256; i++) {
        std::cout << tabRed[i] << " ";
    }
}


void histogramme::reiinit(){
    QImage *temp;
    if(!outil->imageTemp){
        temp = new QImage(*outil->getImage());

    }else{
        temp = new QImage(*outil->getImageTraite());
    }
    image = temp;
    int j;
    for (j = 0; j < 256; j++) {
        tabBlue[j] = 0;
        tabGreen[j] = 0;
        tabRed[j] = 0;
    }
    nombreMoy = 0;
}

void histogramme::reiinitTab(){
    int j;
    for (j = 0; j < 256; j++) {
        tabBlue[j] = 0;
        tabGreen[j] = 0;
        tabRed[j] = 0;
    }
    nombreMoy = 0;
}
