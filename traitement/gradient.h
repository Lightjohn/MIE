/* 
 * File:   gradient.h
 * Author: Adri
 *
 * Created on 11 janvier 2012, 12:42
 */

#ifndef GRADIENT_H
#define	GRADIENT_H
//#include "outils.h"
#include "QQueue"
#include "wrapertraitement.h"
#include <math.h>

class element {
    
public:
    element();
    element(int,int,int=0);
    int x;
    int y;
    int poid;
    int poidPot;
    
};

class gradient {
public:
    gradient(outils *tool);
    virtual ~gradient();
     int dijkstra(int x,int y,int *chem);
     void SC_agrandissement_horizontal(int);
     void SC_reduction_horizontal(int);
     void recup_chem_verticaux(int nb_chem);
     void SC_agrandissement_vertical(int);
     void SC_reduction_vertical(int);
     void recup_chem_horizontaux(int nb_chem);
     int parcours_naif(int x ,int *chem);
     void supr_chem_mat(int *chemin_a_supprimer);
     void add_chem_mat(int *chemin_a_supprimer);
     void maj_picture();
private:
    void affichMat(int);
    outils *tool;
    int** matrixTemp;
    int **m1;
    int **m2;
    QImage *imagein;   
    QImage *imageout;
    QImage *image_temp;
    wraperTraitement *wrap;
    int *chem;
   
};





#endif	/* GRADIENT_H */
