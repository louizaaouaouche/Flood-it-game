#ifndef __ENTETE_FONCTIONS2__
#define __ENTETE_FONCTIONS2__

#include "API_Grille.h"
#include "Liste_case.h"

//==========================================================================================//
//Exercice 2
//==========================================================================================//
/* Retourne dans L la liste des cases de meme couleur que la case i,j*/
void trouve_zone_imp(int **M, int nbcase,int i, int j, int *taille, ListeCase *L);//Version itérative

/* Algorithme tirant au sort une couleur: il utilise la fonction trouve_zone pour determiner la Zsg */
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff);//Version itérative


#endif  /* __ENTETE_FONCTIONS2__ */
