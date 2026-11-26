#include <stdio.h>
#include <stdlib.h>
#include "ELTPRIM.h"


void binLire(bin* b )
{ (*b)->Nbobj=0;
  do {
  printf ("donner la taille du bin ");
  scanf ("%i",&(*b)->Cbin);

  }while ((*b)->Cbin<0);
 (*b)->Tbin[(*b)->Nbobj]=0;
}


void binAfficher(bin b , int x,int y )
{
    int i;

     for (i=0 ; i <b->Nbobj  ; i++)
    {
       Color(7);
      gotoxy (x,y);printf (" ||");Color(b->Tbin[i]+12);printf("²²²²²²²"); Color(7);printf("||\n");
      gotoxy (x,y+1);printf (" ||");Color(b->Tbin[i]+12); if (b->Tbin[i]<10){printf("²² %i ²²",b->Tbin[i]);}
                                               else {printf("²² %i ²",b->Tbin[i]);}; Color(7);printf("||\n");
       gotoxy (x,y+2);printf (" ||");Color(b->Tbin[i]+12);printf("²²²²²²²"); Color(7);printf("||\n");
       gotoxy (x,y+3);printf(" ===========\n");
       y=y-4;
   }



}
void binAffecter(bin* b1 , bin b2)
{
    *b1 = b2 ;
}
void binCopier(bin* b1 , bin b2)
{
	memcpy(*b1,b2,sizeof(BIN));
}

int binComparer(bin b1 , bin b2 )
{
    int s1=0,s2=0,i;
    for (i=0 ;  i < b1->Nbobj ; i++ )
    {
        s1 = s1 + b1->Tbin[i];
    }
    for (i=0 ;  i < b2->Nbobj ; i++ )
    {
        s2 = s2 + b2->Tbin[i];
    }
    if (s1>s2){return 1;}
    else if (s1<s2) {return -1;}
    else return 0 ;
}

bin binCreer()
{
  bin b;
    b = (bin)malloc(sizeof(BIN));
    if(b==NULL)
	printf("impossible de faire la creation de votre bin");
	return b;
}

void binDetruire (bin b )
{
      free (b);
}
