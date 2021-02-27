#ifndef ELTPRIM_H_INCLUDED
#define ELTPRIM_H_INCLUDED

#include "ELTSDD.h"


void binLire(bin * );

void binAfficher(bin , int, int );

void binAffecter(bin*, bin);

void binCopier(bin *, bin) ;

int binComparer(bin, bin);

bin binCreer(void) ;

void binDetruire (bin);

#endif // ELTPRIM_H_INCLUDED
