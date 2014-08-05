/* 
 * File:   zoom.cpp
 * Author: light
 * 
 * Created on 5 janvier 2012, 17:44
 */

#include <QtGui/qcolor.h>
#include <QtGui/qrgb.h>
#include <QtGui/qimage.h>
#include <iostream>

#include "traitement/zoom.h"

zoom::zoom(outils *o) {
    outil = o;
    reiinitZoom();
}

zoom::~zoom() {
}
void zoom::reiinitZoom(){
    outil->setZoomFactor(1);
    coef = 1;
    imageIn = outil->getImage();
    heightOriginal = imageIn->height();
    widthOriginal = imageIn->width();
    heightOutPrec = heightOriginal;
    widthOutPrec = widthOriginal;
}


//a =0 on dezoom
//a=1 on zoom

void zoom::zoomer(int a) {
    imageIn = outil->getImage();
    coef = outil->getZoomFactor();
    qreal increment = 0.125;
    if (a != 0) {
        coef += increment;
        if (heightOutPrec >= heightOriginal) {

            zoomPlus();
        } else {
            zoomMoin();
        }
    } else {
        if (coef - increment > 0) {
            coef -= increment;
            if (heightOutPrec > heightOriginal) {
                zoomPlus();
            } else {
                zoomMoin();
            }
        }
    }

    outil->setImageZoomee(imageOut);
    outil->setZoomFactor(coef);
}
void zoom::zoomViaFacteur(){
    imageIn = outil->getImage();
    coef = outil->getZoomFactor();
    if(coef>=1){
        zoomPlus();
    }else{
        zoomMoin();
    }
    outil->setImageZoomee(imageOut);
    outil->setZoomFactor(coef);

}


void zoom::zoomPlus() {
    int heightOut = heightOriginal*coef;
    int widthOut = widthOriginal*coef;
    imageOut = new QImage(widthOut, heightOut, imageIn->format());
    heightOutPrec = heightOut;
    widthOutPrec = widthOut;
    double beta = heightOriginal * coef / heightOriginal;
    double alpha = widthOriginal * coef / widthOriginal;
    //std::cout << "coef " << coef << "\n";
    //std::cout << "out " << widthOut << "x" << heightOut << "\n";
    //std::cout << "in " << widthOriginal << "x" << heightOriginal << "\n";

    double x, y;
    int red, blue, green;
    QRgb RGB;
    for (int i = 0; i < widthOut; i = i + alpha) {
        for (int j = 0; j < heightOut; j = j + beta) {
            red = 0;
            blue = 0;
            green = 0;
            x = i / alpha;
            y = j / alpha;
            RGB = imageIn->pixel((int) x, (int) y);
            
            for (int k = i; k < i + alpha; k++) {
                for (int l = j; l < j + beta; l++) {
                    if (k < widthOut && l < heightOut) {
                        imageOut->setPixel(k, l, RGB);
                    }
                }
            }
        }
    }
}

void zoom::zoomMoin() {



    int heightOut = heightOriginal*coef;
    int widthOut = widthOriginal*coef;
    double beta = heightOriginal / (heightOriginal * coef);
    double alpha = widthOriginal / (widthOriginal * coef);
    heightOutPrec = heightOut;
    widthOutPrec = widthOut;
    imageOut = new QImage(widthOut, heightOut, imageIn->format());

    //std::cout << "coef " << coef << "\n";
    //std::cout << "out " << widthOut << "x" << heightOut << "\n";
    //std::cout << "in " << widthOriginal << "x" << heightOriginal << "\n";

    QRgb RGB;

    for (int i = 0; i < widthOriginal; i = i + alpha) {
        for (int j = 0; j < heightOriginal; j = j + beta) {

            for (int k = i; k < i + alpha; k++) {
                for (int l = j; l < j + beta; l++) {
                    RGB = 0;


                    if (k < widthOriginal && l < heightOriginal) {
                        RGB = imageIn->pixel(k, l);
                    } else if (k >= widthOriginal && l < heightOriginal) {
                        RGB = imageIn->pixel(widthOriginal - 1, l);
                    } else if (k < widthOriginal && l >= heightOriginal) {
                        RGB = imageIn->pixel(k, heightOriginal - 1);
                    } else if (k >= widthOriginal && l >= heightOriginal) {
                        RGB = imageIn->pixel(widthOriginal - 1, heightOriginal - 1);
                    } else {
                        std::cout << "fatal error";
                        //exit(10);
                    }
                }
            }
            if ((int) i / alpha < widthOut && (int) j / beta < heightOut) {
                imageOut->setPixel((int) i / alpha, (int) j / beta, RGB);
            }
        }
    }
    
}

void zoom::redim(int w2, int h2){
    imageIn = outil->getImage();
    QImage *imageOut = new QImage(w2,h2,imageIn->format());
    int w1 = imageIn->width();
    int h1 = imageIn->height();
    //std::cout<<w1<<"x"<<h1<<"\n"<<w2<<"x"<<h2<<"\n";
    // EDIT: added +1 to account for an early rounding problem
    int x_ratio = (int)((w1<<16)/w2) +1;
    int y_ratio = (int)((h1<<16)/h2) +1;
    int x2, y2 ;
    for (int i=0;i<h2;i++) {
        for (int j=0;j<w2;j++) {
            x2 = ((j*x_ratio)>>16) ;
            y2 = ((i*y_ratio)>>16) ;
            imageOut->setPixel(j,i,imageIn->pixel(x2,y2));
            //temp[(i*w2)+j] = pixels[(y2*w1)+x2] ;
        }                
    }
    
    //imageOut->save("zoomed.jpg");
    outil->setImageTraite(imageOut); 
}