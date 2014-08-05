/* 
 * File:   ciseau.cpp
 * Author: light
 * 
 * Created on 18 janvier 2012, 16:53
 */
#include "ciseau.h"

ciseau::ciseau(outils *t) {
    tool = t;
    wrap = new wraperTraitement(tool);
}

ciseau::~ciseau() {
}

void ciseau::contour(int x1, int y1, int x2, int y2, int seuil) {
    matrixTemp = wrap->_conv_gradient(3);
    
    //dijkstra(0,8,8,8,m);
    tool->decoupagePossible = true;
    astar(y1, x1, y2, x2,seuil);
    //astar(649,0,649,1000,m);

}

int ciseau::astar(int x, int y, int x2, int y2, int seuil) {
    //cout<<"depart "<<x<<" "<<y<<" arrive "<<x2<<" "<<y2<<"\n";
    
    if(tool->imageTemp){
        imageIn = tool->getImageTraite();
    }else{
        imageIn = tool->getImage();
    }
    
    int l = imageIn->width();
    int h = imageIn->height();
    QImage *temp = new QImage(*imageIn);
    imageIn =temp;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            matrixTemp[i][j] = matrixTemp[i][j]/seuil;

        }
    }
    
    //init matrice traite
    traite = new int * [h];
    for (int i = 0; i < h; i++) {
        traite[i] = new int[l];
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < l; j++) {
            traite[i][j] = -1;
        }
    }
    
    //creation du noeud depart et arrive
    int dist;
    element dep(x, y, 0);
    traite[x][y] = 0;
    element arrive(x2, y2, 0);
    //liste des noeuds a traiter
    priority_queue<element, vector<element>, C> queue;
    queue.push(dep);
    element tmp;
    while (!queue.empty()) {
        tmp = queue.top();
        queue.pop();
        //si fin
        if ((tmp.x == arrive.x && tmp.y == arrive.y)) {
            break;
        }
        //traitons les successeurs
        successeur(tmp.x, tmp.y, h, l);
        while (!successeurQueue.empty()) {
            element succ = successeurQueue.front();
            successeurQueue.pop();

            int xx = arrive.x - tmp.x;
            if (xx < 0) {
                xx = -xx;
            }
            int yy = arrive.y - tmp.y;
            if (yy < 0) {
                yy = -yy;
            }
            dist = xx + yy; //distance de manhattan
            succ.poid = tmp.poid + 1 + matrixTemp[succ.x][succ.y];
            succ.poidPot = succ.poid + dist;
            queue.push(succ);
            traite[succ.x][succ.y] = succ.poid;
        }
    }

    
    affiche_chemin(arrive, dep, h, l);
    tool->setImageTraite(imageIn);
    return 1;
}
//retourne les successeurs ne prend que les non traite

void ciseau::successeur(int x, int y, int h, int l) {

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < h && j >= 0 && j < l && traite[i][j] == -1) {
                element tmp(i, j, 0);
                successeurQueue.push(tmp);
                traite[i][j] = -1;
            }
        }
    }

}
//idem mais prend que les traites

void ciseau::successeur2(int x, int y, int h, int l) {

    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < h && j >= 0 && j < l && traite[i][j] != -1) {
                element tmp(i, j, 0);
                successeurQueue.push(tmp);
                //cout<<"ajoute "<<i<<" "<<j<<"\n";
            }
        }
    }

}

