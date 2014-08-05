/*
 * File:   fenetrePrincipale.cpp
 * Author: Adri
 * 
 * Created on 3 janvier 2012, 15:52
 */




#include <QtCore/qnamespace.h>

#include "fenetrePrincipale.h"
#include "interface/customGraphicsView.h"

fenetrePrincipale::fenetrePrincipale(outils *tool) {

   // tool->setNiveauZoom(1);
//   qApp->setStyleSheet( "QPushButton { background-color: red; }");
//     background-color: red;
//     border-style: outset;
//     border-width: 2px;
//     border-radius: 10px;
//     border-color: beige;
//     font: bold 14px;
//     min-width: 10em;
//     padding: 6px;
// }
// QPushButton#evilButton:pressed {
//     background-color: rgb(224, 0, 0);
//     border-style: inset;
// }");

    this->setMaximumSize(QApplication::desktop()->width(),QApplication::desktop()->height());
    this->setWindowTitle("Retouche d'image");
    this->tool = tool;
    grad = new gradient(this->tool);
    
    //création de la barre des menus
    menuFichier = menuBar()->addMenu("Fichier");
    menuEdition = menuBar()->addMenu("Edition");

    menuFiltre = menuBar()->addMenu("Filtre");
    menuPresentation = menuBar()->addMenu("Affichage");
    

    sauver = menuFichier->addAction("Enregistrer Sous");

    actionYuv = menuPresentation->addAction("Affichage en YUV");



    actionOuvrir = menuFichier->addAction("&Ouvrir");
    actionOuvrir->setShortcut(QKeySequence("o"));

    actionAnnuler=menuEdition->addAction("Annuler");
    actionAnnuler->setShortcut(QKeySequence("CTRL+Z"));



    actionRefaire=menuEdition->addAction("Refaire");
    actionRefaire->setShortcut(QKeySequence("CTRL+Y"));


    //menu filtre
    gris = menuFiltre->addAction("Noir et blanc");
    moyenne = menuFiltre->addAction("Flou");
    rehausse_contraste = menuFiltre->addAction("Rehaussement contraste");
    detectBord = menuFiltre->addAction("Detection des bords");
    but_gradientX = menuFiltre->addAction("GradientX");
    but_gradientY = menuFiltre->addAction("GradientY");
    customFiltre=menuFiltre->addAction("Filtre personnalise...");
    
    
    tool->actionAnnul=actionAnnuler;
    tool->actionRef=actionRefaire;

    actionAnnuler->setEnabled(false);
    actionRefaire->setEnabled(false);
    
    actionCopier=menuEdition->addAction("Copier");
    actionCopier->setShortcut(QKeySequence("CTRL+C"));

    actionCouper=menuEdition->addAction("Couper");
    actionCouper->setShortcut(QKeySequence("CTRL+X"));

    actionColler=menuEdition->addAction("Coller");
    actionColler->setShortcut(QKeySequence("CTRL+V"));

    actionSuppr=menuEdition->addAction("Supprimer");
    actionSuppr->setShortcut(QKeySequence("DEL"));

    // Creation de la palette de fonctions

    dock_option = new QDockWidget("Options de traitement", this);
    dock_option->hide();
    dock_option->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::RightDockWidgetArea, dock_option);

    contener_fonct_filtre = new QWidget;
    contener_fonct_histo = new QWidget;
    contener_fonct_selection = new QWidget;
    contener_fonct_fusion=new QWidget;
    contener_fonct_redim = new QWidget;
    contener_fonct_ciseau = new QWidget;

    //Bouton presents dans plusieurs fonctions
    boutonAnnulerCiseau = new QPushButton("");
    boutonAnnulerCiseau->setIcon((const QIcon &)QIcon("icones/no.png"));
    boutonAccepterCiseau = new QPushButton("");
    boutonAccepterCiseau->setIcon((const QIcon &)QIcon("icones/yes.png"));
    boutonAnnulerHisto = new QPushButton("");
    boutonAnnulerHisto->setIcon((const QIcon &)QIcon("icones/no.png"));
    boutonAccepterHisto = new QPushButton("");
    boutonAccepterHisto->setIcon((const QIcon &)QIcon("icones/yes.png"));
    boutonAnnulerRedim = new QPushButton("");
    boutonAnnulerRedim->setIcon((const QIcon &)QIcon("icones/no.png"));
    boutonAccepterRedim = new QPushButton("");
    boutonAccepterRedim->setIcon((const QIcon &)QIcon("icones/yes.png"));
    boutonAnnulerCrop = new QPushButton("");
    boutonAnnulerCrop->setIcon((const QIcon &)QIcon("icones/no.png"));
    boutonAccepterCrop = new QPushButton("");
    boutonAccepterCrop->setIcon((const QIcon &)QIcon("icones/yes.png"));
    
    // Creation de la palette d'outils
  //  palette_outil = new QDockWidget("Palette d'outils", this);
   // palette_outil->setFeatures(QDockWidget::NoDockWidgetFeatures);
  //  addDockWidget(Qt::LeftDockWidgetArea, palette_outil);

  //  QWidget *contener_outil = new QWidget;
 //   palette_outil->setWidget(contener_outil);
    
    //bouton de la palette d'outils

    select=new QPushButton("");
    select->setCheckable(true);
    select->setIcon((const QIcon &)QIcon("icones/selection.png"));
    select->setToolTip("Selection de l'image");
    ciseauBox=new QPushButton("");
    ciseauBox->setIcon((const QIcon &)QIcon("icones/ciseau2.png"));
    ciseauBox->setToolTip("Decoupage Intelligent");
    rectangle = new QPushButton("");
    rectangle->setIcon((const QIcon &)QIcon("icones/rectangle.png"));
    rectangle->setToolTip("Rectangle de selection");

    zoom_p = new QPushButton("");
    zoom_p->setIcon((const QIcon &)QIcon("icones/zoomp.png"));
    zoom_m = new QPushButton("");
    zoom_m->setIcon((const QIcon &)QIcon("icones/zoomm.png"));
    undo_button=new QPushButton("");
    undo_button->setIcon((const QIcon &)QIcon("icones/undo.png"));
    redo_button=new QPushButton("");
    redo_button->setIcon((const QIcon &)QIcon("icones/redo.png"));
    undo_button->setEnabled(false);
    redo_button->setEnabled(false);
    tool->annulBouton=undo_button;
    tool->refaireBouton=redo_button;

    fus=new QPushButton("");
    fus->setIcon((const QIcon &)QIcon("icones/fusion.png"));
    fus->setToolTip("Ajouter une image a fusionner");
    histogrammeBouton = new QPushButton("");
    histogrammeBouton->setIcon((const QIcon &)QIcon("icones/histo.png"));
    histogrammeBouton->setToolTip("Histogrammes de couleurs");
    redimention = new QPushButton("");
    redimention->setIcon((const QIcon &)QIcon("icones/resizing.png"));
    redimention->setToolTip("Redimentionnement");
    //layout de la palette d'outil
    bar_outils = new QToolBar("Palette");
    addToolBar(Qt::LeftToolBarArea,bar_outils);
    bar_outils->addWidget(select);
    bar_outils->addWidget(ciseauBox);
    bar_outils->addWidget(rectangle);

    bar_outils->addWidget(fus);
    bar_outils->addWidget(histogrammeBouton);
    bar_outils->addWidget(redimention);
    bar_outils->addSeparator();


    //contener_outil->setLayout(layout_outils);

    //interface palette de fonction
    layout_selection = new QVBoxLayout;

    layout_fusion=new QVBoxLayout;
    layout_histogramme = new QVBoxLayout; 
    layout_ciseau = new QGridLayout;
    layout_redim = new QGridLayout;

    //interface palette histogramme
    histoClarte = new QLabel("Clarte");
    slider_clarte = new QSlider(Qt::Horizontal);
    histoContraste = new QLabel("Contraste");
    slider_contraste1 = new QSlider(Qt::Horizontal);
    slider_contraste2 = new QSlider(Qt::Horizontal);
    histoIndiv = new QLabel("Reglage RGB");
    slider_r = new QSlider(Qt::Horizontal);
    slider_g = new QSlider(Qt::Horizontal);
    slider_b = new QSlider(Qt::Horizontal);
    
    slider_b->setRange(-255,255);
    slider_clarte->setRange(-255,255);
    slider_clarte->setSliderPosition(0);
    slider_contraste1->setRange(0,255);
    slider_contraste2->setRange(0,255);
    slider_contraste2->setSliderPosition(255);
    slider_r->setRange(-255,255);
    slider_g->setRange(-255,255);
    yuvBox = new QCheckBox("YUV");
    
    //interface filtrage

    /*moyenne = new QAction;
    rehausseur = new QAction;
    passebas = new QAction;
    rehausse_contraste = new QAction;
    detectBord = new QAction;
    but_gradient = new QAction;*/

    

    /*moyenne=menuFiltre->addAction("Flou");
    rehausseur=menuFiltre->addAction("Rehaussement");
    passebas=menuFiltre->addAction("Passe-bas");
    rehausse_contraste=menuFiltre->addAction("Rehaussement de contraste");
    detectBord=menuFiltre->addAction("Detection des bords");*/
    //but_gradient=menuFiltre->addAction("Gradient");


    //interface redimentionnement
    
    redim_intel = new QCheckBox("Redimensionnement\n intelligent");
    lab_largeur = new QLabel("Largeur : ");
    lab_hauteur = new QLabel("Hauteur : ");
    slider_redim_hauteur = new QSlider(Qt::Horizontal);
    slider_redim_largeur = new QSlider(Qt::Horizontal);
    
    champ_largeur = new QLineEdit();
    champ_hauteur = new QLineEdit();
    
    layout_redim->addWidget(lab_largeur,0,0);
    layout_redim->addWidget(champ_largeur,0,1);
    layout_redim->addWidget(slider_redim_largeur,1,0,1,2);
    layout_redim->addWidget(lab_hauteur,2,0);
    layout_redim->addWidget(champ_hauteur,2,1);
    layout_redim->addWidget(slider_redim_hauteur,3,0,1,2);
    layout_redim->addWidget(redim_intel,5,0,1,2);
    layout_redim->addWidget(boutonAnnulerRedim,6,0);
    layout_redim->addWidget(boutonAccepterRedim,6,1);
    
    //interface rognage lol
    rogner_func = new QPushButton("");
    rogner_func->setIcon((const QIcon &)QIcon("icones/crop.png"));
    rogner_func->setToolTip("Rogner");
    layout_selection->addWidget(rogner_func);
    layout_selection->addWidget(boutonAccepterCrop);
    layout_selection->addWidget(boutonAnnulerCrop);

    
    //interface ciseau
    ciseauSensibilite = new QLabel("            Sensibilite");
    ciseauSlider = new QSlider(Qt::Horizontal);
    ciseauSlider->setRange(1,100);
    
    layout_ciseau->addWidget(ciseauSensibilite,0,0,0,2);
    layout_ciseau->addWidget(ciseauSlider,1,0,1,2);
    layout_ciseau->addWidget(boutonAnnulerCiseau,2,0);
    layout_ciseau->addWidget(boutonAccepterCiseau,2,1);
    
    //interface fusion
    fairefusionner=new QPushButton("Fusionner");
    
    slideFusionimg1 = new QSlider(Qt::Horizontal);
    slideFusionimg2 = new QSlider(Qt::Horizontal);

    
    slideFusionimg1->setRange(0,255);
    slideFusionimg2->setRange(0,255);
    slideFusionimg2->setSliderPosition(255);
    slideFusionimg1->setSliderPosition(255);
    
    layout_fusion->addWidget(fairefusionner);
    layout_fusion->addWidget(slideFusionimg1);
    layout_fusion->addWidget(slideFusionimg2);
    
   // contener_fonct_filtre->setLayout(layout_filtre);
    contener_fonct_selection->setLayout(layout_selection);
    contener_fonct_fusion->setLayout(layout_fusion);
    contener_fonct_histo->setLayout(layout_histogramme);
    contener_fonct_redim->setLayout(layout_redim);
    contener_fonct_ciseau->setLayout(layout_ciseau);
        

    //interface palette d'etat(QToolBar)

    
    lab_r = new QLabel("<font color=\"#FF0000\">R : </font>");
    lab_v = new QLabel("<font color=\"#419F2E\">V : </font>");
    lab_b = new QLabel("<font color=\"#0000FF\">B : </font>");
    lab_x = new QLabel("X :      ");
    lab_y = new QLabel("Y :      ");
    
    scene_ap = new QGraphicsScene;
    view_ap = new QGraphicsView(scene_ap);
    
    tool->scene_ap = scene_ap;
    toolbar=new QToolBar("Barre d'outils");
    addToolBar(Qt::BottomToolBarArea,toolbar);
    toolbar->addWidget(lab_x);
    toolbar->addWidget(lab_y);
    toolbar->addSeparator();
    toolbar->addWidget(lab_r);
    toolbar->addWidget(lab_v);
    toolbar->addWidget(lab_b);
    toolbar->addWidget(view_ap);
    toolbar->addSeparator();
    toolbar->addWidget(undo_button);
    toolbar->addWidget(redo_button);
    toolbar->addSeparator();
    toolbar->addWidget(zoom_m);
    toolbar->addWidget(zoom_p);


    lab_x->setFixedWidth(60);
    lab_y->setFixedWidth(60);
    lab_r->setFixedWidth(50);
    lab_v->setFixedWidth(50);
    lab_b->setFixedWidth(50);
    view_ap->setFixedSize(30,30);
    toolbar->setFixedHeight(40);

    tool->lab_r = lab_r;
    tool->lab_v = lab_v;
    tool->lab_b = lab_b;
    tool->lab_x = lab_x;
    tool->lab_y = lab_y;
    
    //creation zone de dessin

    scene = new QGraphicsScene;
    scene->setForegroundBrush(QColor(0,0,0,0));
    scene->setBackgroundBrush(QColor(0,0,0,0));
    tool->scene = scene;

    view = new customGraphicsView(scene,this,tool);


    lab_image = new QLabel();
    lab_image->setStyleSheet("background-color: rgba(0, 0, 0, 0)");
    

    lab_imagefg=new QLabel();


    proxy = new customQGraphicsProxyWidget(lab_image);
    proxyfg=new customQGraphicsProxyWidget(lab_imagefg);
    proxyfg->setVisible(false);





    scene->addItem(proxy);
    scene->addItem(proxyfg);

    proxyfg->autre=proxy;
    proxy->autre=proxyfg;

    tool->bg =proxy;
    tool->fg=proxyfg;

    setCentralWidget(view);



    chem_image = new QString("");   //pour toi alex modifie ici pour recup l'image de base



    tool->ouvrir_image_memoire(*chem_image);
    
    updateImageAffiche();

    QObject::connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(ouvrir_image()));
    QObject::connect(actionAnnuler,SIGNAL(triggered()),this,SLOT(undo()));
    QObject::connect(actionRefaire,SIGNAL(triggered()),this,SLOT(redo()));
    QObject::connect(undo_button,SIGNAL(clicked()),this,SLOT(undo()));
    QObject::connect(redo_button,SIGNAL(clicked()),this,SLOT(redo()));

    QObject::connect(actionCopier,SIGNAL(triggered()),this,SLOT(copier()));
    QObject::connect(actionColler,SIGNAL(triggered()),this,SLOT(coller()));
    QObject::connect(actionCouper,SIGNAL(triggered()),this,SLOT(couper()));
    QObject::connect(actionSuppr,SIGNAL(triggered()),this,SLOT(supprimer()));

    
    QObject::connect(ciseauBox,SIGNAL(clicked()),this,SLOT(activerCiseau()));
    QObject::connect(select,SIGNAL(toggled(bool)),this,SLOT(activerSelection(bool)));
    
    QObject::connect(zoom_p, SIGNAL(clicked()), this, SLOT(zoom_plus()));
    QObject::connect(zoom_m, SIGNAL(clicked()), this, SLOT(zoom_moins()));
    //QObject::connect(flou,   SIGNAL(clicked()), this, SLOT(traitement_flou()));
    QObject::connect(rectangle, SIGNAL(clicked()), this, SLOT(faireRectangle()));
    QObject::connect(histogrammeBouton, SIGNAL(clicked()), this, SLOT(histogrammee()));
    QObject::connect(redimention, SIGNAL(clicked()), this, SLOT(traitement_redimension()));
    
    //menu filtre
    QObject::connect(moyenne, SIGNAL(triggered()), this, SLOT(filtrageMoyenne()));
    QObject::connect(gris,   SIGNAL(triggered()), this, SLOT(traitement_niveau_gris()));
    QObject::connect(rehausse_contraste, SIGNAL(triggered()), this, SLOT(filtrageContraste()));
    QObject::connect(detectBord, SIGNAL(triggered()), this, SLOT(filtrageDetection()));
    QObject::connect(but_gradientX, SIGNAL(triggered()), this, SLOT(filtrageGradientX()));
    QObject::connect(but_gradientY, SIGNAL(triggered()), this, SLOT(filtrageGradientY()));
    QObject::connect(customFiltre,SIGNAL(triggered()),this,SLOT(customFiltrage()));
    
    QObject::connect(rogner_func, SIGNAL(clicked()), this, SLOT(traitement_rognage()));
    QObject::connect(sauver, SIGNAL(triggered()), this, SLOT(save()));
    QObject::connect(actionYuv, SIGNAL(triggered()), this, SLOT(passageMenuYuv()));    
    


    QObject::connect(fus, SIGNAL(clicked()), this, SLOT(actionfusion()));
    QObject::connect(fairefusionner, SIGNAL(clicked()), this, SLOT(fusionner()));
    
    //john On
    QObject::connect(slider_clarte, SIGNAL(valueChanged(int)), this, SLOT(histoSliderClarte(int)));
    QObject::connect(slider_contraste1, SIGNAL(valueChanged(int)), this, SLOT(histoSliderContraste1(int)));
    QObject::connect(slider_contraste2, SIGNAL(valueChanged(int)), this, SLOT(histoSliderContraste2(int)));
    QObject::connect(slider_r, SIGNAL(valueChanged(int)), this, SLOT(histoSliderR(int)));
    QObject::connect(slider_g, SIGNAL(valueChanged(int)), this, SLOT(histoSliderG(int)));
    QObject::connect(slider_b, SIGNAL(valueChanged(int)), this, SLOT(histoSliderB(int)));
    QObject::connect(yuvBox, SIGNAL(stateChanged(int)), this, SLOT(utiliserYUV(int)));
    
    QObject::connect(ciseauSlider, SIGNAL(valueChanged(int)), this, SLOT(slider_ciseau(int)));
    //John Off
    QObject::connect(slideFusionimg1, SIGNAL(valueChanged(int)), this, SLOT(fusionSliderImage1(int)));
    QObject::connect(slideFusionimg2, SIGNAL(valueChanged(int)), this, SLOT(fusionSliderImage2(int)));
    
    
    //QObject::connect(rehausseur, SIGNAL(clicked()), this, SLOT(filtrageRehausseur()));

    
    
    QObject::connect(redim_intel ,SIGNAL(stateChanged(int)), this, SLOT(redimIntelligent(int)));

    QObject::connect(champ_largeur, SIGNAL(textEdited(const QString&)), this, SLOT(maj_largeur(const QString&)));
    QObject::connect(champ_hauteur, SIGNAL(textEdited(const QString&)), this, SLOT(maj_hauteur(const QString&)));
    QObject::connect(slider_redim_largeur, SIGNAL(valueChanged(int)), this, SLOT(slider_largeur(int)));
    QObject::connect(slider_redim_hauteur, SIGNAL(valueChanged(int)), this, SLOT(slider_hauteur(int)));
    
    QObject::connect(boutonAccepterCiseau, SIGNAL(clicked()), this, SLOT(accepter()));
    QObject::connect(boutonAnnulerCiseau, SIGNAL(clicked()), this, SLOT(annuler()));
    QObject::connect(boutonAccepterHisto, SIGNAL(clicked()), this, SLOT(accepter()));
    QObject::connect(boutonAnnulerHisto, SIGNAL(clicked()), this, SLOT(annuler()));
    QObject::connect(boutonAccepterRedim, SIGNAL(clicked()), this, SLOT(accepter()));
    QObject::connect(boutonAnnulerRedim, SIGNAL(clicked()), this, SLOT(annuler()));
    QObject::connect(boutonAccepterCrop, SIGNAL(clicked()), this, SLOT(accepter()));
    QObject::connect(boutonAnnulerCrop, SIGNAL(clicked()), this, SLOT(annuler()));




    histo = new histogramme(this->tool); 
    zoomi = new zoom(tool);

    contraste1=0;
    contraste2=255;
    histR=0;
    histG=0;
    histB=0;
    
    
    //john On
    histo->calculHistogramme(tool->utiliserRGB);
    sceneHisto = histo->getHistogrammes(3,1,18);
    viewHisto = new QGraphicsView(sceneHisto);
    layout_histogramme->addWidget(viewHisto);
    layout_histogramme->addWidget(histoClarte);
    layout_histogramme->addWidget(slider_clarte);
    layout_histogramme->addWidget(histoContraste);
    layout_histogramme->addWidget(slider_contraste1);
    layout_histogramme->addWidget(slider_contraste2);
    layout_histogramme->addWidget(histoIndiv);
    layout_histogramme->addWidget(slider_r);
    layout_histogramme->addWidget(slider_g);
    layout_histogramme->addWidget(slider_b);
    layout_histogramme->addWidget(yuvBox);
    layout_histogramme->addWidget(boutonAnnulerHisto);
    layout_histogramme->addWidget(boutonAccepterHisto);
    //John off
    
    wrapper =new wraperTraitement(tool);

    /*plein ecran, raz le cul d'avoir une miniature a redimensionner a chaque fois.*/
    //this->showMaximized();

}
void fenetrePrincipale::nod(){
    int aa1,aa2,aa3,aa4,aa5,aa6,aa7,aa8,aa9;
    aa1=sb0->text().toInt();

    aa2=sb1->text().toInt();

    aa3=sb2->text().toInt();

    aa4=sb3->text().toInt();

    aa5=sb4->text().toInt();

    aa6=sb5->text().toInt();

    aa7=sb6->text().toInt();

    aa8=sb7->text().toInt();

    aa9=sb8->text().toInt();

    wrapper->a1=aa1;
    wrapper->a2=aa2;
    wrapper->a3=aa3;
    wrapper->a4=aa4;
    wrapper->a5=aa5;
    wrapper->a6=aa6;
    wrapper->a7=aa7;
    wrapper->a8=aa8;
    wrapper->a9=aa9;



    dialog->close();

    wrapper->conv(3,NOYAU_PERSONNALISE);


    updateImageAffiche();
}

