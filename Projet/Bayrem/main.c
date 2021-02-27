#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "ELTPRIM.h"
#include "LSTPRIM.h"

void saisie (int Lobj [100] , int* n );
void afficher (int Lobj [100] , int ,int y);
void First_Fit(int Lobj [100] , int n,bin b1,int y);
void tri_selestion (int T [100], int n );
void Best_Fit_Decreasing(int Lobj [100] ,int n,bin b1,int y);
void binmodifier(bin* b , int x);

void main()
{
    int n,i,Lobj[100],y=10;
    bin b1 = binCreer();
    printf("\n\n     saisie du tableau \n\n");
    saisie (Lobj,&n);
    printf("\n\n     l'affichage du tableau \n\n");
    y=y+n;
    afficher (Lobj,n,y);
    printf("\n\n²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²\n\n");
    binLire(&b1);
    printf("\n²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²\n\n");
    printf("\n\n           ²²²²²²²²²²²²²²²²²²²²²²²  BIN PACKING ²²²²²²²²²²²²²²²²²²²²²²²\n\n");
    y=y+30;
    First_Fit(Lobj,n,b1,y);
    y=y+5;
    gotoxy(1,y);
    printf("======> l'affichage du liste remplie avec le first fit bin paking ");
    tri_selestion(Lobj,n);
    y=y+30;
    First_Fit(Lobj,n,b1,y);
    y=y+5;
    gotoxy(1,y);
    printf("======>  l'affichage du liste remplie avec le first fit Decreasing bin paking ");
    y=y+30;
    Best_Fit_Decreasing(Lobj,n,b1,y);
    y=y+5;
    gotoxy(1,y);
    printf("======>  l'affichage du liste remplie avec le Best fit Decreasing bin paking \n\n\n\n");


}

void saisie (int Lobj [100] , int* n  )
{
  int i;
  do { printf (" donner le nombre des objets   ");
      scanf ("%i",&(*n));

  }while (*n <= 0);

   for (i=0 ; i <(*n) ; i++)
    {
       printf ("donner la taille de l'objet %i = ",i+1);
      scanf("%i",&Lobj[i]);

   }
}

void afficher (int Lobj [100] , int n ,int  y )
{ int i,x ;

    x=1;
    for (i=0 ; i <n ; i++)
    { if (x>70){y=y+5;x=1;}
       Color(7);
       gotoxy (x,y);printf (" ||");Color(Lobj[i]+12);printf("²²²²²²²"); Color(7);printf("||\n");
       gotoxy (x,y+1);printf (" ||");Color(Lobj[i]+12); if (Lobj[i]<10){printf("²² %i ²²",Lobj[i]);}
                                               else {printf("²² %i ²",Lobj[i]);}; Color(7);printf("||\n");
       gotoxy (x,y+2);printf (" ||");Color(Lobj[i]+12);printf("²²²²²²²"); Color(7);printf("||\n");
       gotoxy (x,y+3);printf(" ===========\n");
       x=x+12;
   }

}

void First_Fit(int Lobj [100] , int n, bin b1,int y )
{

    LISTE L1=listeCreer();
    int i,a=0,j,k=1,T[100] ;

    memcpy(T, Lobj, sizeof(T));

  do
    {
    bin b = binCreer();
    b->Cbin=b1->Cbin;
    b->Nbobj=0;
    i=a;
     while (i<n)
     {
         if (T[i]<=b->Cbin){binmodifier(&b,T[i]);
                              for (j=i ; j<n-1 ; j++)
                                {
                                    T[j]=T[j+1];
                                }
                                n--;
                               }
        else {i++;}
     }

if (T[j]>b1->Cbin){a++;}
    inserer(L1,b,k);
    k++;
    }  while(a<n);

    listeAfficher(L1,y);

}



void Best_Fit_Decreasing(int Lobj [100] , int n,bin b1 ,int  y )
{
LISTE L3 = listeCreer();
NOEUD p ;

int tpos[100],c,M,k,j,d, i,T[100] ;

    memcpy(T, Lobj, sizeof(T));
for (i=0 ; i < n; i++)
{ if (T[i]<= b1->Cbin){
    p= L3->tete;
    for(c=0;c<L3->lg;c++)
   {
       tpos[c]= p->info->Cbin-T[i];
       p=p->suivant;
   }
   M=b1->Cbin;
   k=L3->lg+1;
   for (j=0 ; j < c ; j++)
   {
       if ((tpos[j]<M)&&(tpos[j]>= 0)){M=tpos[j];k=j+1;}
   }

   if (M==b1->Cbin){ bin b = binCreer();
                    b->Cbin=b1->Cbin;
                    b->Nbobj=0;
                     binmodifier(&b,T[i]);

                    inserer(L3,b,k);}
   else {p= L3->tete;
			for (d=1; d<k; d++)
			{p = p->suivant; }
                 binmodifier(&p->info,T[i]);

         }
}
}
listeAfficher(L3,y);
  }



void gotoxy(int x, int *y)
{
COORD c,k;
c.X = x - 1;
c.Y = y - 1;
SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);

}

Color(int couleurDuTexte) // fonction pour colorer le text
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDuTexte);
}

void binmodifier(bin* b , int x)
{
   (*b)->Tbin[(*b)->Nbobj]= x;
   (*b)->Nbobj++;
    (*b)->Cbin=(*b)->Cbin-x;
}
void tri_selestion (int T [100], int n )
{ int i ,m ,j ,c ;
    for (i = 0; (i < n-1); i ++)
     { m = i;
      for (j = i+1; (j < n); j ++)
       {
        if (T[j] > T[m]) { m = j; }
       }
      c = T[m];
      T[m] = T[i];
      T[i] = c;
    }
}
