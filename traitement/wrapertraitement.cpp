#include <QtGui/qcolor.h>
#include <QtGui/qimage.h>
#include <QtGui/qwindowdefs.h>
#include <QtGui/qrgb.h>

#include "wrapertraitement.h"
using namespace std;
#include "stdio.h"

wraperTraitement::wraperTraitement(outils *t) {
    this->tool = t;
}

int** wraperTraitement::retourner_noyau(int numero_noyau) {
    int **m = new int*[3];
    for (int i = 0; i < 3; i++) {
        m[i] = new int[3];
    }
    switch (numero_noyau) {
            /*rajouter des cases pour tous les noyaux � rajouter ;penser � rajouter dans le .h les noyaux dans le type enum*/


        case NOYAU_PERSONNALISE:

        {

             m[0][0] = a1;m[0][1] = a2;m[0][2] = a3;
             m[1][0] = a4;m[1][1] = a5;m[1][2] = a6;
             m[2][0] = a7;m[2][1] = a8;m[2][2] = a9;
             som = a1+a2+a3+a4+a5+a6+a7+a8+a9;
             if(som==0){som=1;}
             break;

        }

        case NOYAU_MOYENNEUR:
        {
            m[0][0] = 1;m[0][1] = 1;m[0][2] = 1;
            m[1][0] = 1;m[1][1] = 1;m[1][2] = 1;
            m[2][0] = 1;m[2][1] = 1;m[2][2] = 1;
            som = 9;
            break;
        }
        case NOYAU_REHAUSSEMENT:
        {
            m[0][0] = 1;m[0][1] = 2;m[0][2] = 1;
            m[1][0] = 2;m[1][1] = -12;m[1][2] = 2;
            m[2][0] = 1;m[2][1] = 2;m[2][2] = 1;
            som = 1;
            break;
        }
        case NOYAU_PASSEBAS:
        {
            m[0][0] = 1;m[0][1] = 1;m[0][2] = 1;
            m[1][0] = 1;m[1][1] = 8;m[1][2] = 1;
            m[2][0] = 1;m[2][1] = 1;m[2][2] = 1;
            som = 16;
            break;
        }
        case NOYAU_REHAUSSEMENTCONTRASTE:
        {
            m[0][0] = 0;m[0][1] = -1;m[0][2] = 0;
            m[1][0] = -1;m[1][1] = 5;m[1][2] = -1;
            m[2][0] = 0;m[2][1] = -1;m[2][2] = 0;
            som = 5;
            break;
        }
        case NOYAU_DETECTIONBORD:
        {
            m[0][0] = 0;m[0][1] = 1;m[0][2] = 0;
            m[1][0] = 1;m[1][1] = -4;m[1][2] = 1;
            m[2][0] = 0;m[2][1] = 1;m[2][2] = 0;
            som = 1;
            break;
        }

        case NOYAU_GRADIENTX:
        {
            m[0][0] = -1;m[0][1] = 0;m[0][2] = 1;
            m[1][0] = -2;m[1][1] = 0;m[1][2] = 2;
            m[2][0] = -1;m[2][1] = 0;m[2][2] = 1;
            som = 4;
            break;
        }
        case NOYAU_GRADIENTY:
        {
            m[0][0] = -1;m[0][1] = -2;m[0][2] = -1;
            m[1][0] = 0;m[1][1] = 0;m[1][2] = 0;
            m[2][0] = 1;m[2][1] = 2;m[2][2] = 1;
            som = 4;
            break;
        }
        default:
        {
            break;
        }

    }

    return m;

}

