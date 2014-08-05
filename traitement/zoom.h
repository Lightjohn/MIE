/* 
 * File:   zoom.h
 * Author: light
 *
 * Created on 5 janvier 2012, 17:44
 */

#ifndef ZOOM_H
#define	ZOOM_H
#include "outils.h"

class zoom {
public:
    zoom(outils *o);
    virtual ~zoom();
    void zoomPlus();
    void zoomMoin();
    void zoomer(int a);
    void reiinitZoom();
    void zoomViaFacteur();
    void redim(int xout, int yout);
private:
    qreal coef;
    outils *outil;
    int heightOriginal;
    int widthOriginal;
    QImage *imageIn;
    QImage *imageOut;
    int heightOutPrec;
    int widthOutPrec;

};

#endif	/* ZOOM_H */