void ciseau::affiche_chemin(element arrive, element depart, int h, int l) {
    //cout<<"affichage du chemin\n";
//    QFile file("out.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;
//    QTextStream out(&file);
//    for(int i=0;i<h;i++){
//        for(int j=0;j<l;j++){
//            out<<matrixTemp[i][j]<<"   ";
//        }
//        out<<"\n";
//    }
    //cout<<"depart "<<depart.x<<" "<<depart.y<<" "<<matrixTemp[depart.x][depart.y]<<"\n";
    //cout<<"arrive "<<arrive.x<<" "<<arrive.y<<" "<<matrixTemp[arrive.x][arrive.y]<<"\n";
    element top = arrive;
    top.poid = 2000000;
    element tmp;
    while (!successeurQueue.empty()) {
        successeurQueue.pop();
    }
    imageIn->setPixel(depart.y, depart.x, 0xFFFF0000);
    successeur2(top.x, top.y, h, l);
    int trouve = 0;
    while (trouve == 0 && !successeurQueue.empty()) {

        while (!successeurQueue.empty()) {
            tmp = successeurQueue.front();
            successeurQueue.pop();
            if (tmp.x == depart.x && tmp.y == depart.y) {
                //imageIn->save("chemin.png");
                //tool->setImage(imageIn);
                trouve = 1;
                break;
            }
            if (traite[tmp.x][tmp.y] <= traite[top.x][top.y]) {
                //cout<< top.x<<" "<<top.y<<" "<<traite[top.x][top.y]<<"\n";
                top = tmp;
                position aba(top.x,top.y);
   
                tool->pixel.push_back(aba);
                imageIn->setPixel(top.y, top.x, 0xFFFF0000);
            }

        }
        successeur2(top.x, top.y, h, l);
    }

//    if (trouve) {
//        cout << "chemin trouver\n";
//    } else {
//        cout << "chemin pas remontable\n";
//    }
}

void ciseau::decouperImage(){
    QImage *in = tool->getImage();
    QImage *temp = new QImage(*tool->getImage());
    position elem(0,0);
    for(int i=0;i<temp->width();i++){
        for(int j=0; j<temp->height();j++){
            temp->setPixel(i,j,0xFFFFFFFF);
        }
    }
    while(!tool->pixel.empty()){
        elem = tool->pixel.front();
        temp->setPixel(elem.y,elem.x,0xFF000000);
        tool->pixel.pop_front();
    }
//    bool dessin = false;
//    for(int i=0;i<temp->width();i++){
//        for(int j=0; j<temp->height();j++){
//            if(temp->pixel(i,j)==0xFF000000){
//                dessin = true;
//            }
//            if(dessin){
//                temp->setPixel(i,j,in->pixel(i,j));
//            }
//        }
//        dessin = false;
//    }
    
    tool->setImage(temp);
}

//void ciseau::calculeGradient(int seuil){
//    QColor color;
//    int red = 0, green = 0, blue = 0, aa = 0;
//    int tmpPrec=0, tmp;
//    //init de matrix temp
//    matrixTemp = new int * [imageIn->height()];
//    for (int i = 0; i < imageIn->height(); i++) {
//        matrixTemp[i] = new int[imageIn->width()];
//    }
//    //Recherche des details sur y
//    for (int i = 0; i < imageIn->width(); i++) {
//        for (int j = 0; j < imageIn->height(); j++) {
//
//            color.setRgb(imageIn->pixel(i, j));
//            color.getRgb(&red, &blue, &green, &aa);
//
//            tmp = (red + green + blue) / 3 - tmpPrec;
//            if (tmp > seuil || tmp < -1 * seuil) {
//                tmp = 255;
//            } else {
//                tmp = 0;
//            }
//            matrixTemp[j][i]=tmp;
//            tmpPrec = (red+blue+green)/3;
//        }
//        color.setRgb(imageIn->pixel(i, 0));
//        color.getRgb(&red, &blue, &green, &aa);
//        tmpPrec = (red+blue+green)/3;
//
//    }
//    //RAZ des valeurs entre 2 passes
//    red = 0;
//    green = 0;
//    blue = 0;
//    tmpPrec = 0;
//    //Recherche des details sur x
//    for (int i = 0; i < imageIn->height(); i++) {
//        for (int j = 0; j < imageIn->width(); j++) {
//
//            color.setRgb(imageIn->pixel(j, i));
//            color.getRgb(&red, &blue, &green, &aa);
//            tmp = (red + green + blue) / 3 - tmpPrec;
//            if (tmp > seuil || tmp < -1 * seuil) {
//                tmp = 255;
//            } else {
//                tmp = 0;
//            }
//            tmpPrec = (red+blue+green)/3;
//            matrixTemp[j][i]=tmp;
//        }
//        color.setRgb(imageIn->pixel(0, i));
//        color.getRgb(&red, &blue, &green, &aa);
//        tmpPrec = (red+blue+green)/3;
//    }
//}

