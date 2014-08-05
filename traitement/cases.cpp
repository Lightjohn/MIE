/* 
 * File:   cases.cpp
 * Author: Adri
 * 
 * Created on 23 janvier 2012, 21:02
 */

#include "cases.h"

cases::cases(int pos_x, int pos_y, int pixel)
{
 x = pos_x;
 y = pos_y;
 pix = pixel;
 actif = true;
case_tab = -1;
 
}
cases::cases()
{
     actif = true;
     case_tab = -1;
}

cases::~cases()
{
//    delete suivant;
//    delete precedent;
}

