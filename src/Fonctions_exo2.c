#include<stdio.h>
#include "Entete_Fonctions2.h"
/*=========================================================================
                                EXERCICE 2
  =========================================================================*/
  
void trouve_zone_imp(int **M, int nbcase, int i, int j, int *taille, ListeCase *L){

  /*Création de la pile */
	ListeCase Pile;
	init_liste(&Pile);
	ajoute_en_tete(&Pile, i, j);/*On empile la case (i,j)*/

  int couleur_ij = M[i][j]; 
  int get_i,get_j; /*Variables où on va récupérer les éléments dépilés*/

	while (!test_liste_vide(&Pile)) {
    /*On dépile*/
		enleve_en_tete(&Pile, &get_i, &get_j);
    
    /*Insertion de l'élément dépilé*/
    *taille = *taille + 1;
    ajoute_en_tete(L, get_i, get_j);
  
    int k,l;
        
    /*-------------------------Cases adjacentes------------------------------*/
    //On n'ajoute que les cases non présentes dans la Pile et la Liste L
    /*DROITE-----------------------------------------------------------------*/
    
    if (get_j+1 <= nbcase-1){
      if (couleur_ij == M[get_i][get_j+1]){ 
        
        //Vérification de la présence de la case (i,j+1) dans la Pile
        int flag = 0;
        Elnt_liste *elem=Pile;
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i) && (elem->j == get_j+1) ) {
            flag = 1; /* l'élément existant */
          }
          elem=elem->suiv;
        }
        //Vérification de la présence de la case (i,j+1) dans la Liste L
        elem=*L;
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i) && (elem->j == get_j+1) ) {
            flag = 1; /* l'élément existant */
          }
          elem=elem->suiv;
        }
        if (flag==0){
          ajoute_en_tete(&Pile, get_i, get_j+1);
        }
      }
      
    }
    /*HAUT -----------------------------------------------------------------*/
    if (get_i-1>= 0){
      if (couleur_ij == M[get_i-1][get_j]){
        int flag = 0;
        //Vérification de la présence de la case (i-1,j) dans la Pile
        Elnt_liste *elem=Pile;
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i-1) && (elem->j == get_j) ) {
            flag = 1; /* l'élément existe déjà dans la Pile */
          }
          elem=elem->suiv;
        }
        //Vérification de la présence de la case (i-1,j) dans la Liste L
        elem=*L;  
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i-1) && (elem->j == get_j) ) {
            flag = 1; /* l'élément existe déjà dans la Pile */
          }
          elem=elem->suiv;
        }
        if (flag==0){
          ajoute_en_tete(&Pile, get_i-1, get_j);
        }
      }
    }	
    /*GAUCHE-----------------------------------------------------------------*/
    if (get_j-1>= 0){
      if (couleur_ij == M[get_i][get_j-1]){
        int flag=0;
        //Vérification de la présence de la case (i,j-1) dans la Pile
        Elnt_liste *elem=Pile;
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i) && (elem->j == get_j-1) ) {
            flag = 1; /* l'élément existe déjà dans la Pile */
          }
          elem=elem->suiv;
        }
        //Vérification de la présence de la case (i,j-1) dans la Liste L
        elem=*L;  
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i) && (elem->j == get_j-1) ) {
            flag = 1; /* l'élément existe déjà dans la Liste L */
          }
          elem=elem->suiv;
        }
        if (flag==0){
          ajoute_en_tete(&Pile, get_i, get_j-1);
        }
      }
    }	
    /*BAS-----------------------------------------------------------------*/
    if (get_i+1 <= nbcase-1){
      if (couleur_ij == M[get_i+1][get_j]){
        int flag = 0;
        Elnt_liste *elem=Pile;
        //Vérification de la présence de la case (i+1,j) dans la Pile
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i+1) && (elem->j == get_j) ) {
            flag = 1; /* l'élément existe déjà dans la Pile */
          }
          elem=elem->suiv;
        }
        //Vérification de la présence de la case (i+1,j) dans la Liste L
        elem=*L;
        while ( (flag==0) && (elem!=NULL) ){
          if ( (elem->i == get_i+1) && (elem->j == get_j) ) {
            flag = 1; /* l'élément existe déjà dans la Pile */
          }
          elem=elem->suiv;
        }
        if (flag==0){
          ajoute_en_tete(&Pile, get_i+1, get_j);
        }
      }
    } 
  }
}
//=========================================================================================================//
int sequence_aleatoire_imp(int **M, Grille *G, int dim, int nbcl, int aff){
  int cpt=0;
  int tailleZsg;
  do {

    /*Identification de la zone supérieure gauche*/
    tailleZsg = 0;
    ListeCase ListeZsg;
    init_liste(&ListeZsg);
    trouve_zone_imp(M, dim, 0, 0, &tailleZsg, &ListeZsg);
    /*Tirage au sort d'une nouvelle couleur*/
    int couleur=rand()%nbcl;

    while (couleur==M[0][0]){
      couleur=rand()%nbcl;
    } 

    /* Modification de la couleur de la zone supérieure gauche par la nouvelle couleur */
    Elnt_liste *elem=ListeZsg;
    while(elem !=NULL) {
      M[elem->i][elem->j] = couleur;
      if(aff==1){
        Grille_attribue_couleur_case(G,elem->i,elem->j,couleur);
      }
      elem=elem->suiv;
    }

    /* Modification de la grille et affichage*/
    if (aff == 1) {
      Grille_redessine_Grille(G);
      //Grille_attente_touche();
    } 

    detruit_liste(&ListeZsg); 
    cpt ++;  
    
  }while(tailleZsg != dim*dim); /*Victoire non atteinte*/

  return cpt;
}