void fenetrePrincipale::customFiltrage(){
    dialog=new QWidget;
    dialog->setWindowTitle("Informations necessaires");
    dialog->setGeometry(400,400,300,150);
    QVBoxLayout *mainLayout=new QVBoxLayout;
    QGridLayout *font=new QGridLayout;
    QGroupBox *groupBox = new QGroupBox("Noyau a utiliser", dialog);
    sb0=new QSpinBox;
    sb0->setValue(1);

    sb0->setRange(-99,99);

    sb1=new QSpinBox;
    sb1->setValue(1);

     sb1->setRange(-99,99);

    sb2=new QSpinBox;
    sb2->setValue(1);

     sb2->setRange(-99,99);

    sb3=new QSpinBox;
    sb3->setValue(1);

     sb3->setRange(-99,99);

    sb4=new QSpinBox;
    sb4->setValue(1);

     sb4->setRange(-99,99);

    sb5=new QSpinBox;
    sb5->setValue(1);

     sb5->setRange(-99,99);

    sb6=new QSpinBox;
    sb6->setValue(1);

     sb6->setRange(-99,99);

    sb7=new QSpinBox;
    sb7->setValue(1);

     sb7->setRange(-99,99);

    sb8=new QSpinBox;
    sb8->setValue(1);

     sb8->setRange(-99,99);

    //font->addWidget();
    font->addWidget(sb0,0,0);
    font->addWidget(sb1,0,1);
    font->addWidget(sb2,0,2);
    font->addWidget(sb3,1,0);
    font->addWidget(sb4,1,1);
    font->addWidget(sb5,1,2);
    font->addWidget(sb6,2,0);
    font->addWidget(sb7,2,1);
    font->addWidget(sb8,2,2);

    groupBox->setLayout(font);
    QHBoxLayout *butL=new QHBoxLayout;
    ok=new QPushButton("Ok");
    cancel=new QPushButton("Annuler");
    butL->addWidget(ok);
    butL->addWidget(cancel);

    mainLayout->addWidget(groupBox);
    mainLayout->addLayout(butL);
    dialog->setLayout(mainLayout);
    dialog->show();
    QObject::connect(cancel,SIGNAL(clicked()),dialog,SLOT(close()));
    QObject::connect(ok,SIGNAL(clicked()),this,SLOT(nod()));



}

