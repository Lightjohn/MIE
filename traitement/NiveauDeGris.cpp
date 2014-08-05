#include "NiveauDeGris.h"
#include "iostream"
#include "stdio.h"

NiveauDeGris::NiveauDeGris(outils *o)
{
    this->tool=o;
}
NiveauDeGris::~NiveauDeGris(){
   // delete tool;

}

int NiveauDeGris::couleurToGris(int red, int green, int blue){
    QColor c;
    int grey = (299*red + 587*green + 114*blue)/1000; // POSSIBLE DE CHANGER LA FORMULE
    c.setRgb(grey,grey,grey);

    return c.rgba();//0
}
void NiveauDeGris::PassageNiveauDeGris(){

    QImage *imageIn=tool->getImage();
    QColor c;
    QImage *imageOut = new QImage(tool->getWidth(),tool->getHeight(),imageIn->format());

    int r=0,g=0,b=0,aa=0;
    for(int i =0;i<tool->getWidth();i++){
        for(int j=0;j<tool->getHeight();j++){

            tool->getPixel(i,j,&r,&g,&b,&aa);

            imageOut->setPixel(i,j,couleurToGris(r,g,b));
        }
    }

   tool->setImage(imageOut);
}
