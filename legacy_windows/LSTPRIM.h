#ifndef LSTPRIM_H_INCLUDED
#define LSTPRIM_H_INCLUDED

#include "ELTPRIM.h"
#include "LSTSDD.h"

LISTE listeCreer(void);
void listeDetruire(LISTE);
int estVide(LISTE);
int estSaturee(LISTE);
int listeTaille(LISTE);
bin recuperer(LISTE, int);
int inserer(LISTE, bin,int);
int supprimer(LISTE, int);
void listeAfficher(LISTE, int );
LISTE listeCopier(LISTE);
int  listeComparer(LISTE, LISTE);


#endif // LSTPRIM_H_INCLUDED