void fenetrePrincipale::activerCiseau(){ 
    tool->checkBoxCiseau=true;
    contener_fonct_ciseau->setFixedSize(200,150);
    dock_option->show();
    dock_option->setWidget(contener_fonct_ciseau);

    zoom_p->setEnabled(false);
    zoom_m->setEnabled(false);
    rectangle->setEnabled(false);
    redimention->setEnabled(false);
    histogrammeBouton->setEnabled(false);
    fus->setEnabled(false);
    select->setEnabled(false);
    gris->setEnabled(false);
    moyenne->setEnabled(false);
    rehausse_contraste->setEnabled(false);
    detectBord->setEnabled(false);
    but_gradientX->setEnabled(false);
    but_gradientY->setEnabled(false);
    customFiltre->setEnabled(false);
}

void fenetrePrincipale::activerSelection(bool b){
    tool->checkBoxCiseau = false;
    tool->checkBoxSelection=b;
    if(b){


     ciseauBox->setEnabled(false);
     zoom_p->setEnabled(false);
     zoom_m->setEnabled(false);
     //flou->setEnabled(false);
     rectangle->setEnabled(false);
     redimention->setEnabled(false);
     histogrammeBouton->setEnabled(false);
     fus->setEnabled(false);
     gris->setEnabled(false);
     moyenne->setEnabled(false);
     rehausse_contraste->setEnabled(false);
     detectBord->setEnabled(false);
     but_gradientX->setEnabled(false);
     but_gradientY->setEnabled(false);
     customFiltre->setEnabled(false);
     proxy->selectionActivee=false;
     proxyfg->selectionActivee=false;

    }else{

        proxy->selectionActivee=false;
        proxyfg->selectionActivee=false;

        proxy->bordure->hide();
        proxyfg->bordure->hide();

        ciseauBox->setEnabled(true);
        gris->setEnabled(true);
        zoom_p->setEnabled(true);
        zoom_m->setEnabled(true);
        //flou->setEnabled(true);
        rectangle->setEnabled(true);
        redimention->setEnabled(true);
        histogrammeBouton->setEnabled(true);
        fus->setEnabled(true);
        moyenne->setEnabled(true);
        rehausse_contraste->setEnabled(true);
        detectBord->setEnabled(true);
        but_gradientX->setEnabled(true);
        but_gradientY->setEnabled(true);
        customFiltre->setEnabled(true);

    }

}
void fenetrePrincipale::ajuster(){
    qreal factor=0;
    QImage* im;
    if(tool->getZoomFactor()==1.0)
        im=tool->getImage();
    else
        im=tool->getImageZoomee();
      QSize old=view->size();
     view->setMinimumSize(im->size());
    if(im->width()>QApplication::desktop()->width()*0.8  || im->height()>QApplication::desktop()->height()*0.8){
       /* if(im->width()>im->height()){
            factor=(qreal)im->width()/QApplication::desktop()->width()
        }else{

        }*/
       view->setMinimumSize(QApplication::desktop()->size()*0.9);
    }
    else{
        view->setMinimumSize(im->size());

        //if(this->size().width()>QApplication::desktop()->width() || this->size().height()>QApplication::desktop()->height())



    }

}

