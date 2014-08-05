#ifndef NIVEAUDEGRIS_H
#define NIVEAUDEGRIS_H
#include "wrapertraitement.h"
#include "outils.h"
using namespace std;
class NiveauDeGris
{
public:
    NiveauDeGris(outils *o);

    int couleurToGris(int red, int green, int blue);
    void PassageNiveauDeGris();
    virtual ~NiveauDeGris();
private:
    outils *tool;

};

#endif // NIVEAUDEGRIS_H
