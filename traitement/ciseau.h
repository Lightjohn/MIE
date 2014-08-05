/* 
 * File:   ciseau.h
 * Author: light
 *
 * Created on 18 janvier 2012, 16:53
 */

#ifndef CISEAU_H
#define	CISEAU_H
#include "interface/fenetrePrincipale.h"
#include <queue>

class C
{
public:
    bool operator()(const element &a1, const element &a2)
    {
        return a1.poidPot > a2.poidPot ;
    }
};

class C2
{
public:
    bool operator()(const element &a1, const element &a2)
    {
        return a1.y > a2.y ;
    }
};

class ciseau {
public:
    ciseau(outils *t);
    virtual ~ciseau();
    void contour(int x1,int y1,int x2, int y2, int seuil);
    void decouperImage();
    priority_queue<element, vector<element>, C2> pixelContour;
private:
    //retourne la longueur du chemin et elem et une matrice 2*longueur_chemin
    //qui contient x en 0 et y en 1


    outils *tool;
    wraperTraitement *wrap;
    int** matrixTemp;
    queue<element> successeurQueue;
    int **traite;
    QImage *imageIn;
    int astar(int x, int y,int x2,int y2, int seuil);
    void successeur(int x,int y,int h,int l);
    void successeur2(int x,int y,int h,int l);
    void affiche_chemin(element arrive,element depart,int h,int l);
//    void calculeGradient(int seuil);
//    int dijkstra(int x, int y,int x2,int y2,int **elem);
};





#endif	/* CISEAU_H */