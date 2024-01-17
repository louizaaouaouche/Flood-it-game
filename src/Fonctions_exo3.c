#include<stdio.h>
#include<stdlib.h>
#include "Entete_Fonctions3.h"

/*=========================================================================
                                EXERCICE 3
 =========================================================================*/

/* 3.1 =========================================================================*/

/* Initialise la structure S_Zsg*/
void init_Zsg(S_Zsg **Zsg,int dim, int nbcl ){
    //Allocation    
    (*Zsg)=(S_Zsg *)malloc(sizeof(S_Zsg));
    if ((*Zsg)==NULL){
        printf("Pas assez d'espace mémoire disponible pour Zsg\n");
        exit(EXIT_FAILURE);
    }
   
    /*Initialisation des champs avec vérification du bon déroulement de l'allocation*/
    (*Zsg)->dim=dim;
    (*Zsg)->nbcl=nbcl;

    /*Lzsg vide initialement*/
    (*Zsg)->Lzsg=NULL;
   
    /*tableau B*/
    (*Zsg)->B = (ListeCase *)malloc(nbcl * sizeof(ListeCase));
    if((*Zsg)->B==NULL){
    printf("Pas assez d'espace mémoire disponible pour Zsg->B\n");
      exit(EXIT_FAILURE);
    }
   
	for (int i = 0; i < nbcl; i++){
		(*Zsg)->B[i] = NULL;
    }

    /*Matrice  app*/
    (*Zsg)->App = (int **)malloc(dim*sizeof(int *));
    if((*Zsg)->App==NULL){
        printf("Pas assez d'espace mémoire disponible pour Zsg->app\n");
        exit(EXIT_FAILURE);
    }
    int i;
	for (i = 0; i < dim; i++){
	    (*Zsg)->App[i] = (int *)malloc(dim * sizeof(int));
        if((*Zsg)->App[i]==NULL){
            printf("Pas assez d'espace mémoire disponible pour Zsg->App[%d]\n",i);
            exit(EXIT_FAILURE);
        }
        int j;
        for(j=0; j<dim;j++){
            (*Zsg)->App[i][j]=-2; // case (i,j) n'est ni dans Lzsg ni dans B
        }
    }

}

/*=========================================================================*/
/*Ajoute la case (i,j) dans la liste Lzsg en tête (pour que ce soit en O(1)*/
void ajoute_Zsg (S_Zsg *Zsg,int i, int j){
   //Ajout
   ajoute_en_tete(&(Zsg->Lzsg),i,j);
   //Mise ajout de l'element dans la matrice App
   Zsg->App[i][j]=-1;
}
/*=========================================================================*/
/*Ajoute une case dans la bordure d’une couleur cl donnée; */
 void ajoute_Bordure(S_Zsg *Zsg,int i, int j,int cl){
   //Ajout
    ajoute_en_tete(&(Zsg->B)[cl], i, j);
   //Mise ajout de l'element dans la matrice App
   Zsg->App[i][j]=cl;
 }
 /*=========================================================================*/
/*Renvoie vrai si une case est dans Lzsg */
int appartient_Zsg(S_Zsg *Zsg,int i, int j){
   /*Utilisation de l'accès au tableau pour obtenir du O(1)*/

   return Zsg->App[i][j]==-1;
}
/*=========================================================================*/
/*Renvoie vrai si une case est dans la bordure de couleur cl donnée*/
int appartient_Bordure(S_Zsg *Zsg,int i,int j,int cl){
   /*Utilisation de l'accès au tableau pour obtenir du O(1)*/
   return Zsg->App[i][j]==cl;
}
/*=========================================================================*/
/* Libere la structure Zsg*/
void detruit_Zsg(S_Zsg *Zsg) {
    if (Zsg!=NULL){
        /*libere Zsg->Lzsg*/
        detruit_liste(&(Zsg->Lzsg));

        int i;
        /*Libere Zsg->B*/
        for (i = 0; i < Zsg->nbcl; i++) {
            detruit_liste(&  ((Zsg->B)[i])  );
        }
        free(Zsg->B);

        /*Libere Zsg->app*/
        for (i = 0; i < Zsg->dim; i++) {
            free((Zsg->App)[i]);
        }
        free(Zsg->App);

        /*Libere Zsg*/
        free(Zsg);
    }
    
}
/* 3.2 =========================================================================*/
/* Mise a jour des champs d'une S_Zsg, et retourne le nombre de cases ajoutées*/
int agrandit_zone(int **M, S_Zsg *Z, int cl, int k, int l){
    int cpt=0;

	ListeCase Liste;
	init_liste(&Liste);
	ajoute_en_tete(&Liste, k, l);

	while (Liste!=NULL) {
        int i,j; /*Variables où on va récupérer les éléments dépilés*/
        /*On dépile*/
		enleve_en_tete(&Liste, &i, &j);
    
 
        if(M[i][j]==cl){
            if (!appartient_Zsg(Z,i,j)){
                ajoute_Zsg(Z, i, j);
                cpt++;
                 //HAUT
                if (i-1>=0 ){
                    ajoute_en_tete(&Liste, i - 1, j);
                }
                //GAUCHE
                if(j-1 >=0){
                    ajoute_en_tete(&Liste, i, j - 1);
                }
                //BAS
                if(i+1<=Z->dim-1){
                    ajoute_en_tete(&Liste, i + 1, j);
                }
                //DROITE
                if(j+1<=Z->dim-1){
                    ajoute_en_tete(&Liste, i, j + 1);
                } 
            }
        }else if(!appartient_Bordure(Z, i, j, M[i][j])){
            ajoute_Bordure(Z, i, j, M[i][j]);
        }
        
    }
    detruit_liste(&Liste);
    return cpt;
}

/* 3.3 =========================================================================*/
/* Renvoie le nombre de couleurs necessaires pour gagner, en faisant appel à la 
fonction agrandit_zone*/
int sequence_aleatoire_rapide(int **M, Grille *G, int dim, int nbcl, int aff) {
    int cpt=0;

    S_Zsg *Zsg;
    init_Zsg(&Zsg, dim, nbcl);
    int taille = agrandit_zone(M, Zsg, M[0][0], 0, 0);
    while (taille != dim * dim) {
        /*Tirage au sort d'une nouvelle couleur*/
        int couleur=rand()%nbcl;
        while (couleur==M[0][0]){
            couleur=rand()%nbcl;
        } 

        /*Mise à jour des couleurs de la Zsg */
        Elnt_liste *elem=Zsg->Lzsg;
        while(elem !=NULL) {
            M[elem->i][elem->j] = couleur;
            if (aff==1) {
                /*Mise à jour des couleurs de la Zsg dans la grille*/
                Grille_attribue_couleur_case(G, elem->i, elem->j, couleur);
            }
            elem=elem->suiv;
        }

        /*Ajout des éléments de la bordure de la même couleur que la nouvelle Zsg*/
        int i, j;
        while (Zsg->B[couleur]!=NULL) {
            enleve_en_tete(&(Zsg->B[couleur]), &i, &j);
            taille += agrandit_zone(M, Zsg, couleur, i, j);
        }

        /*Affichage si aff=1*/
        if (aff) {
            Grille_redessine_Grille(G);
            //Grille_attente_touche();
        }
        cpt++;
    }
    detruit_Zsg(Zsg);
    return cpt;
}