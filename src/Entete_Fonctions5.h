#ifndef __ENTETE_FONCTIONS5__
#define __ENTETE_FONCTIONS5__

#include "API_Grille.h"
#include "Entete_Fonctions1.h"
#include "Entete_Fonctions4.h"

//==========================================================================================//
//Exercice 5
//==========================================================================================//

typedef struct{
  Cellule_som *Zsg;           /* Suite de sommets constituant la Zsg */
 
  Cellule_som **ListeSom;     /* Bordure = Tableau de listes chainées de pointeurs sur les sommets-zones par couleur */
  int *TabLen;                /* Tailles des listes de la bordure (dans BorSom) par couleur*/

  int NbElemTab;              /* nombre total d'élements dans le tableau Tablen */
}Bordure_graphe;

/*Crée et initialise la structure Bordure_Graphe selon les données dans la structure G*/
Bordure_graphe *cree_graphe_bordure(Graphe_zone *G,int nbcl);

/*Met à jour la bordure B du graphe zone G après un tour de jour illustré par le choix de
  la couleur cl*/
void maj_bordure_graphe(Graphe_zone *G,Bordure_graphe *B,int cl);

/*Renvoie la taille de la séquence qui résoud la grille en optant pour la couleur dominante 
  de la bordure de la Zsg à chaque tour*/
int strategie_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff);

/*libère la mémoire allouée à B*/
void detruit_bordure_graphe(Bordure_graphe *B,int nbcl);



//------------------------------ MISE A JOUR FONCTIONS EXO4 -------------------------------

/*renvoie le graphe_zone associé à la grille de jeu M
 modification: ajout du champ marque*/
Graphe_zone *creer_graphe_zone2(int **M, int dim);

#endif  /* __ENTETE_FONCTIONS5__ */
