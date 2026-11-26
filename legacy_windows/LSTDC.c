
#include <stdlib.h>
#include <stdio.h>
#include "LSTPRIM.h"

/* implémentation des fonctions utiles pour la structure NOEUD */

NOEUD noeudCreer(bin b){
NOEUD n;
n =(NOEUD)malloc(sizeof(structNoeud));
if(!n)
	printf ("\nPlus d'espace");
else
	{
	binAffecter(&n->info, b);
	n->suivant = NULL;
	}
return n;
}
/* -------------------------------------------------- */
void noeudDetruire(NOEUD n){
binDetruire(n->info);
free(n);
}

/*----implémentation des primitive de la LISTE -------*/

int estVide(LISTE L) {
	return (L->lg == 0);
}
/* -------------------------------------------------- */

LISTE listeCreer(void)	{
	LISTE L;
	L=(LISTE)malloc(100*sizeof(laStruct));
	if (! L)
		printf("\nProblème de mémoire");
	else {
		L->lg = 0;
        L->tete = NULL; /* initialiser la tête */
		}
	return(L);
}

/* -------------------------------------------------- */
int estSaturee(LISTE L) {
	NOEUD temp;
	int saturee = 1; /* on suppose mémoire saturée */
	temp = (NOEUD) malloc ( sizeof ( structNoeud ) );
     if(temp != NULL)  {
		saturee = 0; /* mémoire non saturée */
		free(temp);
	}
	return saturee;
}
/* -------------------------------------------------- */
void listeDetruire(LISTE L){
int i;
NOEUD  p, q;
q= L->tete;
   for(i = 1;i <= L->lg; i++)
	{
	   p=q;
	   q=q->suivant;
	   noeudDetruire(p);
   }
   free(L);
}
/* -------------------------------------------------- */
void listeAfficher(LISTE L , int y ){
   NOEUD p;
   int x=1;
   for(p= L->tete;p!=NULL;p=p->suivant) {
        if (x>70){y=y+30;x=1;}
		binAfficher(p->info,x,y); x=x+12;

	}

	printf("\n\n\n");
}

/* -------------------------------------------------- */
LISTE listeCopier(LISTE L){

LISTE LR = listeCreer();

int i;
bin b;

   for(i = 1;i <= L->lg; i++) {

	    b=binCreer();
		binCopier(&b, recuperer(L,i));

		inserer(LR,b, i);
	}
 return LR;
}
/* -------------------------------------------------- */
int  listeComparer (LISTE L1,LISTE L2 )
{
int test= 1;
int i=1;

if (listeTaille(L1) != listeTaille(L2)) test= 0;

while ((i<=listeTaille(L1)) && (test)) {
	   if (binComparer(recuperer(L1,i),recuperer(L2,i))!=0)
		test=0;
	i++;
}

return test;
}

/* -------------------------------------------------- */
int listeTaille(LISTE L) {
   return (L->lg);
}
/* -------------------------------------------------- */
int inserer (LISTE L, bin b, int pos){
int succee=1;
int i;

NOEUD n, p, q;     // c des pointeurs sur noeud c equivalent à: 		 // structNoeud * n

if (estSaturee(L)){
	printf ("\nListe saturée");
	succee=0;}
else	{
	if  ((pos < 1) || (pos > L->lg + 1)) 	{
		printf ("\nPosition invalide");
		succee=0;
	}
	else	{
		n=noeudCreer (b); 			/*on est sûr que la réservation va se faire car la mémoire 	n'est pas saturée*/
		if (pos == 1)  /*insertion en tête de liste*/
			{
			n->suivant=L->tete;
			L->tete = n;
			}
			else	 /*cas général (pos > 1) */
		{
		q= L->tete;
		for (i=1; i<pos; i++) {
			p = q;
           	q = q->suivant;
		}
// q désigne l’élément de rang pos et p son prédécesseur
		p->suivant=n;
		n->suivant=q;
		}
	(L->lg)++;

	}
}

return succee;
}

/* -------------------------------------------------- */
int supprimer (LISTE L, int pos ){
	int i;
	int succee=1;
	NOEUD  p,  q;

  if (estVide(L))	{
		printf ("\nListe vide");
		succee=0;
		}
   else		{
		if   ((pos < 1) || (pos > L->lg))
			{
			printf ("\nPosition invalide");
			succee=0;
			}
		else
		 	{
              q = L->tete;
		          /*suppression en tête de liste*/
			  if (pos == 1)    L->tete=L->tete->suivant;
         else { /*cas général (pos > 1) */
	         for (i=1; i<pos; i++)
             {
		       p = q;
               q = q->suivant;
	         }
            p->suivant=q->suivant;
       }

	noeudDetruire(q);
    (L->lg)--;
  }
 }
return succee;
}

/* -------------------------------------------------- */
bin recuperer(LISTE L, int pos) {

	bin b= binCreer();
	int i;
	NOEUD p;

	if (estVide(L))
		printf ("\nListe vide");
	else	{
		if   ((pos < 1) || (pos > L->lg))
			printf ("\nPosition invalide");
		else	{
			p= L->tete;
			for (i=1; i<pos; i++)
			{p = p->suivant; }
			 binAffecter(&b,p->info);
			}
		}
	return(b);
}
/* -------------------------------------------------- */
