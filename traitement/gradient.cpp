/* 
 * File:   gradient.cpp
 * Author: Adri
 * 
 * Created on 11 janvier 2012, 12:42
 */

#include <QtGui/qimage.h>
#include <QtGui/qrgb.h>

#include "gradient.h"

gradient::gradient(outils *tool) 
{
    this->tool = tool;
    wrap = new wraperTraitement(tool);
    m1 = wrap->retourner_noyau(NOYAU_GRADIENTX);
    m2 = wrap->retourner_noyau(NOYAU_GRADIENTY);
    //affichMat(0);
}
int gradient::parcours_naif(int x ,int *chem)
{
    chem[0] = x;
   // std::cout << " chemCalcul[0] : " << chem[0] << std::endl;
    int sum = tool->get_case(x,0)->grad;
    
    int p_min = 0;
    
    for(int i = 1 ; i < tool->matrice_h ; i++)
    { 
        int gauche = 0x7FFFFFFF;
        int milieu = tool->get_case(chem[i-1],i)->grad;
        int droite = 0x7FFFFFFF;
        
        if(chem[i-1] > 0)
          {
            gauche = tool->get_case(chem[i-1]-1,i)->grad;
          }

        if(chem[i-1]+1 < (tool->matrice_w))
          {droite = tool->get_case(chem[i-1]+1,i)->grad;}
     
          p_min = tool->min(tool->min(gauche,droite),milieu);
 
              if(p_min == tool->get_case(chem[i-1],i)->grad)
                    {chem[i] = chem[i-1];}
     
              else if(p_min == tool->get_case(chem[i-1]+1,i)->grad)
                    {chem[i] = chem[i-1]+1;}
  
              else if(p_min == tool->get_case(chem[i-1]-1,i)->grad)
                    {chem[i] = chem[i-1]-1;}
        
//          if(chem[i] >= tool->matrice_w || chem[i] < 0 || chem[i] < chem[i-1]-1 || chem[i] > chem[i-1]+1)
//          {
//              std::cout << "ERREUR : chemin casse ";
//                 std::cout << "(" <<gauche<<","<<milieu<<","<<droite<<") ";
//                 std::cout << " chem[i] : " << chem[i] << " chem[i-1] : " << chem[i-1];
//                 std::cout << " taille matrice w : " << tool->matrice_w;
//                 std::cout << std::endl;
//          }
        sum += p_min;
       // std::cout << "chem["<<i<<"] : " << chem[i] << std::endl;
        
    }
    //std::cout <<std::endl;
    return sum;
}