QImage* wraperTraitement::construireImageTemp(outils *t) {
    // Construit une image temporaire similaire a in mais avec un cadre de taille "taille" autour d'elle contenant des pixels similaires au bord de l'image
    // utile pour le parcours avec un noyau de convolution pour eviter les cas de bordure
    int offset = (taille - 1) / 2;
    temp = new QImage(t->getImage()->width()+(taille - 1), t->getImage()->height()+(taille - 1), (t->getImage())->format());
    int r = 0, g = 0, b = 0, aa = 0;
    int tmph = temp->size().height();
    int tmpw = temp->size().width();
    QColor c;
    for (int x = 0; (x + offset)<(tmpw - offset); x++) {

        for (int y = 0; (y + offset)<(tmph - offset); y++) {

            t->getPixel(x, y, &r, &g, &b, &aa);
            c.setRgb(r, g, b, aa);
            temp->setPixel(x + offset, y + offset, c.rgba());
        }
    }

    //=============================
    // pour la bordure a gauche
    for (int x = 0; x < offset; x++) {

        for (int y = offset; y < (tmph - offset); y++) {
            t->getPixel(0, y - offset, &r, &g, &b, &aa);
            c.setRgb(r, g, b, aa);
            temp->setPixel(x, y, c.rgba());
        }
    }
    int k = 0, l = 0;
    t->getPixel(0, 0, &r, &g, &b, &aa); // pixel en haut a gauche
    c.setRgb(r, g, b, aa);
    while (k < offset) {
        while (l < offset) {
            temp->setPixel(k, l, c.rgba());
            l++;
        }
        k++;
    }
    k = 0;
    l = 0;
    t->getPixel(0, t->getHeight() - 1, &r, &g, &b, &aa); // pixel en bas a gauche
    c.setRgb(r, g, b, aa);
    while (k < offset) {
        while (l < offset) {
            temp->setPixel(k, (tmph - offset) + l, c.rgba());
            l++;
        }
        k++;
    }

    //==============================
    // pour la bordure a droite

    for (int x = (tmpw - offset); x < tmpw; x++) {

        for (int y = offset; y < (tmph - offset); y++) {
            t->getPixel(t->getWidth() - 1, y - offset, &r, &g, &b, &aa);
            c.setRgb(r, g, b, aa);
            temp->setPixel(x, y, c.rgba());
        }
    }
    k = 0;
    l = 0;
    t->getPixel(t->getWidth() - 1, 0, &r, &g, &b, &aa); // pixel en haut a droite
    c.setRgb(r, g, b, aa);
    while (k < offset) {
        while (l < offset) {
            temp->setPixel(k + (tmpw - offset), l, c.rgba());
            l++;
        }
        k++;
    }
    k = 0;
    l = 0;
    t->getPixel(t->getWidth() - 1, t->getHeight() - 1, &r, &g, &b, &aa); // pixel en bas a droite
    c.setRgb(r, g, b, aa);
    while (k < offset) {
        while (l < offset) {
            temp->setPixel(k + (tmpw - offset), l + (tmph - offset), c.rgba());
            l++;
        }
        k++;
    }

    //==============================
    // pour la bordure en haut
    for (int x = offset; x < (tmpw - offset); x++) {

        for (int y = 0; y < offset; y++) {
            t->getPixel(x - offset, 0, &r, &g, &b, &aa);
            c.setRgb(r, g, b, aa);
            temp->setPixel(x, y, c.rgba());
        }
    }

    //==============================
    // pour la bordure en bas
    for (int x = offset; x < (tmpw - offset); x++) {

        for (int y = (tmph - offset); y < tmph; y++) {
            t->getPixel(x - offset, (t->getHeight() - 1), &r, &g, &b, &aa);
            c.setRgb(r, g, b, aa);
            temp->setPixel(x, y, c.rgba());
        }
    }

    return temp;
}

