#ifndef FUSION_H
#define FUSION_H
#include "wrapertraitement.h"
class outils;
class fusion
{
public:
    fusion(outils *t);
    void fusionner(QImage *fg,QImage *bg,QPoint position, int alphafg);
    void ouvrir_image_a_rajouter(QString chemin);
    QImage* getImageFg();
private:
    outils *tool;
    QImage *imagefg;
    int widthfg;
    int heightfg;
    QRgb calculerMultiplicationParAlpha(QRgb p1,QRgb p2,int alphafg);

};

#endif // FUSION_H
