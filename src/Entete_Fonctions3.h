#ifndef __ENTETE_FONCTIONS3__
#define __ENTETE_FONCTIONS3__

#include "API_Grille.h"
#include "Liste_case.h"

//==========================================================================================//
//Exercice 3
//==========================================================================================//


/*Structure S_Zsg*/
typedef struct {
   int dim;          /* dimension de la grille */
   int nbcl;         /* nombre de couleurs */
   ListeCase Lzsg;   /* Liste des cases de la zone Zsg */ 
   ListeCase *B;     /* Tableau de listes de cases de la bordure*/ 
   int **App;        /* Tableau a double entree des appartenances */
}S_Zsg;

/* Initialise la structure S_Zdg*/
void init_Zsg(S_Zsg **Zsg,int dim, int nbcl );

/*Ajoute la case (i,j) dans la liste LZsg en tête (pour que ce soit en O(1)*/
void ajoute_Zsg (S_Zsg *Zsg,int i, int j);

/*Ajoute une case dans la bordure d’une couleur cl donnée; */
void ajoute_Bordure(S_Zsg *Zsg,int i, int j,int cl);

/*Renvoie vrai si une case est dans LZsg */
int appartient_Zsg(S_Zsg *Zsg,int i, int j);

/*Renvoie vrai si une case est dans la bordure de couleur cl donnée*/
int appartient_Bordure(S_Zsg *Zsg,int i,int j,int cl);

/* Libere la structure Zsg*/
void detruit_Zsg(S_Zsg *Zsg);

/* Mise a jour des champs d'une S_Zsg, et retourne le nombre de cases ajoutées*/
int agrandit_zone(int **M, S_Zsg *Z, int cl, int k, int l);

/* Renvoie le nombre de couleurs necessaires pour gagner, en faisant appel à la 
fonction agrandit_zone*/
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff);

#endif  /* __ENTETE_FONCTIONS3__ */
