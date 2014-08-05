#include "fusion.h"
#include "outils.h"
fusion::fusion(outils *t)
{
    this->tool=t;
}
QImage* fusion::getImageFg(){
    return imagefg;
}

void fusion::ouvrir_image_a_rajouter(QString chemin){
    imagefg=NULL;
    imagefg=new QImage(chemin);
    *imagefg=imagefg->convertToFormat(QImage::Format_ARGB32);

    widthfg=imagefg->width();
    heightfg=imagefg->height();

}

QRgb fusion::calculerMultiplicationParAlpha(QRgb p1,QRgb p2,int alphafg){
    QColor c;
    int r1,g1,b1,a1,r,g,b,a;
    c.setRgb(p1);
    c.getRgb(&r,&g,&b,&a);
    c.setRgb(p2);
    c.getRgb(&r1,&g1,&b1,&a1);
    int red,blue,green;
    if(a==255){



     red=((r*alphafg)/255)+(((255-alphafg)*r1)/255);
     green=((g*alphafg)/255)+(((255-alphafg)*g1)/255);
     blue=((b*alphafg)/255)+(((255-alphafg)*b1)/255);
     c.setRgb(red,green,blue,255);
     return c.rgba();
    }else{
        red=r1;
        green=g1;
        blue = b1;
        c.setRgb(red,green,blue,a1);
        return c.rgba();

    }

}

void fusion::fusionner(QImage *fg,QImage *bg,QPoint position,int alphafg){

    int x=position.x();
    int y=position.y();
    QImage *tmp;
    tmp=bg;

    QColor color;
    int m=0,n=0;
    //int r,g,b,aa;
    
    if(fg->width()<bg->width() && fg->height()<bg->height()){
    
        for(int i=x;i<(x+fg->width())-1;i++){
            n=0;
            for(int j=y;j<(y+fg->height())-1;j++){
                if(i<bg->width() && j <bg->height() && i>0 && j>0){
                    QRgb cfg,cbg;
                    cfg=fg->pixel(m,n);
                    cbg=bg->pixel(i,j);
                    QRgb c=calculerMultiplicationParAlpha(cfg,cbg,alphafg);
                    tmp->setPixel(i,j,c);
                }


                n++;
            }
            m++;
        }
        tool->setImage(tmp);
    }
   // tmp->save("lolol.png");

}
