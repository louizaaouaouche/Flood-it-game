#include<stdio.h>
#include "Entete_Fonctions4.h"

/*========================================================================
                                EXERCICE 4
 =========================================================================*/

int ajoute_liste_sommet(Cellule_som **L,Sommet *S){

  Cellule_som *nouv_cell=(Cellule_som *) malloc (sizeof (Cellule_som));
  
  if (nouv_cell ==NULL){
    printf("Erreur d'allocation mémoire: ajoute_liste_sommet\n");
    return 0;
  }
  //Insertion en tête
  nouv_cell->sommet=S;
  nouv_cell->suiv=*L;
  *L=nouv_cell;
  
  return 1;
}

/*==============================================================================*/
void detruit_liste_sommet(Cellule_som *L){

    Cellule_som * s_tmp=L;

    //On ne libère que les pointeurs sur les sommets et non pas les sommets eux mêmes
    while (L!=NULL){
      L=L->suiv;
      free (s_tmp);
      s_tmp=L;
    }
}

/*==============================================================================*/
void ajoute_voisin(Sommet *s1, Sommet *s2){
  //On ajoute le sommet s1(resp s2) à la liste d'adjacence de s2 (resp s1)
  
  int flag=ajoute_liste_sommet(&(s2->sommet_adj),s1); //ajout de s1 aux adjacents de s2
  if (flag==0) printf("ERREUR: PROBLEME DANS L'APPEL A LA FONCTION ajoute_liste_sommet DANS ajoute_voisin");

  flag=ajoute_liste_sommet(&(s1->sommet_adj),s2); //ajout de s2 aux adjacents de s1
  if (flag==0) printf("ERREUR: PROBLEME DANS L'APPEL A LA FONCTION ajoute_liste_sommet DANS ajoute_voisin");
  
}
/*==============================================================================*/
int adjacent(Sommet *s1, Sommet *s2){

  /*Il suffit de vérifier si l'un est dans la liste d'adjacence de l'autre
  en supposant que la fonction ajoute_voisin fonctionne bien*/

  if (s1!=NULL && s2!=NULL ){
    Cellule_som *adj_s1=s1->sommet_adj;
    Cellule_som *adj_s2=s2->sommet_adj;
    
   
    /*On ne s'arrête que si on a parcouru les deux listes et on n'a pas 
      trouvé le sommet s1 dans les adjacents de s2 (et inversement)*/
    while(adj_s1 !=NULL || adj_s2!=NULL ) {


      if (adj_s1 !=NULL){
        //on vérifie si s2 est dans s1
        if (adj_s1->sommet->num==s2->num) {
          return 1; 
        }else{
          adj_s1=adj_s1->suiv;
        }
      }
        
      
      if(adj_s2!=NULL){
        //on vérifie si s1 est dans s2
        if (adj_s2->sommet->num==s1->num){
          
          return 1;
        }else{
          adj_s2=adj_s2->suiv;
        }
      }
    }
  }
  
  return 0; //Les deux sommets ne sont pas adjacents
}

