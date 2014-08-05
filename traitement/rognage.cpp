/* 
 * File:   rognage.cpp
 * Author: Adri
 * 
 * Created on 8 janvier 2012, 23:22
 */

#include "rognage.h"

rognage::rognage(outils *tool)
{
    this->tool = tool;
    
}

void rognage::rognationner()
{
QImage *imagerogn = new QImage(tool->rect_selection->width(),tool->rect_selection->height(),tool->getImage()->format());


QImage *origin;
if(tool->getZoomFactor()==1)
    origin= tool->getImage();
else
    origin=tool->getImageZoomee();

int k = 0;

 for(int i = tool->rect_selection->x() ; i < tool->rect_selection->width()+tool->rect_selection->x() ; i++)
    {int l = 0;
   for(int j = tool->rect_selection->y() ; j < tool->rect_selection->height()+tool->rect_selection->y() ; j++)
      {
       QRgb rgb = origin->pixel(i,j);
       imagerogn->setPixel(k,l,(uint)rgb);
       l++;
      }
    k++;
    }

 tool->supression_cadre_selection();
 tool->rect_selection->setRect(0,0,0,0);
 tool->setImageTraite(imagerogn);
}

rognage::~rognage()
{
    
}

