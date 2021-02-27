#ifndef LSTDC_H_INCLUDED
#define LSTDC_H_INCLUDED
#include "ELTPRIM.h"
 typedef struct structNoeud {
		bin info;
		struct structNoeud * suivant;
	}  structNoeud, * NOEUD;

typedef struct {
   NOEUD tete;
   int lg;
} laStruct,*LISTE;


#endif // LSTDC_H_INCLUDED
