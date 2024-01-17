#ifndef __ENTETE_FONCTIONS6__
#define __ENTETE_FONCTIONS6__

#include "API_Grille.h"
#include "Entete_Fonctions4.h"
#include "Entete_Fonctions5.h"

//==========================================================================================//
//Exercice 6
//==========================================================================================//

/*Remplie les champs "distant" et "pere" à partir de Racine, de sorte 
à ce que distant soit le plus petit possible */
void plus_court_chemin(Graphe_zone *G, Sommet *Racine);

int strategie_parcours_largeur(int **M, Grille *G, int dim, int nbcl, int aff);

//------------------------------ MISE A JOUR FONCTION EXO5 --------------------------------

/*renvoie le graphe_zone associé à la grille de jeu M
  Modification: ajout champs distant et pere dans la structure*/
Graphe_zone *creer_graphe_zone3(int **M, int dim);

/*renvoie la taille de la séquence pour gagner le jeu de la grille G à partir du graphe Gr et sa bordure B
A noter que dans cet exercice on appelle cette fonction apres un premier parcours entre Zsg et Zid*/
int strategie_max_bordure2( Grille *G,Graphe_zone *Gr,Bordure_graphe *B, int dim, int nbcl, int aff);
#endif  /* __ENTETE_FONCTIONS6__ */
