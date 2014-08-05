/* 
 * File:   cases.h
 * Author: Adri
 *
 * Created on 23 janvier 2012, 21:02
 */

#ifndef CASES_H
#define	CASES_H

class cases {
public:
    cases(int pos_x, int pos_y, int pixel);
    cases();
    int x;
    int y;
    int pix;
    cases *suivant;
    cases *precedent;
    int grad;
    bool actif;
    int case_tab;
    virtual ~cases();
private:

};

#endif	/* CASES_H */