void fenetrePrincipale::copier(){
    tool->copieActivee=true;
    tool->copier();
}
void fenetrePrincipale::coller(){
    int res;
    if((res=tool->coller())==0){
         updateImageAffiche();
    }else if(res==1){
        QPixmap* ima;
        *ima=ima->fromImage(*imagefg);

        lab_imagefg->setPixmap(*ima);
        lab_imagefg->resize(imagefg->width(),imagefg->height());
        proxyfg->setWidget(lab_imagefg);
        scene->addItem(proxyfg);
        lab_imagefg->repaint();

    }else if(res==2){
         updateImageAffiche();
    }


}
void fenetrePrincipale::couper(){
    tool->copieActivee=true;
    tool->couper();
    updateImageAffiche();

}

void fenetrePrincipale::supprimer(){
    lab_imagefg->clear();
}

void fenetrePrincipale::histogrammee(){
    tool->checkBoxCiseau = false;
    contener_fonct_histo->setFixedSize(290,450);
    dock_option->show();
    dock_option->setWidget(contener_fonct_histo);


    select->setEnabled(false);
    ciseauBox->setEnabled(false);
    gris->setEnabled(false);
    zoom_p->setEnabled(false);
    zoom_m->setEnabled(false);
    histogrammeBouton->setEnabled(false);
    //flou->setEnabled(false);
    rectangle->setEnabled(false);
    redimention->setEnabled(false);
    fus->setEnabled(false);
    moyenne->setEnabled(false);
    rehausse_contraste->setEnabled(false);
    detectBord->setEnabled(false);
    but_gradientX->setEnabled(false);
    but_gradientY->setEnabled(false);
    customFiltre->setEnabled(false);

}