int gradient::dijkstra(int x, int y,int *elem) {
    //init matrice a +infini
    std::cout << "coord : ("<< x << "," << y << ")"<<std::endl;
    QImage *imageIn = tool->getImage();

    int l = imageIn->width();
    int h = imageIn->height();
    
    matrixTemp = new int * [h];
    for (int i = 0; i < h; i++) {
        matrixTemp[i] = new int[l];
    }
    //initialisation matrice à +inf
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            matrixTemp[i][j] = 2000000000;
            //std::cout << tool->matrix[i][j] << " ";
        }//std::cout << "\n";
    }
   // std::cout << "\n";
    
    QQueue<element>queue;
    //on met à 0 le poids du 1er element
    matrixTemp[x][y] = 0;
    
    element dep(x, y, 0); 
    queue.enqueue(dep);
    //DI.J.RA en lui meme
    while (!queue.isEmpty()) {

        element tmp = queue.dequeue();
        
        //std::cout << tmp.x << " " << tmp.y << std::endl;
        
        if ((tmp.y) - 1 >= 0 && (tmp.x)+1 < h)
        {
            //gauche(x-1 , y , poids(x,y) + poids(x-1,y) , 0)
            element gauche(tmp.x + 1, tmp.y - 1, matrixTemp[tmp.x][tmp.y] + tool->matrix[tmp.x + 1][tmp.y-1]);
            if (gauche.poid < matrixTemp[tmp.x + 1][tmp.y - 1]) {
                matrixTemp[tmp.x + 1][tmp.y - 1] = gauche.poid;
                queue.enqueue(gauche);
            }
        }
        
        if ((tmp.y) + 1 < l && (tmp.x) + 1 < h)
        {
            element droite(tmp.x+1, tmp.y+1, matrixTemp[tmp.x][tmp.y]+ tool->matrix[tmp.x+1][tmp.y+1]);
            if (droite.poid < matrixTemp[tmp.x+1][tmp.y+1]) {
                matrixTemp[tmp.x+1][tmp.y+1] = droite.poid;
                queue.enqueue(droite);
            }
        }
        
        if ((tmp.x) + 1 < h)
        {
            element dessous(tmp.x + 1, tmp.y, matrixTemp[tmp.x][tmp.y] + tool->matrix[tmp.x + 1][tmp.y]);
            if (dessous.poid < matrixTemp[tmp.x + 1][tmp.y]) {
                matrixTemp[tmp.x + 1][tmp.y] = dessous.poid;
                queue.enqueue(dessous);
            }
        }

    }

    int val_cour_chem=2000000000;
    int num;
    for(int i=0;i<l;i++){
        if(matrixTemp[h-1][i]<val_cour_chem){
            num = i;
            val_cour_chem = matrixTemp[h-1][i];
            //std::cout<<"first "<<num<<"\n";
        }
    }
    QImage *in = tool->getImage();
    int hauteur = h-1;
    int a,b,c;
    
    elem[0] = x;
   int val_x;
    while(hauteur >= 0){
        //in->setPixel(num,hauteur,0xFFFF0000);
        
        b=matrixTemp[hauteur][num];
        val_x = num;
        if(num-1>0){
                a=matrixTemp[hauteur][num-1];
                if(a<b){
                    b=a;
                    val_x = num-1;
                }
        }
        if(num<l-1){
            c=matrixTemp[hauteur][num+1];
            if(c<b){
                b=c;
                val_x = num+1;
            }
        }
         elem[hauteur] = val_x;
         //std::cout << temp << std::endl;
        num = val_x;
      hauteur--;
    }
    tool->setImage(in);
    return val_cour_chem;

}