QRgb wraperTraitement::filtrage(int i, int j, int **m) {
    int red = 0, green = 0, blue = 0, alpha = 255;
    int r, g, b, aa;
    int p = 0, q = 0;
    QColor c;
    int offset = (taille - 1) / 2;
    // changement de la couleur du pixel
    for (int u = i - offset; u < i + offset + 1; u++) {
        p = 0;
        for (int v = j - offset; v < j + offset + 1; v++) {
            tool->getPixel(u, v, &r, &g, &b, &aa);
            red += (r * m[p][q]);
            green += (g * m[p][q]);
            blue += (b * m[p][q]);
            //alpha += (aa * m[p][q]);
            p++;
        }
        q++;
    }
    
    if(red<0){red= -1*red;}
    if(blue<0){blue= -1*blue;}
    if(green<0){green= -1*green;}
    
    if(som!=0){
        red = red / som;
        green = green / som;
        blue = blue / som;
    }
    //alpha = alpha / som;
    
    if(red>255){red=255;}//if(red<0){red=-red;}
    if(blue>255){blue=255;}//if(blue<0){blue=-blue;}
    if(green>255){green=255;}//if(green<0){green=-green;}
    //cout<<red<<" "<<blue<<" "<<green<<" "<<alpha<<"\n";
    c.setRgb(red, green, blue, alpha);
    return c.rgba();

}

void wraperTraitement::filt_grad(int x, int y, int **m)
{
int red = 0, green = 0, blue = 0;
    int r, g, b, aa;
    int p = 0, q = 0;
    
    for (int i = x - 1; i <= x + 1; i++) {
        p = 0;
        for (int j = y - 1; j <= y + 1; j++) {

            tool->getPixelGradient(i,j, &r, &g, &b, &aa);
           // std::cout << r << "," << g << "," << b << std::endl;
            red += (r * m[p][q]);
            green += (g * m[p][q]);
            blue += (b * m[p][q]);
            p++;
        }
        q++;
    }


    red = abs(red / som);
    green = abs(green / som);
    blue = abs(blue / som);
   
    tool->get_case(x,y)->grad = (red + green + blue);
}

int wraperTraitement::filtrage_gradient(int x, int y, int **m) {

    int red = 0, green = 0, blue = 0;
    int r, g, b, aa;
    int p = 0, q = 0;

    
    for (int i = x - 1; i <= x + 1; i++) {
        p = 0;
        for (int j = y - 1; j <= y + 1; j++) {

            tool->getPixel(j, i, &r, &g, &b, &aa);
           // std::cout << r << "," << g << "," << b << std::endl;
            red += (r * m[p][q]);
            green += (g * m[p][q]);
            blue += (b * m[p][q]);
            p++;
        }
        q++;
    }


    red = abs(red / som);
    green = abs(green / som);
    blue = abs(blue / som);
    //cout<<"x "<<x-1<<" y "<<y-1<<"\n";
    tool->matrix[x][y] += (red + green + blue);
   
    return (red + green + blue);
}

int** wraperTraitement::retournementSpatial(int **m) {
    int offset = (taille - 1) / 2;
    int tmp;
    for (int i = 0; i < offset; i++) { // mirroring nord sud
        for (int j = 0; j < taille; j++) {
            tmp = m[i][j];
            m[i][j] = m[taille - 1 - i][j];
            m[taille - 1 - i][j] = tmp;
        }
    }
    for (int i = 0; i < taille; i++) { // mirroring est ouest
        for (int j = 0; j < offset; j++) {
            tmp = m[i][j];
            m[i][j] = m[i][taille - 1 - j];
            m[i][taille - 1 - j] = tmp;

        }
    }
    return m;
}

void wraperTraitement::conv(int tailles, int noyau) {
    _conv(tailles, noyau);
    tool->setImage(imageOut);
    //tool->setImageTraite(imageOut);
}

void wraperTraitement::convTraitement(int tailles, int noyau) {
    _conv(tailles, noyau);
    tool->setImage(imageOut);
    tool->setImageTraite(imageOut);
}