void fenetrePrincipale::undo(){
   QStack<QImage> u=tool->getUndo();
   if(!u.isEmpty()){
    tool->annuler();
   }
   QImage *imag = new QImage();
   QPixmap *ima = new QPixmap();
   imag = tool->getImage(); //recup image grise
   *ima = ima->fromImage(*imag);

   lab_image->setPixmap(*ima); //on ajoute l'image grise dans un label
   lab_image->resize(ima->width(),ima->height());
   updateImageAffiche();


}
void fenetrePrincipale::actionfusion(){
    tool->checkBoxCiseau = false;
    outilfusion=new fusion(tool);

    chem_imagefg=NULL;
    recup_cheminfg();
    if(chem_imagefg!=NULL){
        dock_option->show();
         dock_option->setWidget(contener_fonct_fusion);
        outilfusion->ouvrir_image_a_rajouter(*chem_imagefg);
        imagefg=new QImage();
        QPixmap *ima = new QPixmap();
        imagefg = outilfusion->getImageFg();
        tool->setImageFg(imagefg);
        *ima = ima->fromImage(*imagefg);
       // updateImageAffiche();

        //proxyfg->setPos(100,100);
        //lab_imagefg->setVisible(true);
        proxyfg->setPos(50,50);
        lab_imagefg->setStyleSheet("background-color: rgba(0, 0, 0, 0)");
        lab_imagefg->setPixmap(*ima);
        lab_imagefg->resize(ima->width(),ima->height());
        alphafg=255;       
        lab_imagefg->repaint();
        //proxyfg->setVisible(false);
        proxyfg->setVisible(true);
        scene->removeItem(proxyfg);
        proxyfg->setWidget(lab_imagefg);
        scene->addItem(proxyfg);
        slideFusionimg1->setValue(255);

    }


}
void fenetrePrincipale::fusionner(){
    QPoint position;
    position.setX(25);
    position.setY(25);

    outilfusion->fusionner(imagefg,tool->getImage(),QPoint(lab_imagefg->pos().x(),lab_imagefg->pos().y()),alphafg);

    QImage *imag = new QImage();
    QPixmap *ima = new QPixmap();
   /* imag = tool->getImage();
    *ima = ima->fromImage(*imag);*/

    tool->checkBoxSelection=false;
    select->setChecked(false);
    proxyfg->setVisible(false);
    lab_imagefg->clear();
   /* lab_image->setPixmap(*ima);
    lab_image->resize(ima->width(),ima->height());*/
    dock_option->hide();
    updateImageAffiche();

}

void fenetrePrincipale::redo(){
    QStack<QImage> r=tool->getRedo();
    if(!r.isEmpty()){
        tool->refaire();
    }
    QImage *imag = new QImage();
    QPixmap *ima = new QPixmap();
    imag = tool->getImage();
    *ima = ima->fromImage(*imag);

    lab_image->setPixmap(*ima);
    lab_image->resize(ima->width(),ima->height());
    updateImageAffiche();
}

void fenetrePrincipale::save(){
    QFileDialog dialog(this,"Enregistrer sous");
    dialog.setFilter("Image(*.png *.jpg *.bmp)");

    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        chem_image = new QString(fileNames.takeFirst());
    }
    QString a;
    a.append(chem_image);
   // a.append("/imageFin.jpg");
    tool->getImage()->save(a);
}


void fenetrePrincipale::ouvrir_image(){
    int lala = recup_chemin();
    if(lala == 1)
    {
    tool->ouvrir_image_memoire(*chem_image);
    /*QImage *tmp=tool->getImage();
    QPixmap ima = ima.fromImage(*tmp);
    lab_image->resize(ima.width(),ima.height());
    proxy->resize(ima.width(),ima.height());
    lab_image->setPixmap(ima);
    histo->reiinit();
    zoomi->reiinitZoom();*/
    tool->imageTemp = false;
    gris->setEnabled(true);
    zoom_p->setEnabled(true);
    zoom_m->setEnabled(true);
    //flou->setEnabled(true);
    rectangle->setEnabled(true);
    redimention->setEnabled(true);
    histogrammeBouton->setEnabled(true);
    fus->setEnabled(true);
    select->setEnabled(true);
    ciseauBox->setEnabled(true);
    moyenne->setEnabled(true);
    rehausse_contraste->setEnabled(true);
    detectBord->setEnabled(true);
    but_gradientX->setEnabled(true);
    but_gradientY->setEnabled(true);
    customFiltre->setEnabled(true);
    dock_option->hide();
    updateImageAffiche();
    histo->reiinit();
    ajuster();
    updateImageAffiche();
    }
    
}
void fenetrePrincipale::recup_cheminfg() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        chem_imagefg = new QString(fileNames.takeFirst());
    }
}
int fenetrePrincipale::recup_chemin() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    QStringList fileNames;
    if (dialog.exec()) {
        fileNames = dialog.selectedFiles();
        chem_image = new QString(fileNames.takeFirst());
        return 1;
    }
    return 0;
}

void fenetrePrincipale::traitement_niveau_gris() {
    NiveauDeGris *g;
    g=new NiveauDeGris(tool);
    g->PassageNiveauDeGris();
    updateImageAffiche();
}

