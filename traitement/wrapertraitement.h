
#ifndef WRAPERTRAITEMENT_H
#define WRAPERTRAITEMENT_H
#include "./outils.h"

enum{NOYAU_MOYENNEUR,NOYAU_REHAUSSEMENT,NOYAU_PASSEBAS,NOYAU_REHAUSSEMENTCONTRASTE,NOYAU_DETECTIONBORD,NOYAU_GRADIENTX,NOYAU_GRADIENTY,NOYAU_PERSONNALISE};


class wraperTraitement
{
public:
    wraperTraitement(outils *t);
    ~wraperTraitement();
    QImage *construireImageTemp( outils *t);
    int** retourner_noyau(int numero_noyau);
    void conv(int taille,int noyau);
    void _conv(int taille,int noyau);
    void convTraitement(int taille,int noyau);
    void rehaussementContour(int lim);
    int** _conv_gradient(int tailles);
    int filtrage_gradient(int i, int j,int **m);
     void affichMat(int i);
     int a1,a2,a3,a4,a5,a6,a7,a8,a9;
    
   /************ Fonctions pour seam carving ***************/  
     
      void gradient();
      void filt_grad(int x, int y, int **m);
       
   /********************************************************/  
private:
    QRgb filtrage(int i,int j,int **m);
    int** retournementSpatial(int **m);
    
   
    outils *tool;
    int som;
    int taille;
    QImage *imageOut;
    QImage *temp;
};



#endif // WRAPERTRAITEMENT_H
