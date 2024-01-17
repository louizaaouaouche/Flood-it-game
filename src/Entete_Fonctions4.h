#ifndef __ENTETE_FONCTIONS4__
#define __ENTETE_FONCTIONS4__

#include "API_Grille.h"
#include "Entete_Fonctions1.h"

//==========================================================================================//
//Exercice 4
//==========================================================================================//
 typedef struct sommet Sommet;
 /* Element d’une liste chainée de pointeurs sur Sommets */
 typedef struct cellule_som{
    Sommet * sommet;
    struct cellule_som * suiv;
} Cellule_som;

struct sommet{ 
   int num;                   /* Numero du sommet (sert uniquement a l’affichage) */
   int cl;                    /* Couleur d’origine du sommet-zone */
   ListeCase cases;           /* Listes des cases du sommet-zone */
   int nbcase_som;            /* Nombre de cases de cette liste */
   Cellule_som * sommet_adj;  /* Liste des arêtes des pointeurs sur les sommets adjacents */

   //Apparition à partir de EXO 5:

   int marque;                /* vaut 0 si le sommet est dans la Zsg, 1 dans la bordure, 2 s'il est non visite */

   //Apparition à partir de EXO 6:
   int distance;              /* Nombre d’aretes reliant ce sommet a la racine
                              du parcours en largeur */
   Sommet *pere;              /* Pere du sommet dans l’arborescence du parcours en largeur */

};

typedef struct graphe_zone{
   int nbsom;                 /* Nombre de sommets dans le graphe */
   Cellule_som *som;          /* Liste chainee des sommets du graphe */
   Sommet ***mat;             /* Matrice de pointeurs sur les sommets indiquant a quel sommet appartient une case (i,j) de la grille */
} Graphe_zone;


/*ajoute le sommet S à la liste L, renvoie faux si problème d'allocation*/
int ajoute_liste_sommet(Cellule_som **L,Sommet *S);

/*détruit la liste chainée L sans détruire les sommets pointés par cette liste */
void detruit_liste_sommet(Cellule_som *L);

/*Ajoute s1 (resp s2) à la liste d'adjacence de s2 (resp s1)*/
void ajoute_voisin(Sommet *s1, Sommet *s2);

/*Renvoie vrai (1) si s1 et s2 sont adjacents, faux (0) sinon*/
int adjacent(Sommet *s1, Sommet *s2);

/*renvoie le graphe_zone associé à la grille de jeu M*/
Graphe_zone *creer_graphe_zone(int **M, int dim);

/*libère la mémoire allouée à G*/
void detruit_graphe_zone(Graphe_zone *G,int dim);

/*Affiche le contenu du graphe zone G en paramètre*/
void affichage_graphe(Graphe_zone *G);

#endif  /* __ENTETE_FONCTIONS4__ */