void fenetrePrincipale::zoom_plus() {


    //zoomi->zoomer(1);
    qreal a=tool->getZoomFactor();
     if(a<3){
         tool->setZoomFactor(tool->getZoomFactor()+0.1);
        tool->zoom();
        zoom_m->setEnabled(true);
        if(a>=2.9)
            zoom_p->setEnabled(false);



         updateImageAffiche();
         ajuster();
     }
}

void fenetrePrincipale::zoom_moins() {

    //zoomi->zoomer(0);
    qreal a=tool->getZoomFactor();
     if(a>0.2){
         tool->setZoomFactor(tool->getZoomFactor()-0.1);
         tool->zoom();
         zoom_p->setEnabled(true);
         if(a<=0.3)
             zoom_m->setEnabled(false);


         updateImageAffiche();
         ajuster();


    }
}
void fenetrePrincipale::traitement_flou()
{
    dock_option->show();
    dock_option->setWidget(contener_fonct_filtre);
}

void fenetrePrincipale::faireRectangle()
{
  tool->redimensionnement =false;
  tool->checkBoxCiseau = false;  
  dock_option->show();
  dock_option->setWidget(contener_fonct_selection);
  tool->rectangleSelectionActive = true;

  rogner_func->setEnabled(false);
  view->boutonRogner=rogner_func;

  customFiltre->setEnabled(false);
  select->setEnabled(false);
  ciseauBox->setEnabled(false);
  gris->setEnabled(false);
  zoom_p->setEnabled(false);
  zoom_m->setEnabled(false);
  histogrammeBouton->setEnabled(false);
  rectangle->setEnabled(false);
  redimention->setEnabled(false);
  fus->setEnabled(false);
  moyenne->setEnabled(false);
  rehausse_contraste->setEnabled(false);
  detectBord->setEnabled(false);
  but_gradientX->setEnabled(false);
  but_gradientY->setEnabled(false);
}

void fenetrePrincipale::traitement_rognage()
{
   tool->redimensionnement =false;
   rognage rogn(tool);
   rogn.rognationner();
   updateImageAffiche();
   tool->rectangleSelectionActive=false;
   //zoomi->reiinitZoom();
}

void fenetrePrincipale::updateImageAffiche()
{    
    QPixmap ima;
    QImage *im=new QImage();
    if(!tool->imageTemp){
        if(tool->getZoomFactor()==1.0){
            im=tool->getImage();


        }else{
            im=tool->getImageZoomee();
        }
    }else{
        //ici on affiche d'abord une preview
        if(tool->getZoomFactor()==1.0){
            im=tool->getImageTraite();


        }else{
            im=tool->getImageTraiteeZoomee();
        }
    }

    ima=ima.fromImage(*im);


    scene->removeItem(proxy);
    lab_image->setPixmap(ima);
    lab_image->resize(im->width(),im->height());

    proxy->setWidget(lab_image);
    scene->addItem(proxy);
  //  tool->rect_image->setRect(0,0,im->width(),im->height());

   // lab_image->repaint();
    QSize s=lab_image->sizeHint();
    view->setSceneRect((qreal)0,(qreal)0,(qreal)s.width(),(qreal)s.height());

}


void fenetrePrincipale::histoSliderClarte(int a){
    refreshHisto();
    histo->modifHistogrammeClarte(a);
    updateImageAffiche();
}
void fenetrePrincipale::histoSliderContraste1(int a){
    refreshHisto();
    
    contraste1 = a;
    histo->modifHistogrammeContraste(contraste1,contraste2);
    updateImageAffiche();
}
void fenetrePrincipale::histoSliderContraste2(int a){
    refreshHisto();
    
    contraste2 = a;
    histo->modifHistogrammeContraste(contraste1,contraste2);
    updateImageAffiche();
}

//5.1-255
void fenetrePrincipale::histoSliderR(int a){
    refreshHisto();
    histR = a;
    histo->modifHistogrammeClarteIndiv(histR,histG,histB);
    updateImageAffiche();
}
void fenetrePrincipale::histoSliderG(int a){
    refreshHisto();
    
    histG = a;
    histo->modifHistogrammeClarteIndiv(histR,histG,histB);
    updateImageAffiche();
}
void fenetrePrincipale::histoSliderB(int a){
    refreshHisto();
    histB = a;
    histo->modifHistogrammeClarteIndiv(histR,histG,histB);
    updateImageAffiche();
    //cout<<(int)r<<" "<<(int)g<<" "<<(int)b<<"\n";
}

void fenetrePrincipale::fusionSliderImage1(int a)
{
    alphafg=a;
    // marche pas pour les png pour le moment.
        QColor c;
        int r,g,b,aa;

        for(int i = 0 ; i < imagefg->width() ; i++)
            {
            for(int j = 0 ; j < imagefg->height() ; j++)
              {

                c.setRgb(imagefg->pixel(i,j));
                c.getRgb(&r,&g,&b,&aa);

                if(aa==0){
                   c.setRgb(r,g,b,0);
                   imagefg->setPixel(i,j,c.rgba());
                }
                else{
                    c.setRgb(r,g,b,a);
                    imagefg->setPixel(i,j,c.rgba());
                }
              }
            }



        QPixmap *ima = new QPixmap();
        *ima = ima->fromImage(*imagefg);
        lab_imagefg->setPixmap(*ima);
        lab_imagefg->resize(imagefg->width(),imagefg->height());

}

void fenetrePrincipale::fusionSliderImage2(int a)
{
    int r,g,b,aa;
    QImage *image;
    if(tool->getZoomFactor()==1.0)
        image=tool->getImage();
    else
        image=tool->getImageZoomee();
    QColor c;
    for(int i = 0 ; i < image->width() ; i++)
        {
        for(int j = 0 ; j < image->height() ; j++)
          {

            c.setRgb(image->pixel(i,j));
            c.getRgb(&r,&g,&b,&aa);

            if(aa!=0){
               c.setRgb(r,g,b,a);
               image->setPixel(i,j,c.rgba());
            }
          }
        }



    QPixmap *ima = new QPixmap();
    *ima = ima->fromImage(*image);
    lab_image->setPixmap(*ima);
    lab_image->resize(image->width(),image->height());

}