void wraperTraitement::_conv(int tailles, int noyau) {
    taille = tailles;
    QImage *imageIn = tool->getImage();
    int **m;
    QImage *temp;
    temp = construireImageTemp(tool);

    m = retourner_noyau(noyau);
    m = retournementSpatial(m);
    imageOut = new QImage(tool->getWidth(), tool->getHeight(), imageIn->format());
    tool->setImage2(temp);

    int offset = (taille - 1) / 2;
    int x = 0, y = 0;
    for (int i = offset; i < tool->getWidth() - offset; i++) {
        y = 0;
        for (int j = offset; j < tool->getHeight() - offset; j++) {
            imageOut->setPixel(x, y, filtrage(i, j, m));
            y++;
        }
        x++;
    }
    //imageOut->save("temp.png");
}
 void wraperTraitement::gradient()
 {
  
   int **m1 = retourner_noyau(NOYAU_GRADIENTX);
   int **m2 = retourner_noyau(NOYAU_GRADIENTY);
   
   int l = tool->matrice_w;
   int h = tool->matrice_h;

   for (int i = 1; i < h-1; i++) {
        for (int j = 1 ; j < l-1 ; j++)
        {
            filt_grad(j,i,m1);
            filt_grad(j,i,m2);
        }
    }
    
    //en haut et en bas
        cases *c1 = tool->matrice_case[0];
        cases *c2 = tool->matrice_case[1];
        
        while(c1->suivant != NULL)
          {
            c1->grad = c2->grad;

            c1 = c1->suivant;
            c2 = c2->suivant;
          }
        
        c1 = tool->matrice_case[h-1];
        c2 = tool->matrice_case[h-2];
        
        while(c1->suivant != NULL)
          {
            c1->grad = c2->grad;

            c1 = c1->suivant;
            c2 = c2->suivant;
          }
        
       
    //a droite et a gauche
    for(int i = 0 ; i < h ; i++)
     {
      tool->get_case(0,i)->grad = tool->get_case(1,i)->grad;
      tool->get_case(l-1,i)->grad = tool->get_case(l-2,i)->grad;
     }
 }

int** wraperTraitement::_conv_gradient(int tailles)
{
    taille = tailles;
    QImage *imageIn = tool->getImage();

//    QColor c1;
//    QColor c2;
  
    int **m1;
    int **m2;


    int l = imageIn->width();
    int h = imageIn->height();
    
//    std::cout << "largeur dans conv_gradient : " << l << std::endl;
//    std::cout << "hauteur dans conv_gradient : " << h << std::endl;
    
    tool->matrix = new int * [h];

    for (int i = 0; i < h; i++) {
        tool->matrix[i] = new int[l];
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            tool->matrix[i][j] = 0;
        }
    }

    tool->mat_h = h;
    tool->mat_w = l;
    
    m1 = retourner_noyau(NOYAU_GRADIENTX);
    m2 = retourner_noyau(NOYAU_GRADIENTY);

    for (int i = 1; i < h -1; i++) {
        for (int j = 1 ; j < l-1 ; j++)
        {
            filtrage_gradient(i, j, m1);
            filtrage_gradient(i, j, m2);
        }
    }
    
    //en haut et en bas
    for(int i = 0 ; i < l ; i++)
     {
      tool->matrix[0][i] = tool->matrix[1][i];
      tool->matrix[h-1][i] = tool->matrix[h-2][i];
      
     }
    //a droite et a gauche
    for(int i = 0 ; i < h ; i++)
     {
      tool->matrix[i][0] = tool->matrix[i][1];
      tool->matrix[i][l-1] = tool->matrix[i][l-2];
     }
    
    return tool->matrix;
}

