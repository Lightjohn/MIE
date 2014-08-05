/*
 * File:   main.cpp
 * Author: Adri
 *
 * Created on 3 janvier 2012, 15:02
 */

#include "QtGui"
#include <QtGui/qimage.h>
#include <QtGui/qpixmap.h>
#include "outils.h"
#include "interface/fenetrePrincipale.h"
#include "traitement/zoom.h"
#include "traitement/histogramme.h"

/**/
int main(int argc, char *argv[]) {
    //    
        QApplication app(argc, argv);
        QClipboard *cp=app.clipboard();

        outils *sto = new outils(cp);

        fenetrePrincipale fen(sto);
        fen.show();
        return app.exec();




    //      outils *sto = new outils();
    //    //QApplication app(argc, argv);
    //      sto->ouvrir_image_memoire("lala.jpg");
    //      histogramme hi(sto);
    //      hi.calculHistogramme(1);
    //    //hi.modifHistogrammeClarte(50);
    //      hi.modifHistogrammeContraste(100,255);
    //      //hi.modifHistogrammeClarteIndiv(0,-255,0);
    ////    QGraphicsScene *scene = hi.getHistogrammes();
    ////    QGraphicsView * view = new QGraphicsView(scene);
    ////    view->show();
    //     sto->saveImage("lala_histo.jpg");
    //    //return app.exec();
    //    //exit(0);


//    outils *sto = new outils();
//    sto->ouvrir_image_memoire("lala.jpg");
//    wraperTraitement wra(sto);
//    wra.conv(3,NOYAU_REHAUSSEMENT);
//    sto->saveImage("lala_rehauss.jpg");
//    exit(0);
        
//        outils *sto = new outils();
//        sto->ouvrir_image_memoire("image/lala3.jpg");
//        zoom zoomi(sto);
//        zoomi.redim(1000,500);
//        exit(0);
}