void fenetrePrincipale::refreshHisto(){    
    histo->calculHistogramme(tool->utiliserRGB);
    if(tool->utiliserRGB){
        sceneHisto = histo->getHistogrammes(3, 1, 20);
    }else{
        sceneHisto = histo->getHistogrammes(3, 1, 25);
    }
    viewHisto->setScene(sceneHisto);
}

 
 void fenetrePrincipale::filtrageMoyenne()
 {
     int taille=3;
     wrapper->conv(taille,NOYAU_MOYENNEUR);
     updateImageAffiche();
 }
 
 void fenetrePrincipale::filtrageRehausseur()
 {
     NiveauDeGris *g;
     g=new NiveauDeGris(tool);
     g->PassageNiveauDeGris();
     int taille=3;
     wrapper->conv(taille,NOYAU_REHAUSSEMENT);
     updateImageAffiche();
 }
 
 void fenetrePrincipale::filtrageContraste()
 {
     wrapper->rehaussementContour(10);
     updateImageAffiche();
 }
 
 void fenetrePrincipale::filtrageDetection()
 {
     NiveauDeGris *g;
     g=new NiveauDeGris(tool);
     g->PassageNiveauDeGris();
     int taille=3;
     wrapper->conv(taille,NOYAU_DETECTIONBORD);
     
     //temporairement commente
//     ciseau cise(tool);
//     cise.contour(649,990,649,50,20);
     updateImageAffiche();
 }
 
 void fenetrePrincipale::filtrageGradientX()
 { 
     NiveauDeGris *g;
     g=new NiveauDeGris(tool);
     g->PassageNiveauDeGris();
     int taille=3;
     wrapper->conv(taille,NOYAU_GRADIENTX);
     updateImageAffiche();
}

// void fenetrePrincipale::traitement_redimension()
// {
//     tool->bool_image_gradient = false;
//     std::cout << "redimension" << std::endl;
// //    contener_fonct_histo->setFixedSize(600,600);
//     palette_couleur->setWidget(contener_fonct_redim);
////     
//     champ_hauteur->setText(QString::number(tool->getImage()->height()));
//     champ_largeur->setText(QString::number(tool->getImage()->width()));
//     ratio = ((tool->getImage()->height()*1.0)/(tool->getImage()->width()*1.0));
//     std::cout << "ratio : " << ratio << std::endl;
//     
//     tool->setImageGradient(tool->getImage());
//     
//     slider_redim_largeur->setRange(0.6*tool->getImageGradient()->width(),1.4*tool->getImageGradient()->width());
//     slider_redim_largeur->setValue(tool->getImageGradient()->width());
//     
//     slider_redim_hauteur->setRange(tool->getImageGradient()->height(),1.5*tool->getImageGradient()->height());
//     slider_redim_hauteur->setValue(tool->getImageGradient()->height());
//     
//     tool->init_matrice_case();
//     wrapper->gradient();
//     grad->recup_chem_verticaux(tool->matrice_w);
//     tool->bool_image_gradient = true;
//}
  void fenetrePrincipale::filtrageGradientY()
 { 
     NiveauDeGris *g;
     g=new NiveauDeGris(tool);
     g->PassageNiveauDeGris();
     int taille=3;
     wrapper->conv(taille,NOYAU_GRADIENTY);
     updateImageAffiche();
}

void fenetrePrincipale::traitement_redimension() {
    tool->checkBoxCiseau = false;
    select->setEnabled(false);
    ciseauBox->setEnabled(false);
    gris->setEnabled(false);
    zoom_p->setEnabled(false);
    zoom_m->setEnabled(false);
    //flou->setEnabled(false);
    rectangle->setEnabled(false);
    histogrammeBouton->setEnabled(false);
    fus->setEnabled(false);
    moyenne->setEnabled(false);
    rehausse_contraste->setEnabled(false);
    detectBord->setEnabled(false);
    but_gradientX->setEnabled(false);
    but_gradientY->setEnabled(false);
    customFiltre->setEnabled(false);


    tool->redimensionnement =true;
    tool->bool_image_gradient = false;
    //std::cout << "redimension" << std::endl;
    //    contener_fonct_histo->setFixedSize(600,600);
    contener_fonct_redim->setFixedSize(250, 400);
    dock_option->show();
    dock_option->setWidget(contener_fonct_redim);
    //     
    champ_hauteur->setText(QString::number(tool->getImage()->height()));
    champ_largeur->setText(QString::number(tool->getImage()->width()));
//    ratio = ((tool->getImage()->height()*1.0) / (tool->getImage()->width()*1.0));
    //std::cout << "ratio : " << ratio << std::endl;

//    tool->setImageGradient(tool->getImage());

    slider_redim_largeur->setRange(0.5 * tool->getImage()->width(), 1.5 * tool->getImage()->width());
    slider_redim_largeur->setValue(tool->getImage()->width());

    slider_redim_hauteur->setRange(0.5 *tool->getImage()->height(), 1.5 * tool->getImage()->height());
    slider_redim_hauteur->setValue(tool->getImage()->height());
    
    redim_intel->setChecked(false);
    tool->bool_image_gradient = true;

}
 
 void fenetrePrincipale::redim_f()
 {
     std::cout << "redim : " << "(" << tool->val_champ_largeur << 
     "," << tool->val_champ_hauteur << ")" << std::endl;
 }
 
 void fenetrePrincipale::maj_largeur(const QString& txt)
 {//std::cout << "maj_largeur : " << std::endl;
    //tool->val_champ_largeur = txt.toInt();

    ////champ_hauteur->setText(QString::number(val));
 }
 
 void fenetrePrincipale::maj_hauteur(const QString& txt)
 {
     //std::cout << "maj_hauteur : " << std::endl;
     //tool->val_champ_hauteur = txt.toInt();
     //champ_largeur->setText(QString::number(val));
 }
 
 
 void fenetrePrincipale::redimIntelligent(int etat)
 {

     tool->check_intelligent = etat;
     //cout<<" etat : "<<etat<<std::endl;
     if(etat == 2)
     {
     tool->bool_image_gradient = false;
      //tool->setImage(tool->getImage());
      tool->setImageTraite(tool->getImage());
     
     slider_redim_largeur->setRange(0.6*tool->getImageTraite()->width(),1.4*tool->getImageTraite()->width());
     slider_redim_largeur->setValue(tool->getImageTraite()->width());
     
     slider_redim_hauteur->setRange(0.6*tool->getImageTraite()->height(),1.4*tool->getImageTraite()->height());
     slider_redim_hauteur->setValue(tool->getImageTraite()->height());
     
     tool->init_matrice_case();
     wrapper->gradient();
     grad->recup_chem_verticaux(tool->matrice_w);
     tool->bool_image_gradient = true;
     slider_redim_hauteur->setEnabled(false);
     }else{
     slider_redim_hauteur->setEnabled(true);
     }
 }      
 
 void fenetrePrincipale::slider_largeur(int val)
 {

     if(tool->check_intelligent == 2){
         
        champ_largeur->setText(QString::number(val));
     
     if(val > tool->getImageTraite()->width())
       {
         grad->SC_agrandissement_horizontal(val);
       }
     else if(val < tool->getImageTraite()->width())
      {
         grad->SC_reduction_horizontal(val);
      }
        
      }
     else{
         zoom zoomi(tool);
         zoomi.redim(val,tool->getHeight());
         champ_hauteur->setText(QString::number(tool->getHeight()));
         champ_largeur->setText(QString::number(val));
     }

     
     updateImageAffiche();
 }
 
  void fenetrePrincipale::slider_hauteur(int val)
 {
     //std::cout << val << std::endl;
     if(tool->check_intelligent){
         
     }else{
        zoom zoomi(tool);
        zoomi.redim(tool->getWidth(),val);
        champ_hauteur->setText(QString::number(val));
        champ_largeur->setText(QString::number(tool->getWidth()));
     }
     updateImageAffiche();
 }
 
 void fenetrePrincipale::slider_ciseau(int a){
     tool->ciseauSeuil= a;
}

