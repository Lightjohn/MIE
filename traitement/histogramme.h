/* 
 * File:   histogramme.h
 * Author: light
 *
 * Created on 6 janvier 2012, 14:40
 */

#ifndef HISTOGRAMME_H
#define	HISTOGRAMME_H
#include "outils.h"

class histogramme {
public:
    histogramme(outils *o);
    void calculHistogramme(int rgb);
    void modifHistogrammeClarte(int modif);
    void modifHistogrammeClarteIndiv(int modifR=0,int modifV=0,int modifB=0);
    void modifHistogrammeContraste(int min, int max);
    void affichage();
    void reiinit();
    void reiinitTab();
    virtual ~histogramme();
    QGraphicsScene *getHistogrammes(int hauteurMax = 3,int longueurGraphe = 1,int hauteurGraphe = 50);
    
private:
    void trouverMax();
    outils *outil;
    QImage *image;
    int tabRed[256];
    int tabBlue[256];
    int tabGreen[256];
    int nombreMoy;//Le nombre de la couleur la plus presente
    
};

#endif	/* HISTOGRAMME_H */

