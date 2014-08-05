
/* 
 * File:   Global.h
 * Author: light
 *
 * Created on 3 janvier 2012, 16:14
 */

#ifndef OUTILS_H
#define	OUTILS_H
#include <QtGui>
#include <QtGui/QPixmap>
#include "QGraphicsProxyWidget"
#include "iostream"
#include "stdio.h"
#include <string>
#include "QStatusBar"
#include "QLabel"
#include "QGraphicsRectItem"
#include "QGraphicsScene"
#include "QStack"
#include "QClipboard"
#include "interface/customqgraphicsproxywidget.h"

#include "traitement/cases.h"
#include <list>

class fusion;
class position{
public:
    position(int x, int y);
    int x;
    int y;
};
class outils{
public:
    
    QAction *actionAnnul;
    QAction *actionRef;
    QPushButton *annulBouton;
    QPushButton *refaireBouton;

    outils(QClipboard *cp);
    void ouvrir_image_memoire(QString chemin);
    int getHeight();
    QImage *getImage();
    void setImage(QImage *im);
    void setImage2(QImage *im);
    QImage* getImage_init();
    int getWidth();
    void getPixel( int, int, int*,int*, int*, int*);
    void rgbToYuv(int*,int*, int*);
    void yuvToRgb(int*,int*, int*);
    void supression_cadre_selection();
    
    void init_podium(int nb_places,int taille_chem);
    void delete_podium();
    void add_podium(int* chem,int poids);
    int* get_podium();
    int* maj_podium_del(int *chemin_de_base_qui_va_decaller_les_autres);
    int* maj_podium_add(int *chemin_de_base_qui_va_decaller_les_autres);
    void get_deb_chem(int* tab);
    void chem_suivant(int nb_chem);
    void chem_precedent(int nb_chem);
    int min(int,int);
    void podium_backup();
    void podium_recup();
    
    
    int nombre_chemin(int hauteur, int largeur, int nb_chem);
    void annuler();
    void refaire();
    void ajouterAnnuler(QImage *im);


    void zoom();
    qreal getZoomFactor();
    void setZoomFactor(qreal a);

    void copier();
    int coller();
    void couper();

    bool checkBoxSelection;
    bool checkBoxCiseau;
    int ciseauX;
    int ciseauY;
    std::list<position> pixel;
    
    int makeRGB(int red, int green, int blue, int alpha);
    QImage* getImageTraite();
    void setImageTraite(QImage *imageTraite);
    QStack<QImage> getUndo();
    QStack<QImage> getRedo();
    QImage* getImageZoomee();
    QImage* getImageTraiteeZoomee();
    void setImageZoomee(QImage *im);
    
    void setImageGradient(QImage *image);
    QImage* getImageGradient();
    bool bool_image_gradient;
    
    void saveImage(QString a);
    
    int val_champ_largeur;
    int val_champ_hauteur;


    int* chem_parcours_grad;


    bool copieActivee;
    QClipboard *cp;

    customQGraphicsProxyWidget *fg;
    customQGraphicsProxyWidget *bg;
    /*********** Variable Adri -> ON TOUCHE PAS !!!!! **************/
    
    QGraphicsSimpleTextItem *simpletext1; //position sur x
    QGraphicsSimpleTextItem *simpletext2; //y
    QGraphicsRectItem *rectitem_selection; 
    QGraphicsRectItem *rectitem_taille_selection; 
    
    QRect *rect_selection; //rectangle de la selection lorsque le click est relache
  


    QGraphicsScene *scene;

    QGraphicsScene *scene_ap;

    QLabel *lab_picture; //label qui contient la picture
    QLabel *lab_picturefg;
    bool rectangleSelectionActive; //si l'on as cliqué sur la selection
    bool bool_pressed;  //si le click est enfonce mais pas relache
    bool bool_deplacement;
    bool bool_release;
    
    int pos_press_x;    //recup la position lorsque le click est pressé pour la selection
    int pos_press_y;
    int pos_release_x;    //pareil pour le release click
    int pos_release_y;
    
    QLabel *lab_r;      //valeurs de la toolbar
    QLabel *lab_v;
    QLabel *lab_b;
    QLabel *lab_x;
    QLabel *lab_y;
    
    int dpl_x; //deplacement de la souris 
    int dpl_y;
    
    int nombre_appel_move;
    
    int dpl_x_contain;//deplacement du cadre de selection
    int dpl_y_contain;
    
    int rec_x;
    int rec_y;
    
    int check_redim;
    int **matrix;
    
    QRect *rect_image;

    int mat_w;
    int mat_h;
    int check_intelligent;
    int ciseauSeuil;
    
    /*************************************************************/
    QImage* getImageFg();
    void setImageFg(QImage *fg);
    virtual ~outils();
    
    //défini si on utilise des image temp

    bool decoupagePossible;
    bool imageTemp;
    int utiliserRGB;
    bool redimensionnement;
    
    void reinitCiseau();
    /***********************************/
    /* Variables pour la liste chainee */ 
    /*    ATTENTION, c'est du lourd    */ 
    /*                                 */ 
    /***********************************/
    
    cases **matrice_case;
    cases **matrice_save;
    int matrice_w;
    int matrice_h;
    
    cases ***matrice_tab;
    int matrice_tab_w;
    int matrice_tab_h;
    
    void init_matrice_case();
    cases *get_case(int x, int y);
    cases *_get_cases(int x, int y);
    void getPixelGradient(int x, int y, int *r,int *g, int *b, int *aa);
    
    /************************************/
    
private:
    QImage *image; // image traitee
    QImage *image_init; // image non traitee
    //QImage image_copie; //copie d'image
    QImage *imageZoomee;
    QImage *imageGradient;
    QImage *imageTraite;
    QImage *imageTraiteZoomee;
    QImage *imagefg;

    int width;
    int height;
    int podium_l;
    int podium_h;
    int **podium;
    int **podium_base;
    
    int** matrix_base;
    
    int nb_chem;
    int chemin_parcour_actuel;
    
    int* somme_col;

    QStack<QImage> undo;
    QStack<QImage> redo;

    qreal zoomFactor;

};

#endif	/* OUTILS_H */