/*==============================================================================*/
Graphe_zone *creer_graphe_zone(int **M, int dim){
  
  Graphe_zone *G=(Graphe_zone *)malloc(sizeof(Graphe_zone));
  if (G==NULL){
    printf("ERREUR D'ALLOCATION: creer_graphe_zone\n");
    exit(EXIT_FAILURE);
  }

  //Initialisation de la structure de graphe G--------------------------
  G->nbsom=0;
  G->som=NULL;
  G->mat=(Sommet ***)malloc(dim* sizeof(Sommet **));
  if (G->mat==NULL){
    printf("ERREUR D'ALLOCATION: creer_graphe_zone\n");
    exit(EXIT_FAILURE);
  }


  //Initialisation de la matrice. Enonce: G.mat[i][j]=NULL--------------
  for(int i=0;i<dim;i++){
    (G->mat)[i]=(Sommet **)malloc(dim* sizeof (Sommet )); //pointeurs sur des sommets
    if ((G->mat)[i]==NULL){
      printf("ERREUR D'ALLOCATION: creer_graphe_zone\n");
      exit(EXIT_FAILURE);
    }
    for (int j=0;j<dim;j++){
      (G->mat)[i][j]=NULL; 
    }
  }

  
  //Création des sommets (appel à trouve_zone_rec (exo1-partie1)--------
  
  int cpt=1,taille,i,j;

  for ( i=0;i<dim;i++){
    for( j=0;j<dim;j++){
      if((G->mat)[i][j]==NULL){
        
        Sommet *S=(Sommet *)malloc(sizeof(Sommet));
        S->num=cpt;
        cpt++;                   
        S->cl=M[i][j];
        
        G->nbsom++; 
        ajoute_liste_sommet(&(G->som),S);

        //Zone associée à la case (i,j)
        taille=0;
        S->cases=NULL;
        trouve_zone_rec(M,dim,i,j,&taille,&(S->cases));
        S->nbcase_som=taille;
        //Mise à jour de la matrice mat pour toutes les cases de la zone
        Elnt_liste *elem=S->cases;
        while (elem !=NULL){
          G->mat[elem->i][elem->j]=S;
          elem=elem->suiv;

        }      
        
        S->sommet_adj=NULL; //initialisation de la liste d'adjacence
      }
    }
  }

  //Sommets adjacents -----------------------------------------------------
  Sommet *s1,*s2,*s3;
  for ( i=0;i<dim;i++){
    for( j=0;j<dim;j++){
      
      //on récupère les sommets à comparer: à droite et en bas
      s1=G->mat[i][j];

      //A DROITE -------------------------
      if(j+1<dim) {
        s2=G->mat[i][j+1]; 
        if (s1!=s2){
          //on vérifie si les sommets sont déjà marqués adjacents dans la structure
          if (adjacent(s1,s2)==0){
            ajoute_voisin(s1,s2);
           
          } 
        }
      }
      //EN BAS ----------------------------
      if(i+1<dim){
        s3=G->mat[i+1][j]; 
        
        if (s1!=s3){
          /*on vérifie si les sommets sont déjà marqués adjacents dans la structure
            si ce n'est pas le cas, on les ajoutes l'un dans la liste d'adjacence de l'autre*/
          if (adjacent(s1,s3)==0){
            
            ajoute_voisin(s1,s3);
            
          }
        }

      }
    
    }
  }
  
  return G;
  
}

/*==============================================================================*/
void affichage_graphe(Graphe_zone *G){
  
  Cellule_som *S=G->som;
  Cellule_som *adj;
  ListeCase L;
  while (S!=NULL){
    printf("\n_____________________________________________________________________________________________________\n");
    printf(" ZONE:%d | COULEUR: %d | NB CASES: %d \n CASES:",S->sommet->num,S->sommet->cl,S->sommet->nbcase_som);
    L=S->sommet->cases;
    
    while (L!=NULL){
      printf("(%d,%d)->",L->i,L->j); //Liste de cases associées au sommet 
      L=L->suiv;
    }

    printf("\n ADJACENCE: ");
    adj=S->sommet->sommet_adj;
    while (adj!=NULL){
      printf("(%d)->",adj->sommet->num); //Liste d'aretes
      adj=adj->suiv;
    }

    S=S->suiv; 
  }
  
  
}
/*==============================================================================*/
void detruit_graphe_zone(Graphe_zone *G,int dim){
    
    if (G!=NULL){
      
      if (G->mat!=NULL){
       
        Cellule_som *S=G->som;
        //On libere les sommets 
        while(S!=NULL){ 
          detruit_liste(&S->sommet->cases);
          detruit_liste_sommet(S->sommet->sommet_adj);
          free(S->sommet);
          S=S->suiv;
          
        }
        detruit_liste_sommet(G->som);

        for (int i=0;i<dim;i++){
          free(G->mat[i]);
        }
        free(G->mat);        
        free (G);
      }
     
    }
    
}
