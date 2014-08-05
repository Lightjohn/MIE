/*
 * File:   fenetrePrincipale.h
 * Author: Adri
 *
 * Created on 3 janvier 2012, 15:52
 */

#ifndef FENETREPRINCIPALE_H
#define	FENETREPRINCIPALE_H

#include <QtGui>
#include "outils.h"
#include "fenetrePrincipale.h"
#include "interface/customgraphicsrectitem.h"
#include "traitement/NiveauDeGris.h"
#include "traitement/zoom.h"
#include "traitement/rognage.h"
#include "traitement/fusion.h"
#include "traitement/zoom.h"
#include "traitement/gradient.h"
#include "traitement/wrapertraitement.h"
#include "traitement/histogramme.h"
#include "traitement/ciseau.h"

#include <iostream>
#include "QtAlgorithms"
#include <QtCore/qstring.h>
#include "stdio.h"




using namespace std;

class customGraphicsView;

class fenetrePrincipale : public QMainWindow {
    Q_OBJECT
public:
    fenetrePrincipale(outils *stockage);
    virtual ~fenetrePrincipale();

    outils *tool;
    
    QMenu *menuAffichage;
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuImage;
    QMenu *menuFiltre;
    QMenu *menuPresentation;
  
    QMenu *menuSauver;
    
    QAction *sauver;

    QAction *actionYuv;
    QAction *actionOuvrir;
    QAction *actionAnnuler;
    QAction *actionRefaire;
    QAction *actionCopier;
    QAction *actionCouper;
    QAction *actionColler;
    QAction *actionAjuster;
    QAction *actionSuppr;
    
    QAction *gris;

    
    QGraphicsScene *scene;
    QGraphicsScene *scene_ap;
    
    QLabel *lab_image;
    QLabel *lab_imagefg;
    
    QGraphicsScene *sceneHisto;
    QGraphicsView *viewHisto;
  
    customGraphicsView *view;
    
    QDockWidget *dock_option;
    QDockWidget *palette_outil;
    QDockWidget *palette_etat;
    
    QString *chem_image;
    QString *chem_imagefg;
    
    customQGraphicsProxyWidget *proxy;
    customQGraphicsProxyWidget *proxyfg;
    
    QGraphicsPixmapItem *pixmapitem;
    
    QPushButton *rogner_func;
    QPushButton *fairefusionner;

    QVBoxLayout *layout_selection;
   // QVBoxLayout *layout_filtre;
    QVBoxLayout *layout_fusion;
    QVBoxLayout *layout_histogramme;
    QToolBar *bar_outils;
    QGridLayout *layout_ciseau;
    QGridLayout *layout_redim;

    QLabel *histoClarte;
    QSlider *slider_clarte;
    QLabel *histoContraste;
    QSlider *slider_contraste1;
    QSlider *slider_contraste2;
    QLabel *histoIndiv;
    QSlider *slider_r;
    QSlider *slider_g;
    QSlider *slider_b;
    QCheckBox *yuvBox;
    

    QAction *moyenne;
    QAction *rehausseur;
    QAction *passebas;
    QAction *rehausse_contraste;
    QAction *detectBord;
    QAction *but_gradientX;
    QAction *but_gradientY;
    QAction *customFiltre;

    QPushButton *undo_button;
    QPushButton *redo_button;
    
    QCheckBox *redim_intel;
    QLabel *lab_largeur;
    QLabel *lab_hauteur;
    QSlider *slider_redim_largeur;
    QSlider *slider_redim_hauteur;
    
    QSlider *slideFusionimg1;
    QSlider *slideFusionimg2;
    
    QToolBar *toolbar;
    
    QWidget *contener_fonct_filtre;
    QWidget *contener_fonct_histo;
    QWidget *contener_fonct_selection;
    QWidget *contener_fonct_fusion;
    QWidget *contener_fonct_filtrage;
    QWidget *contener_fonct_redim;
    QWidget *contener_fonct_ciseau;
    
    QLineEdit *champ_largeur;
    QLineEdit *champ_hauteur;
     
    QPushButton *boutonAnnulerCiseau;
    QPushButton *boutonAccepterCiseau;
    QPushButton *boutonAnnulerHisto;
    QPushButton *boutonAccepterHisto;
    QPushButton *boutonAnnulerRedim;
    QPushButton *boutonAccepterRedim;
    QPushButton *boutonAnnulerCrop;
    QPushButton *boutonAccepterCrop;
    
    QLabel *lab_r;
    QLabel *lab_v;
    QLabel *lab_b;
    QLabel *lab_x;
    QLabel *lab_y;
    
    QLabel *ciseauSensibilite;
    QSlider *ciseauSlider;
    
    QPushButton *select;
    QPushButton *ciseauBox;
    QPushButton *rectangle;

    QPushButton *zoom_p;
    QPushButton *zoom_m;
    QPushButton *fus;
    QPushButton *histogrammeBouton;
    QPushButton *redimention;
    
    QGraphicsView *view_ap;

    QImage *image_depart;
    
    QImage *imagefg;
    int alphafg;

    //================
    QWidget *dialog;
    QPushButton *ok;
    QPushButton *cancel;

    QSpinBox *sb0;
    QSpinBox *sb1;
    QSpinBox *sb2;
    QSpinBox *sb3;
    QSpinBox *sb4;
    QSpinBox *sb5;
    QSpinBox *sb6;
    QSpinBox *sb7;
    QSpinBox *sb8;


    //============

private:
    wraperTraitement *wrapper;
    histogramme *histo;
    zoom *zoomi;
    int choixFichier;
    int recup_chemin();
    void refreshHisto();
    void recup_cheminfg();
    fusion *outilfusion;
    gradient *grad;

    int contraste1;
    int contraste2;
    int histR;
    int histG;
    int histB;
    double ratio; //ratio largeur/hauteur


public slots:

    void nod();
    void ouvrir_image();//a=0: ouvre image, a>=1 sauvegarde dans différents formats
    void save();

    void traitement_niveau_gris();
    void zoom_plus();
    void zoom_moins();
    void traitement_flou();
    void faireRectangle();
    void traitement_rognage();
    void undo();
    void redo();
    void updateImageAffiche();
    void activerSelection(bool b);
    void activerCiseau();
    void actionfusion();
    void accepter();
    void annuler();
    void fusionner();
    void copier();
    void coller();
    void supprimer();
    void couper();
    void ajuster();
    void histogrammee();
    void histoSliderClarte(int a);
    void histoSliderContraste1(int a);
    void histoSliderContraste2(int a);
    void histoSliderR(int a);
    void histoSliderG(int a);
    void histoSliderB(int a);
    void fusionSliderImage1(int a);
    void fusionSliderImage2(int a);
    void filtrageMoyenne();
    void filtrageRehausseur();
    void filtrageContraste();
    void filtrageDetection();
    void filtrageGradientX();
    void filtrageGradientY();
    void customFiltrage();
    void traitement_redimension();
    //sans doute a supprime
    void redim_f();
    //fin
    void maj_largeur(const QString&);
    void maj_hauteur(const QString&);
    void slider_ciseau(int);
    void slider_largeur(int);
    void slider_hauteur(int);
    void utiliserYUV(int);
    void redimIntelligent(int etat);
    void passageMenuYuv();
};

#endif	/* FENETREPRINCIPALE_H */

