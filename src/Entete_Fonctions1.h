#ifndef __ENTETE_FONCTIONS1__
#define __ENTETE_FONCTIONS1__

#include "API_Grille.h"
#include "Liste_case.h"

//==========================================================================================//
//Exercice 1
//==========================================================================================//
/* Retourne dans L la liste des cases de meme couleur que la case i,j
   et met -1 dans ces cases */
void trouve_zone_rec(int **M, int nbcase,int i, int j, int *taille, ListeCase *L);//Version récursive


/* Algorithme tirant au sort une couleur: il utilise la fonction trouve_zone pour determiner la Zsg */
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff);//Version récursive



#endif  /* __ENTETE_FONCTIONS1__ */