void fenetrePrincipale::accepter() {
   // redim_intel->setChecked(false);
    gris->setEnabled(true);
    zoom_p->setEnabled(true);
    zoom_m->setEnabled(true);
    //flou->setEnabled(true);
    rectangle->setEnabled(true);
    redimention->setEnabled(true);
    histogrammeBouton->setEnabled(true);
    fus->setEnabled(true);
    select->setEnabled(true);
    ciseauBox->setEnabled(true);
    moyenne->setEnabled(true);
    rehausse_contraste->setEnabled(true);
    detectBord->setEnabled(true);
    but_gradientX->setEnabled(true);
    but_gradientY->setEnabled(true);
    customFiltre->setEnabled(true);
    if(tool->redimensionnement && ((tool->val_champ_largeur != champ_largeur->text().toInt() || tool->val_champ_hauteur != champ_hauteur->text().toInt()) && redim_intel->isChecked() == false)){
        zoom zoomi(tool);
        cout<<"redim a "<<champ_largeur->text().toInt()<<" "<<champ_hauteur->text().toInt()<<endl;
        zoomi.redim(champ_largeur->text().toInt(),champ_hauteur->text().toInt());
    }
    histo->reiinit();
    
    tool->imageTemp = false;
    if((tool->getImageTraite()) != NULL)
    {std::cout << "image traitée pas null" << std::endl;
        tool->setImage(tool->getImageTraite());
    }
    if(tool->decoupagePossible){
        ciseau cis(tool);
        cis.decouperImage();
        while(!tool->pixel.empty()){
            tool->pixel.pop_front();
        }
        tool->decoupagePossible = false;
    }
    dock_option->hide();
    updateImageAffiche();
}

void fenetrePrincipale::annuler() {
    
    redim_intel->setChecked(false);
    ciseauBox->setEnabled(true);
    gris->setEnabled(true);
    zoom_p->setEnabled(true);
    zoom_m->setEnabled(true);
    //flou->setEnabled(true);
    rectangle->setEnabled(true);
    redimention->setEnabled(true);
    histogrammeBouton->setEnabled(true);
    fus->setEnabled(true);
    select->setEnabled(true);
    moyenne->setEnabled(true);
    rehausse_contraste->setEnabled(true);
    detectBord->setEnabled(true);
    but_gradientX->setEnabled(true);
    but_gradientY->setEnabled(true);
    customFiltre->setEnabled(true);
    
    ciseauSlider->setSliderPosition(0);
    slider_clarte->setSliderPosition(0);
    slider_contraste1->setSliderPosition(0);
    slider_contraste2->setSliderPosition(255);
    slider_r->setSliderPosition(0);
    slider_g->setSliderPosition(0);
    slider_b->setSliderPosition(0);
    
//    if(tool->redimensionnement){
//        slider_redim_largeur->setValue(tool->getImageGradient()->width());
//        slider_redim_hauteur->setValue(tool->getImageGradient()->height()); 
//    }
    
    tool->redimensionnement = false;
    refreshHisto();
    tool->decoupagePossible = false;
    tool->ciseauX =-1;
    tool->ciseauY =-1;
    tool->imageTemp = false;
    tool->setImage(tool->getImage());
    dock_option->hide();
    updateImageAffiche();
}

void fenetrePrincipale::utiliserYUV(int a){
    if(a==0){
        tool->utiliserRGB = 1;
        histoIndiv->setText("Reglage RGB");
    }else{
        tool->utiliserRGB = 0;
        histoIndiv->setText("Reglage YUV");
    }
    refreshHisto();
}

void fenetrePrincipale::passageMenuYuv(){
    tool->utiliserRGB = !tool->utiliserRGB;
    if(!tool->utiliserRGB){
        actionYuv->setText("Affichage en RGB");
        lab_r->setText("<font color=\"#FF0000\">Y : </font>");
        lab_v->setText("<font color=\"#419F2E\">U : </font>");
        lab_b->setText("<font color=\"#0000FF\">V : </font>");
    }else{
        actionYuv->setText("Affichage en YUV");
        lab_r->setText("<font color=\"#FF0000\">R : </font>");
        lab_v->setText("<font color=\"#419F2E\">V : </font>");
        lab_b->setText("<font color=\"#0000FF\">B : </font>");
    }
    
    

}


fenetrePrincipale::~fenetrePrincipale()
{
//    delete grad;
//   delete menuAffichage;
//    delete menuFichier;
//   delete menuEdition;
//   delete menuImage;
//    delete menuFiltre;
//   delete menuPresentation;
//  
//    delete menuSauver;
//    
//    delete jpg;
//    delete png;
//    delete bmp;
//    delete actionOuvrir;
//    delete actionAnnuler;
//    delete actionRefaire;
//    
//    delete scene;
//    delete scene_ap;
//    
//   delete lab_image;
//    delete lab_imagefg;
//    
//    delete sceneHisto;
//   delete viewHisto;
//  
//   delete view;
//    
//    delete palette_couleur;
//    delete palette_outil;
//   delete palette_etat;
//    
//    delete chem_image;
//    delete chem_imagefg;
//    
//    delete proxy;
//    delete proxyfg;
//    
//    delete pixmapitem;
//    
//    delete rogner_func;
//    delete fairefusionner;
//
//    delete layout_selection;
//    delete layout_filtre;
//   delete layout_fusion;
//   delete layout_histogramme;
//    delete layout_outils;
//    delete layout_redim;
//
//    delete histoClarte;
//    delete slider_clarte;
//    delete histoContraste;
//   delete slider_contraste1;
//    delete slider_contraste2;
//   delete histoIndiv;
//   delete slider_r;
//    delete slider_g;
//    delete slider_b;
//    
//    delete moyenne;
//    delete rehausseur;
//   delete passebas;
//    delete rehausse_contraste;
//    delete detectBord;
//   delete but_gradient;
//    
//    delete redim_intel;
//  delete redim;
//    delete lab_largeur;
//    delete lab_hauteur;
//    delete lab_prop;
//    
//    delete slideFusionimg1;
//    delete slideFusionimg2;
//    
//    delete toolbar;
//    
//   delete contener_fonct_filtre;
//   delete contener_fonct_histo;
//   delete contener_fonct_selection;
//    delete contener_fonct_fusion;
//   delete contener_fonct_filtrage;
//   delete contener_fonct_redim;
//    
//    delete champ_largeur;
//    delete champ_hauteur;
//    delete check_prop;
//     
//   delete lab_r;
//    delete lab_v;
//   delete lab_b;
//   delete lab_x;
//   delete lab_y;
//    
//   delete gris;
//   delete select;
//   delete flou;
//   delete zoom_p;
//    delete zoom_m;
//    delete fus;
//   delete histogrammeBouton;
//    delete redimention;
//    
//    delete view_ap; 
//    
//    delete slider_redim_largeur;
//    delete slider_redim_hauteur;
}