//int ciseau::dijkstra(int x, int y,int x2,int y2, int **elem) {
//    //init matrice a +infini
//    QImage *imageIn = tool->getImage();
//    int l = imageIn->width();
//    int h = imageIn->height();
//    
//    matrixTemp = new int * [h];
//    for (int i = 0; i < h; i++) {
//        matrixTemp[i] = new int[l];
//    }
//    for (int i = 0; i < h; i++) {
//        for (int j = 0; j < l; j++) {
//            matrixTemp[i][j] = 2000000000;
//        }
//    }
//    QQueue<element>queue;
//    //on met �  0 le poids du 1er element
//    matrixTemp[x][y] = 0;
//    
//    element dep(x, y, 0); 
//    queue.enqueue(dep);
//    //DI.J.RA en lui meme
//    while (!queue.isEmpty()) {
//        element tmp = queue.dequeue();
//        //si on ne depile pas le point de fin
//        if(!(tmp.x == x2 && tmp.y == y2)){
//            if ((tmp.y) - 1 >= 0 && (tmp.x)+1 < h)
//            {
//                //gauche(x-1 , y , poids(x,y) + poids(x-1,y) , 0)
//                element gauche(tmp.x + 1, tmp.y - 1, matrixTemp[tmp.x][tmp.y] + tool->matrix[tmp.x + 1][tmp.y-1]);
//                if (gauche.poid < matrixTemp[tmp.x + 1][tmp.y - 1]) {
//                    matrixTemp[tmp.x + 1][tmp.y - 1] = gauche.poid;
//                    queue.enqueue(gauche);
//                }
//            }
//
//            if ((tmp.y) + 1 < l && (tmp.x) + 1 < h)
//            {
//                element droite(tmp.x+1, tmp.y+1, matrixTemp[tmp.x][tmp.y]+ tool->matrix[tmp.x+1][tmp.y+1]);
//                if (droite.poid < matrixTemp[tmp.x+1][tmp.y+1]) {
//                    matrixTemp[tmp.x+1][tmp.y+1] = droite.poid;
//                    queue.enqueue(droite);
//                }
//            }
//
//            if ((tmp.x) + 1 < h)
//            {
//                element dessous(tmp.x + 1, tmp.y, matrixTemp[tmp.x][tmp.y] + tool->matrix[tmp.x + 1][tmp.y]);
//                if (dessous.poid < matrixTemp[tmp.x + 1][tmp.y]) {
//                    matrixTemp[tmp.x + 1][tmp.y] = dessous.poid;
//                    queue.enqueue(dessous);
//                }
//            }
//        }else{
//            cout<<"trouve\n";
//            break;
//        }
//    }
//
//    int val_cour_chem=2000000000;
//    
//    int num;
//    
////    for(int i=0;i<l;i++){
////        if(matrixTemp[h-1][i]<val_cour_chem){
////            num = i;
////            val_cour_chem = matrixTemp[h-1][i];
////        }
////    }
//
////    int hauteur = h-1;
////    int a,b,c;
////    
////    elem[0] = x;
////    int val_x;
////    while(hauteur >= 0){
////        
////        b=matrixTemp[hauteur][num];
////        val_x = num;
////        if(num-1>0){
////                a=matrixTemp[hauteur][num-1];
////                if(a<b){
////                    b=a;
////                    val_x = num-1;
////                }
////        }
////        if(num<l-1){
////            c=matrixTemp[hauteur][num+1];
////            if(c<b){
////                b=c;
////                val_x = num+1;
////            }
////        }
////         elem[hauteur] = val_x;
////         //std::cout << temp << std::endl;
////        num = val_x;
////      hauteur--;
////    }
//    
//    for(int i=0;i<h;i++){
//        for(int j=0;j<l;j++){
//            std::cout<<matrixTemp[i][j]<< " ";
//        }
//        std::cout<<"\n";
//    }
//    return val_cour_chem;
//    return 0;
//}
