#include<stdio.h>
#include "Entete_Fonctions1.h"
/*========================================================================
                                EXERCICE 1
 =========================================================================*/

void trouve_zone_rec(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){
  
  /*ajout de la case (i,j) à la liste L et mise à jour de la taille */
  ajoute_en_tete(L, i, j);
  *taille = *taille + 1;

  /* Vérification de l'état des cases adjacentes (BAS, GAUCHE, HAUT, DROITE)à (i,j)*/
  
  int couleur_ij = M[i][j];/*couleur de la case (i,j)*/

  /*BAS -----------------------------------------------------------------*/
  if (j+1 <= nbcase-1) {
    if (couleur_ij==M[i][j+1]) {

      //Vérification de la présence de la case (i,j) dans la liste L
      int flag = 0;
      Elnt_liste *elem=*L;
      while ( (flag==0) && (elem!=NULL) ){
        if ( (elem->i == i) && (elem->j == j+1) ) {
          flag = 1; //élément existe déjà dans la liste 
        }
        elem=elem->suiv;
      }
      if (flag==0) {
        trouve_zone_rec(M, nbcase, i, j+1, taille, L);
      }
    }
  }
  /*GAUCHE --------------------------------------------------------------*/
  if (i-1 >= 0) {
    //vérification de la couleur
    if (couleur_ij==M[i-1][j]) { 
      //Vérification de la présence de la case (i,j) dans la liste L
      int flag = 0;
      Elnt_liste *elem=*L;
      while ( (flag==0) && (elem!=NULL) ){
        if ( (elem->i == i-1) && (elem->j == j) ) {
          flag = 1; //élément existe déjà dans la liste
        }
        elem=elem->suiv;
      }
      if (flag==0) {
        trouve_zone_rec(M, nbcase, i-1, j, taille, L);
      }
    }
  }
  
  /*HAUT -----------------------------------------------------------------*/
  if (j-1 >=0) {
    //vérification de la couleur
    if (couleur_ij==M[i][j-1]) { 

      //Vérification de la présence de la case (i,j) dans la liste L
      int flag = 0;
      Elnt_liste *elem=*L;

      while ( (flag==0) && (elem!=NULL) ){
        if ( (elem->i == i) && (elem->j == j-1) ) {
          flag = 1; //élément existe déjà dans la liste
        }
        elem=elem->suiv;
      }
      if (flag==0) {
        trouve_zone_rec(M, nbcase, i, j-1, taille, L);
      }
    }
  }
  

  /*DROITE-----------------------------------------------------------------*/
  if (i+1 <= nbcase-1) {
    //vérification de la couleur
    if (couleur_ij==M[i+1][j]) { 
      //Vérification de la présence de la case (i,j) dans la liste L
      int flag = 0;
      Elnt_liste *elem=*L;
      while ( (flag==0)  && (elem!=NULL) ){
        if ( (elem->i == i+1) && (elem->j == j) ) {
          flag = 1; //élément existe déjà dans la liste
        }
        elem=elem->suiv;
      }
      if (flag==0) {
        trouve_zone_rec(M, nbcase, i+1, j, taille, L);
      }
    }
  }
}

//=========================================================================================================//
int sequence_aleatoire_rec(int **M, Grille *G, int dim, int nbcl, int aff){
  
  int cpt=0;
  
  /*Identification de la zone supérieure gauche*/
  int tailleZsg = 0;
  ListeCase ListeZsg;
  init_liste(&ListeZsg);
  trouve_zone_rec(M, dim, 0, 0, &tailleZsg, &ListeZsg);
  
  int couleur;
  
  if (tailleZsg != dim*dim) { /*Victoire non atteinte */
    /*Tirage au sort d'une nouvelle couleur*/
    couleur=rand()%nbcl;

    while (couleur==M[0][0]){
      couleur=rand()%nbcl;
    } 

    /* Modification de la couleur de la zone supérieure gauche par la nouvelle couleur */
    Elnt_liste *elem=ListeZsg;
    while(elem !=NULL) {
      M[elem->i][elem->j] = couleur;
      if (aff==1){
        Grille_attribue_couleur_case(G,elem->i,elem->j,couleur);
      }

      elem=elem->suiv;
    }

    /* Affichage de la grille*/
    if (aff == 1) {
      Grille_redessine_Grille(G);
      //Grille_attente_touche();
    }

    detruit_liste(&ListeZsg);

    /*Victoire non atteinte donc on effectue un appel récursif */ 
    cpt =1+ sequence_aleatoire_rec(M, G, dim, nbcl, aff);
    
    return cpt;
    
  }else{
    detruit_liste(&ListeZsg);
    return cpt;
  }
  
}


