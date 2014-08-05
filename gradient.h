/* 
 * File:   gradient.h
 * Author: Adri
 *
 * Created on 11 janvier 2012, 12:42
 */

#ifndef GRADIENT_H
#define	GRADIENT_H
#include "outils.h"
#include "QQueue"
class gradient {
public:
    gradient(int** m,outils *tool);
    virtual ~gradient();
     void dijkstra(int x,int y);
private:
    //QQueue
    outils *tool;
    int** matrix;
    int** matrixTemp;
   
};



class element {
    
public:
    element(int,int,int);
    int x;
    int y;
    int poid;
    
};

#endif	/* GRADIENT_H */