void gradient::affichMat(int ii) {
    QImage *in = tool->getImage();
    int h = in->height();
    int l = in->width();
    if (ii) {
        
        QColor color;
        int r, g, b, a;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < l; j++) {
                color.setRgb(in->pixel(j, i));
                color.getRgb(&r, &g, &b, &a);
                std::cout << r << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    } else {
        for (int i = 0; i < tool->getHeight(); i++) {
            for (int j = 0; j < tool->getWidth(); j++) {
                std::cout << tool->matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

void gradient::SC_agrandissement_horizontal(int new_x)
{
   if(tool->bool_image_gradient)
   {

    imagein = tool->getImageTraite();
    int diff = new_x - imagein->width();
   // std::cout << "agrandissement : " << diff <<" taille finale : "<<new_x<< std::endl;
    
 for(int p = 0 ; p < diff ; p++)
   {
          tool->matrice_w++;
     
     int *chem = tool->get_podium();
       
     
     for(int i = 0 ; i < tool->matrice_h ; i++)
     {
       cases *c = tool->get_case(chem[i],i);
       cases *new_c = new cases(chem[i]+1,i,c->pix);
       
       if(c->suivant != NULL)
         {
            new_c->precedent = c;
            new_c->suivant = c->suivant;
            c->suivant = new_c;
            new_c->suivant->precedent = new_c;
            new_c = new_c->suivant;
            
            while(new_c != NULL)
            {
                new_c->x += 1;
                new_c = new_c->suivant;
            }
         }
       else 
         { 
            c->suivant = new_c;
            new_c->precedent = c;
            new_c->suivant = NULL; 
         }
     }
     
//     tool->matrice_w++;
     
   for (int i = 1; i < tool->matrice_h-1; i++) 
   {
         if(chem[i] > 0 && chem[i] < tool->matrice_w-1)
           {
            wrap->filt_grad(chem[i], i, m1);
            wrap->filt_grad(chem[i], i, m2);
           }
            
        if(chem[i]+2 < tool->matrice_w)
         { 
            wrap->filt_grad(chem[i]+1, i, m1);
            wrap->filt_grad(chem[i]+1, i, m2);
            
                         
          if(chem[i]+4 < tool->matrice_w)
           {
            wrap->filt_grad(chem[i]+2, i, m1);
            wrap->filt_grad(chem[i]+2, i, m2);  
           }
         }
    }
     
     //on complete en haut et en bas
     
  for(int i = 0 ; i < tool->matrice_w ; i++)
     {
         tool->get_case(i,0)->grad = tool->get_case(i,1)->grad;
         tool->get_case(i,tool->matrice_h-1)->grad = tool->get_case(i,tool->matrice_h-2)->grad;
     }
    //a droite et a gauche 
  for(int i = 0 ; i < tool->matrice_h ; i++)
     {
         tool->get_case(tool->matrice_w-1,i)->grad = tool->get_case(tool->matrice_w-2,i)->grad;
         tool->get_case(0,i)->grad = tool->get_case(1,i)->grad;
     }
     
     for(int i = 0 ; i < tool->matrice_h ; i++)
     {
     tool->get_case(chem[i],i)->grad = 1.3*tool->get_case(chem[i],i)->grad;
     if(chem[i]+1 < tool->matrice_w)
       tool->get_case(chem[i]+1,i)->grad = 1.3*tool->get_case(chem[i]+1,i)->grad;
     }

        int *chem_redo = tool->maj_podium_add(chem);
        int*chem2 = new int[tool->matrice_h];
        int tmp = 0;
        
        //recalcul des chemins car il passaient par le chemin supprime
        for(int i = 1 ; i < chem_redo[0]+1 ; i++)
           {
           // std::cout << "chem a recalculer (+): "<<chem_redo[i] << std::endl;
            tmp = parcours_naif(chem_redo[i],chem2);
             tool->add_podium(chem2,tmp); 
           }

    }
    
    maj_picture();
 }
}

void gradient::SC_agrandissement_vertical(int new_x)
{
   if(tool->bool_image_gradient)
   {

    imagein = tool->getImageTraite();
    int diff = new_x - imagein->width();
   // std::cout << "agrandissement : " << diff <<" taille finale : "<<new_x<< std::endl;
    
 for(int p = 0 ; p < diff ; p++)
   {
          tool->matrice_w++;
     
     int *chem = tool->get_podium();
       
     
     for(int i = 0 ; i < tool->matrice_h ; i++)
     {
       cases *c = tool->get_case(chem[i],i);
       cases *new_c = new cases(chem[i]+1,i,c->pix);
       
       if(c->suivant != NULL)
         {
            new_c->precedent = c;
            new_c->suivant = c->suivant;
            c->suivant = new_c;
            new_c->suivant->precedent = new_c;
            new_c = new_c->suivant;
            
            while(new_c != NULL)
            {
                new_c->x += 1;
                new_c = new_c->suivant;
            }
         }
       else 
         { 
            c->suivant = new_c;
            new_c->precedent = c;
            new_c->suivant = NULL; 
         }
     }
     
//     tool->matrice_w++;
     
   for (int i = 1; i < tool->matrice_h-1; i++) 
   {
         if(chem[i] > 0 && chem[i] < tool->matrice_w-1)
           {
            wrap->filt_grad(chem[i], i, m1);
            wrap->filt_grad(chem[i], i, m2);
           }
            
        if(chem[i]+2 < tool->matrice_w)
         { 
            wrap->filt_grad(chem[i]+1, i, m1);
            wrap->filt_grad(chem[i]+1, i, m2);
            
                         
          if(chem[i]+4 < tool->matrice_w)
           {
            wrap->filt_grad(chem[i]+2, i, m1);
            wrap->filt_grad(chem[i]+2, i, m2);  
           }
         }
    }
     
     //on complete en haut et en bas
     
  for(int i = 0 ; i < tool->matrice_w ; i++)
     {
         tool->get_case(i,0)->grad = tool->get_case(i,1)->grad;
         tool->get_case(i,tool->matrice_h-1)->grad = tool->get_case(i,tool->matrice_h-2)->grad;
     }
    //a droite et a gauche 
  for(int i = 0 ; i < tool->matrice_h ; i++)
     {
         tool->get_case(tool->matrice_w-1,i)->grad = tool->get_case(tool->matrice_w-2,i)->grad;
         tool->get_case(0,i)->grad = tool->get_case(1,i)->grad;
     }
     
     for(int i = 0 ; i < tool->matrice_h ; i++)
     {
     tool->get_case(chem[i],i)->grad = 1.3*tool->get_case(chem[i],i)->grad;
     if(chem[i]+1 < tool->matrice_w)
       tool->get_case(chem[i]+1,i)->grad = 1.3*tool->get_case(chem[i]+1,i)->grad;
     }

        int *chem_redo = tool->maj_podium_add(chem);
        int*chem2 = new int[tool->matrice_h];
        int tmp = 0;
        
        //recalcul des chemins car il passaient par le chemin supprime
        for(int i = 1 ; i < chem_redo[0]+1 ; i++)
           {
           // std::cout << "chem a recalculer (+): "<<chem_redo[i] << std::endl;
            tmp = parcours_naif(chem_redo[i],chem2);
             tool->add_podium(chem2,tmp); 
           }

    }
    
    maj_picture();
 }
}

void gradient::SC_reduction_horizontal(int new_x)
{
    
     if(tool->bool_image_gradient)
   {

    imagein = tool->getImageTraite();
    int diff =imagein->width() - new_x;
   // std::cout << "reduction : " << diff <<" taille finale : "<<new_x<< std::endl; 
    
 for(int p = 0 ; p < diff ; p++)
   {
      tool->matrice_w--;
     
     int *chem = tool->get_podium();
     
     for(int i = 0 ; i < tool->matrice_h ; i++)
     {
      //   std::cout << "case a supprimer : " << chem[i];
       cases *c = tool->get_case(chem[i],i);
//        std::cout << "x : " << c->x << std::endl;
//       std::cout << "\nsuivant : " << c->suivant << std::endl;
//       std::cout << "precedent : " << c->precedent << " ";
        //c->actif = false;
       //std::cout << "("<<c->actif << ")";
       if(c->suivant != NULL && c->precedent != NULL)
         {
        //   std::cout << " milieu" << std::endl;
           
           c->x = -99999;
           cases *d = c->suivant;
           c->precedent->suivant = c->suivant;
           c->suivant->precedent = c->precedent;
           
           //si c'est une case repere
           if(c->case_tab != -1)
           {
               tool->matrice_tab[i][c->case_tab] = tool->matrice_tab[i][c->case_tab]->suivant;
               //si le suivant n'est pas une case repere il en devient une
               if(tool->matrice_tab[i][c->case_tab]->case_tab == -1)
               {tool->matrice_tab[i][c->case_tab]->case_tab = c->case_tab;}
           }
           
           c->precedent = NULL;
           c->suivant = NULL;
           c = NULL;
           //delete c->precedent;
          // delete c->suivant;
           delete c;
           
            while(d != NULL)
            {
                d->x -= 1;
                d = d->suivant;
            }
           
            
         }
       else if(c->suivant == NULL && c->precedent != NULL)
         { 
          // std::cout << " droite" << std::endl;
             c->x = -9999;
           
                   //si c'est une case repere
           if(c->case_tab != -1)
           {
               tool->matrice_tab[i][c->case_tab] = tool->matrice_tab[i][c->case_tab]->precedent;
               //si le suivant n'est pas une case repere il en devient une
               if(tool->matrice_tab[i][c->case_tab]->case_tab == -1)
               {tool->matrice_tab[i][c->case_tab]->case_tab = c->case_tab;}
           }

            c->precedent->suivant = NULL;
           // c->precedent = NULL;
           
          c->precedent = NULL;
           c->suivant = NULL;
           c = NULL;
          // delete c->precedent;
          // delete c->suivant;
           delete c;
            
         }
      else if(c->suivant != NULL && c->precedent == NULL)
         {
        //  std::cout << " gauche" << std::endl;
           c->x = -999;
          
          cases *d = c->suivant;
          
                  //si c'est une case repere
           if(c->case_tab != -1)
           {
               tool->matrice_tab[i][c->case_tab] = tool->matrice_tab[i][c->case_tab]->suivant;
               //si le suivant n'est pas une case repere il en devient une
               if(tool->matrice_tab[i][c->case_tab]->case_tab == -1)
               {tool->matrice_tab[i][c->case_tab]->case_tab = c->case_tab;}
               
//               tool->matrice_tab[i][0] = tool->matrice_tab[i][0]->suivant;
//               //si le suivant n'est pas une case repere il en devient une
//               if(tool->matrice_tab[i][0]->case_tab == -1)
//               {tool->matrice_tab[i][0]->case_tab = c->case_tab;}
           }
          
           tool->matrice_case[i] = tool->matrice_tab[i][c->case_tab];
           c->suivant->precedent = NULL;
          // c->suivant = NULL;
           
          // c = c->suivant;
            while(d != NULL)
            {
                d->x -= 1;
                d = d->suivant;
            }
           
           c->precedent = NULL;
           c->suivant = NULL;
           c = NULL;
           //delete c->precedent;
           //delete c->suivant;
           delete c;
           
         }
      else
      {
          std::cout << " erreur :(" << std::endl;
//          std::cout << "suivant : " << c->suivant << std::endl;
//          std::cout << "precedent : " << c->precedent << std::endl;
      
      }
     }
     
//     tool->matrice_w--;
     
   for (int i = 1; i < tool->matrice_h-1; i++) 
   {
         if(chem[i]-1 > 0)
           {
            wrap->filt_grad(chem[i]-1,i, m1);
            wrap->filt_grad(chem[i]-1,i, m2);
           }
            
        if(chem[i]+1 < tool->matrice_w-1)
         { 
            wrap->filt_grad(chem[i]+1, i, m1);
            wrap->filt_grad(chem[i]+1, i, m2);
         }
    }
     
     //on complete en haut et en bas
     
  for(int i = 0 ; i < tool->matrice_w ; i++)
     {
         tool->get_case(i,0)->grad = tool->get_case(i,1)->grad;
         tool->get_case(i,tool->matrice_h-1)->grad = tool->get_case(i,tool->matrice_h-2)->grad;
     }
    //a droite et a gauche 
  for(int i = 0 ; i < tool->matrice_h ; i++)
     {
         tool->get_case(tool->matrice_w-1,i)->grad = tool->get_case(tool->matrice_w-2,i)->grad;
         tool->get_case(0,i)->grad = tool->get_case(1,i)->grad;
     }

        int *chem_redo = tool->maj_podium_del(chem);
        int*chem2 = new int[tool->matrice_h];
        int tmp = 0;
        
             // std::cout << "\nnb chem a calculer : "<< chem_redo[0] << "\n";
              
        //recalcul des chemins car il passaient par le chemin supprime
        for(int i = 1 ; i < chem_redo[0]+1 ; i++)
           {
          //  std::cout << "chem a recalculer (-): "<<chem_redo[i] << std::endl;
          //  std::cout << "debut chem a calculer : "<< chem_redo[i] << "\n";
            tmp = parcours_naif(chem_redo[i],chem2);
             tool->add_podium(chem2,tmp); 
           }
//        wrap->affichMat(0);
//        std::cout << std::endl;;
    }
    maj_picture();
   
 }

 }

void gradient::SC_reduction_vertical(int new_x)
{
    
     if(tool->bool_image_gradient)
   {

    imagein = tool->getImageTraite();
    int diff =imagein->width() - new_x;
   // std::cout << "reduction : " << diff <<" taille finale : "<<new_x<< std::endl; 
    
 for(int p = 0 ; p < diff ; p++)
   {
      tool->matrice_w--;
     
     int *chem = tool->get_podium();
     
     for(int i = 0 ; i < tool->matrice_h ; i++)
     {
      //   std::cout << "case a supprimer : " << chem[i];
       cases *c = tool->get_case(chem[i],i);
//        std::cout << "x : " << c->x << std::endl;
//       std::cout << "\nsuivant : " << c->suivant << std::endl;
//       std::cout << "precedent : " << c->precedent << " ";
        //c->actif = false;
       //std::cout << "("<<c->actif << ")";
       if(c->suivant != NULL && c->precedent != NULL)
         {
        //   std::cout << " milieu" << std::endl;
           
           c->x = -99999;
           cases *d = c->suivant;
           c->precedent->suivant = c->suivant;
           c->suivant->precedent = c->precedent;
           
           //si c'est une case repere
           if(c->case_tab != -1)
           {
               tool->matrice_tab[i][c->case_tab] = tool->matrice_tab[i][c->case_tab]->suivant;
               //si le suivant n'est pas une case repere il en devient une
               if(tool->matrice_tab[i][c->case_tab]->case_tab == -1)
               {tool->matrice_tab[i][c->case_tab]->case_tab = c->case_tab;}
           }
           
           c->precedent = NULL;
           c->suivant = NULL;
           c = NULL;
           //delete c->precedent;
          // delete c->suivant;
           delete c;
           
            while(d != NULL)
            {
                d->x -= 1;
                d = d->suivant;
            }
           
            
         }
       else if(c->suivant == NULL && c->precedent != NULL)
         { 
          // std::cout << " droite" << std::endl;
             c->x = -9999;
           
                   //si c'est une case repere
           if(c->case_tab != -1)
           {
               tool->matrice_tab[i][c->case_tab] = tool->matrice_tab[i][c->case_tab]->precedent;
               //si le suivant n'est pas une case repere il en devient une
               if(tool->matrice_tab[i][c->case_tab]->case_tab == -1)
               {tool->matrice_tab[i][c->case_tab]->case_tab = c->case_tab;}
           }

            c->precedent->suivant = NULL;
           // c->precedent = NULL;
           
          c->precedent = NULL;
           c->suivant = NULL;
           c = NULL;
          // delete c->precedent;
          // delete c->suivant;
           delete c;
            
         }
      else if(c->suivant != NULL && c->precedent == NULL)
         {
        //  std::cout << " gauche" << std::endl;
           c->x = -999;
          
          cases *d = c->suivant;
          
                  //si c'est une case repere
           if(c->case_tab != -1)
           {
               tool->matrice_tab[i][c->case_tab] = tool->matrice_tab[i][c->case_tab]->suivant;
               //si le suivant n'est pas une case repere il en devient une
               if(tool->matrice_tab[i][c->case_tab]->case_tab == -1)
               {tool->matrice_tab[i][c->case_tab]->case_tab = c->case_tab;}
               
//               tool->matrice_tab[i][0] = tool->matrice_tab[i][0]->suivant;
//               //si le suivant n'est pas une case repere il en devient une
//               if(tool->matrice_tab[i][0]->case_tab == -1)
//               {tool->matrice_tab[i][0]->case_tab = c->case_tab;}
           }
          
           tool->matrice_case[i] = tool->matrice_tab[i][c->case_tab];
           c->suivant->precedent = NULL;
          // c->suivant = NULL;
           
          // c = c->suivant;
            while(d != NULL)
            {
                d->x -= 1;
                d = d->suivant;
            }
           
           c->precedent = NULL;
           c->suivant = NULL;
           c = NULL;
           //delete c->precedent;
           //delete c->suivant;
           delete c;
           
         }
      else
      {
          std::cout << " erreur :(" << std::endl;
//          std::cout << "suivant : " << c->suivant << std::endl;
//          std::cout << "precedent : " << c->precedent << std::endl;
      
      }
     }
     
//     tool->matrice_w--;
     
   for (int i = 1; i < tool->matrice_h-1; i++) 
   {
         if(chem[i]-1 > 0)
           {
            wrap->filt_grad(chem[i]-1,i, m1);
            wrap->filt_grad(chem[i]-1,i, m2);
           }
            
        if(chem[i]+1 < tool->matrice_w-1)
         { 
            wrap->filt_grad(chem[i]+1, i, m1);
            wrap->filt_grad(chem[i]+1, i, m2);
         }
    }
     
     //on complete en haut et en bas
     
  for(int i = 0 ; i < tool->matrice_w ; i++)
     {
         tool->get_case(i,0)->grad = tool->get_case(i,1)->grad;
         tool->get_case(i,tool->matrice_h-1)->grad = tool->get_case(i,tool->matrice_h-2)->grad;
     }
    //a droite et a gauche 
  for(int i = 0 ; i < tool->matrice_h ; i++)
     {
         tool->get_case(tool->matrice_w-1,i)->grad = tool->get_case(tool->matrice_w-2,i)->grad;
         tool->get_case(0,i)->grad = tool->get_case(1,i)->grad;
     }

        int *chem_redo = tool->maj_podium_del(chem);
        int*chem2 = new int[tool->matrice_h];
        int tmp = 0;
        
             // std::cout << "\nnb chem a calculer : "<< chem_redo[0] << "\n";
              
        //recalcul des chemins car il passaient par le chemin supprime
        for(int i = 1 ; i < chem_redo[0]+1 ; i++)
           {
          //  std::cout << "chem a recalculer (-): "<<chem_redo[i] << std::endl;
          //  std::cout << "debut chem a calculer : "<< chem_redo[i] << "\n";
            tmp = parcours_naif(chem_redo[i],chem2);
             tool->add_podium(chem2,tmp); 
           }
//        wrap->affichMat(0);
//        std::cout << std::endl;;
    }
    maj_picture();
   
 }

 }

void gradient::maj_picture()
{

 imageout = new QImage(tool->matrice_w,tool->matrice_h,imagein->format());
    for(int i = 0 ; i < tool->matrice_h ; i++)
    {
        cases *c = tool->matrice_case[i];
      
        while(c != NULL)
        {
          //   std::cout << c->x << " ";
//            if(c->x < 0 || c->x >= tool->matrice_w)
//            {
//                std::cout << "\nERREUR affichage : "<<c->x << " et max : "<< tool->matrice_w << std::endl;
//            }
            //std::cout << "("<<c->actif << ")";
//            if(c->x >= 0)
//            {
           // std::cout << c->x << " ";
              imageout->setPixel(c->x,i,c->pix);
          //  }
            c = c->suivant;
        }
       // std::cout << std::endl;
    }
//    QImage *tmp = tool->getImageTraite();
//    delete tmp;
    tool->setImageTraite(imageout);
   // std::cout << std::endl;
}
   
element::element(int i,int j,int pds){
    x = i;
    y = j;
    poid = pds;
    poidPot=0;
}

element::element(){}


void gradient::recup_chem_verticaux(int nb_chem)
{
     tool->init_podium(nb_chem,tool->getImage()->height());
     chem = new int [tool->getImage()->height()];
    int tmp = 0;
    for(int i = 0 ; i < tool->getImage()->width() ; i++)
      {
         tmp = parcours_naif(i,chem);
        tool->add_podium(chem,tmp); 
      }

}

void gradient::recup_chem_horizontaux(int nb_chem)
{
     tool->init_podium(nb_chem,tool->getImage()->height());
     chem = new int [tool->getImage()->height()];
    int tmp = 0;
    for(int i = 0 ; i < tool->getImage()->width() ; i++)
      {
         tmp = parcours_naif(i,chem);
        tool->add_podium(chem,tmp); 
      }

}
/*Supprime le chemin de la matrice en créant une nouvelle
 * recalcule le gradient localement
 
 */
void gradient::supr_chem_mat(int *chem)
{
    int l = tool->getImage()->width();
    int h = tool->getImage()->height();
    
//    std::cout << "largeur dans supr_chem_mat : " << l << std::endl;
//    std::cout << "hauteur dans supr_chem_mat : " << h << std::endl;
    int **m1 = wrap->retourner_noyau(NOYAU_GRADIENTX);
    int **m2 = wrap->retourner_noyau(NOYAU_GRADIENTY);
    
    int **old_mat = tool->matrix;
    //nouvelle matrice de taille w-1
    int **new_mat = new int*[h];
    for(int i = 0 ; i < h ; i++)
      {
        new_mat[i] = new int[l];
        for(int j = 0 ; j < l ; j++)
        {new_mat[i][j] = 0;}
      }
    //on remplit avec les anciennes valeurs
    for(int i = 0 ; i < h ; i++)
    {
       // std::cout << "chem["<<i<<"] : "<<chem[i]<<std::endl;
        for(int j = 1 ; j < l-1 ; j++)
        {
            //si on est avant le chemin on recopie
            if(j < (chem[i]-1))
            {
                new_mat[i][j] = old_mat[i][j];
            }
            
            //si on est apres on decale de 1 pixel
            else if(j > (chem[i]))
            {
                new_mat[i][j] = old_mat[i][j+1];
            }
            //sinon on doit se taper le calcul de gradient
            //si on est pas sur les 4 bords
            else if(i > 0 && i < h-1 && j > 0 && j < l-1)
            {
                //std::cout << "i : " << i << " | j : " << j << std::endl;
               new_mat[i][j] = wrap->filtrage_gradient(i,j,m1);
               new_mat[i][j] += wrap->filtrage_gradient(i, j, m2);
               
               //std::cout << "mat["<<i<<"]["<<j<<"] : "<<new_mat[i][j] <<std::endl;

            } 
        }
    }
    //2 extremites du chemin
    new_mat[0][chem[0]] = new_mat[1][chem[0]];
    new_mat[h-1][chem[h-1]] = new_mat[h-2][chem[h-1]];
    //son pote de gauche
    new_mat[0][chem[0]-1] = new_mat[1][chem[0]-1];
    new_mat[h-1][chem[h-1]-1] = new_mat[h-2][chem[h-1]-1];
    
    //bordure de gauche et de droite
    
    for(int i = 0 ; i < h ; i++)
    {
        new_mat[i][0] = new_mat[i][1];
        new_mat[i][l-1] = new_mat[i][l-2];
    }
    
    for(int i = 0 ; i < h ; i++)
      {delete old_mat[i];}
       delete old_mat;
       
    tool->matrix = new_mat;  
    tool->mat_h = h;
    tool->mat_w = l;
}

void gradient::add_chem_mat(int *chem)
{
  int l = tool->getImage()->width();
  int h = tool->getImage()->height();
  
    
//    std::cout << "largeur dans add_chem_mat : " << l << std::endl;
//    std::cout << "hauteur dans add_chem_mat : " << h << std::endl;
    int **m1 = wrap->retourner_noyau(NOYAU_GRADIENTX);
    int **m2 = wrap->retourner_noyau(NOYAU_GRADIENTY);
    
    int **old_mat = tool->matrix;
    //nouvelle matrice de taille w+1
    int **new_mat = new int*[h];
    for(int i = 0 ; i < h ; i++)
      {
        new_mat[i] = new int[l];
        for(int j = 0 ; j < l ; j++)
        {new_mat[i][j] = -1;}
      }
    //on remplit avec les anciennes valeurs
    for(int i = 1 ; i < h-1 ; i++)
    {
        //std::cout << "chem["<<i<<"] : "<<chem[i]<<std::endl;
        for(int j = 1 ; j < l-1 ; j++)
        {
            //si on est avant le chemin on recopie
            if(j < (chem[i]))
            {
                new_mat[i][j] = old_mat[i][j];
            }
            
            //si on est apres on decale de 1 pixel
            else if(j > (chem[i])+2)
            {
                new_mat[i][j] = old_mat[i][j];
            }
            //sinon on doit se taper le calcul de gradient
            //si on est pas sur les 4 bords
            else if(i > 0 && i < h-1 && j > 0 && j < l-1)
            {
               new_mat[i][j] = wrap->filtrage_gradient(i,j,m1);
               new_mat[i][j] += wrap->filtrage_gradient(i, j, m2);
              // std::cout << "mat["<<i<<"]["<<j<<"] : "<<new_mat[i][j] <<std::endl;
               
               

            } 
        }
    }
//    //2 extremites de l'ancien chemin
//    new_mat[0][chem[0]] = new_mat[1][chem[0]];
//    new_mat[h-1][chem[h-1]] = new_mat[h-2][chem[h-1]];
//    //nouveau chemin
//    new_mat[0][chem[0]+1] = new_mat[1][chem[0]+1];
//    new_mat[h-1][chem[h-1]+1] = new_mat[h-2][chem[h-1]+1];
//    //son pote de droite
//    new_mat[0][chem[0]+2] = new_mat[1][chem[0]+2];
//    new_mat[h-1][chem[h-1]+2] = new_mat[h-2][chem[h-1]+2];
    
    //bordure de gauche et de droite
    
    for(int i = 0 ; i < h ; i++)
    {
        new_mat[i][0] = new_mat[i][1];
        new_mat[i][l-1] = new_mat[i][l-2];
        new_mat[i][chem[i]] = 1.5*new_mat[i][chem[i]];
        new_mat[i][chem[i]+1] = 1.5*new_mat[i][chem[i]+1];
    }
    
    //bordure d'en haut et d'en bas
    
    for(int i = 0 ; i < l ; i++)
    {
        new_mat[0][i] = new_mat[1][i];
        new_mat[h-1][i] = new_mat[h-2][i];
    }
    
    
    for(int i = 0 ; i < h ; i++)
      {delete old_mat[i];}
       delete old_mat; 
       
    tool->matrix = new_mat;  
    tool->mat_h = h;
    tool->mat_w = l;
}


gradient::~gradient()
{
//    for(int i = 0 ; i < tool->getHeight() ; i++)
//       {delete matrixTemp[i];}
    
   // delete matrixTemp;
    //delete imageout;
    //delete wrap;
   // delete chem;
}