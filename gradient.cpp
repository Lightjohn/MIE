/* 
 * File:   gradient.cpp
 * Author: Adri
 * 
 * Created on 11 janvier 2012, 12:42
 */

#include "gradient.h"

gradient::gradient(int** matrix,outils *tool) 
{
    this->tool = tool;
    this->matrix = matrix;
}

gradient::~gradient() {
}

void gradient::dijkstra(int x, int y) {
    //init matrice a +infini
    QImage *imageIn = tool->getImage();
    
//***************************************************//
//*                                                 *//
//*   ici j'enleve 2 -> a supprimer pour debugger   *//
//*                                                 *//
//***************************************************//
    
    int l = imageIn->width() - 2;
    int h = imageIn->height() - 2;

//    std::cout << l << std::endl;
//    std::cout << h << std::endl;
    
    matrixTemp = new int * [h];
    for (int i = 0; i < h; i++) {
        matrixTemp[i] = new int[l];
    }
    //initialisation matrice à +inf
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            matrixTemp[i][j] = 2000000000;
        }}
    
    QQueue<element>queue;
    //on met à 0 le poids du 1er element
    matrixTemp[x][y] = 0;
    
    element dep(x, y, 0); 
    queue.enqueue(dep);
    //DI.J.RA en lui meme
    while (!queue.isEmpty()) {

        element tmp = queue.dequeue();
        
        //std::cout << tmp.x << " " << tmp.y << std::endl;
        
        if ((tmp.y) - 1 >= 0 && (tmp.x)+1 < h)
        {
            //gauche(x-1 , y , poids(x,y) + poids(x-1,y) , 0)
            element gauche(tmp.x + 1, tmp.y - 1, matrixTemp[tmp.x][tmp.y] + matrix[tmp.x + 1][tmp.y-1]);
            if (gauche.poid < matrixTemp[tmp.x + 1][tmp.y - 1]) {
                matrixTemp[tmp.x + 1][tmp.y - 1] = gauche.poid;
                queue.enqueue(gauche);
            }
        }
        
        if ((tmp.y) + 1 < l && (tmp.x) + 1 < h)
        {
            element droite(tmp.x+1, tmp.y+1, matrixTemp[tmp.x][tmp.y]+ matrix[tmp.x+1][tmp.y+1]);
            if (droite.poid < matrixTemp[tmp.x+1][tmp.y+1]) {
                matrixTemp[tmp.x+1][tmp.y+1] = droite.poid;
                queue.enqueue(droite);
            }
        }
        
        if ((tmp.x) + 1 < h)
        {
            element dessous(tmp.x + 1, tmp.y, matrixTemp[tmp.x][tmp.y] + matrix[tmp.x + 1][tmp.y]);
            if (dessous.poid < matrixTemp[tmp.x + 1][tmp.y]) {
                matrixTemp[tmp.x + 1][tmp.y] = dessous.poid;
                queue.enqueue(dessous);
            }
        }

    }
    
//***************************************************//
//*                                                 *//
//*   modifie la borne du i pour tout re-parcourir  *//
//*                                                 *//
//***************************************************//

    for (int i = h-1; i < h; i++) {
        for (int j = 0; j < l; j++) {
            std::cout << matrixTemp[i][j] << " ";
        }
        std::cout << "\n";
    }

}

element::element(int i,int j,int pds){
    x = i;
    y = j;
    poid = pds;
}