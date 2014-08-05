/* 
 * File:   rognage.h
 * Author: Adri
 *
 * Created on 8 janvier 2012, 23:22
 */

#ifndef ROGNAGE_H
#define	ROGNAGE_H

#include "outils.h"
#include "QImage"

class rognage {
public:
    rognage(outils *tool);
    void rognationner();
    virtual ~rognage();
private:
    
    outils *tool;

};

#endif	/* ROGNAGE_H */