void wraperTraitement::affichMat(int ii) {
//    QImage *in = tool->getImage();
//    int h = in->height();
//    int l = in->width();
//    if (ii) {
//        
//        QColor color;
//        int r, g, b, a;
//        for (int i = 0; i < h; i++) {
//            for (int j = 0; j < l; j++) {
//                color.setRgb(in->pixel(j, i));
//                color.getRgb(&r, &g, &b, &a);
//                std::cout << r << " ";
//            }
//            std::cout << std::endl;
//        }
//        std::cout << std::endl;
//    } else {
        for (int i = 0; i < tool->matrice_h; i++) {
            for (int j = 0; j < tool->matrice_w; j++) {
                std::cout << tool->get_case(j,i)->x << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
  //  }
}

wraperTraitement::~wraperTraitement()
{
// delete imageOut;
// delete temp;
}

void wraperTraitement::rehaussementContour(int seuil){
    QColor color;
    QImage *imageIn = tool->getImage();
    imageOut = new QImage(imageIn->width(), imageIn->height(), imageIn->format());
    int red = 0, green = 0, blue = 0, aa = 0;
    int redPrev = 0, greenPrev = 0, bluePrev = 0, tmp;

    //Recherche des details sur y
    for (int i = 0; i < imageIn->width(); i++) {
        for (int j = 0; j < imageIn->height(); j++) {

            color.setRgb(imageIn->pixel(i, j));
            color.getRgb(&red, &blue, &green, &aa);

            tmp = (red + green + blue) / 3 - (redPrev + greenPrev + bluePrev) / 3;
            if (tmp > seuil || tmp < -1 * seuil) {
                tmp = 255;
            } else {
                tmp = 0;
            }
            color.setRgb(tmp, tmp, tmp, 255);
            imageOut->setPixel(i, j, color.rgb());
            redPrev = red;
            bluePrev = blue;
            greenPrev = green;
        }
        color.setRgb(imageIn->pixel(i, 0));
        color.getRgb(&redPrev, &greenPrev, &bluePrev, &aa);
    }
    //RAZ des valeurs entre 2 passes
    red = 0;
    green = 0;
    blue = 0;
    redPrev = 0;
    bluePrev = 0;
    greenPrev = 0;
    //Recherche des details sur x
    for (int i = 0; i < imageIn->height(); i++) {
        for (int j = 0; j < imageIn->width(); j++) {

            color.setRgb(imageIn->pixel(j, i));
            color.getRgb(&red, &blue, &green, &aa);
            tmp = (red + green + blue) / 3 - (redPrev + greenPrev + bluePrev) / 3;
            if (tmp > seuil || tmp < -1 * seuil) {
                tmp = 255;
            } else {
                tmp = 0;
            }
            redPrev = red;
            bluePrev = blue;
            greenPrev = green;

            color.setRgb(imageOut->pixel(j, i));
            color.getRgb(&red, &blue, &green, &aa);
            if (!(red == 255 && blue == 255 && green == 255)) {
                imageOut->setPixel(j, i, color.rgb());
            }
        }
    }
    //Renforcement des details en fonction des contours precedemment trouves
    int renforcement = 20;
    for (int i = 0; i < imageIn->width(); i++) {
        for (int j = 0; j < imageIn->height(); j++) {
            
            color.setRgb(imageOut->pixel(i, j));
            color.getRgb(&redPrev, &bluePrev, &greenPrev, &aa);
            color.setRgb(imageIn->pixel(i, j));
            color.getRgb(&red, &green, &blue, &aa);

            if(redPrev == 255){
                //cout<<red<<" "<<green<<" "<<blue<<"\n";
                //tool->rgbToYuv(&red,&green,&blue);
                red-=renforcement;
                //tool->yuvToRgb(&red,&green,&blue);
                //cout<<red<<" "<<green<<" "<<blue<<"\n\n";
                green-=renforcement;blue-=renforcement;
                if(red<0){red=0;}if(blue<0){blue=0;}if(green<0){green=0;}
                if(red>255){red=255;}if(blue>255){blue=255;}if(green>255){green=255;}
                color.setRgb(red,green,blue,128);
                imageOut->setPixel(i,j,color.rgb());
            }else{
                imageOut->setPixel(i,j,color.rgb()); 
            }
        }
    }

    tool->setImage(imageOut);
}

