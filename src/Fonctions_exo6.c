#include<stdio.h>
#include "Entete_Fonctions6.h"


/*========================================================================
                                EXERCICE 6
 =========================================================================*/
void plus_court_chemin(Graphe_zone *G, Sommet *Racine) {

  Racine->distance = 0;
	
	Cellule_som *S = (Cellule_som *)malloc(sizeof(Cellule_som)); //Liste des sommets à étudier
  S->sommet=Racine;//On commence par la racine
  S->suiv=NULL;
	
	Cellule_som *adj,     //permet de parcourir les adjacents du sommet en cours
              *tmp,     //Variable temporaire qui servira à liberer la memoire
              *dernier; //détient le dernier sommet ajouté à la liste S
  dernier=S;
	Sommet *pere;
	
	while(S!=NULL) {
		pere=S->sommet;
    adj=S->sommet->sommet_adj;

    //On libere l'espace alloué à S
    tmp=S;
    S=S->suiv;
    free(tmp);
		
		while(adj != NULL) {
			if(adj->sommet->pere == NULL) {
				adj->sommet->pere = pere;
				adj->sommet->distance=pere->distance+1;
				
        /*Construction d'une sorte de File pour le principe 
          du premier sommet ouvert du parcours en largeur */
        Cellule_som *NewPere = (Cellule_som *)malloc(sizeof(Cellule_som));
        NewPere->sommet=adj->sommet;
        NewPere->suiv=NULL;
        if (S==NULL){
            S=NewPere; 
        }
        dernier->suiv=NewPere;
        dernier=NewPere;
                
			}
			adj= adj->suiv;
		}
	}
}

/*========================================================================*/
int strategie_parcours_largeur(int **M, Grille *G, int dim, int nbcl, int aff){
    int cpt=0;
    //INITIALISATION
    Graphe_zone *Gz=creer_graphe_zone3(M,dim);
    plus_court_chemin (Gz,Gz->mat[0][0]);//La racine est le sommet de la Zsg

    Sommet *S_Zid=Gz->mat[dim-1][dim-1], //Zone inférieure droite
           *S_Zsg=Gz->mat[0][0];         //Zone supérieure gauche

    //CHOIX DES COULEURS POUR ALLER A LA ZID (zone inférieure droite)     
    int len_chemin=S_Zid->distance;    
    
    /* -----stocke les couleurs du plus court chemin allant de Zsg à Zid
            pour cela, on à partir de Zid vers Zsg via le père*/
    int *sequence=(int *)malloc(len_chemin*sizeof(int));
    for (int i=len_chemin-1;i>=0;i--){
        sequence[i]=S_Zid->cl;
        S_Zid=S_Zid->pere;
    }  
    Bordure_graphe *B=cree_graphe_bordure(Gz,nbcl);  
    
    //STRATEGIE MAX_BORDURE
    for (int i=0;i<len_chemin ;i++){

        /* Modification de la couleur de la zone supérieure gauche dans la grille si aff=1 ----------------*/
        if (aff==1){                                                                                        
            Cellule_som *Zsg=B->Zsg;                                                                       
            ListeCase C; 
            while(Zsg !=NULL) {
                C= Zsg->sommet->cases;
                while (C!=NULL){
                    Grille_attribue_couleur_case(G,C->i,C->j,sequence[i]);
                    C= C->suiv ;
                }
            
                Zsg=Zsg->suiv;
            }

            /*  affichage*/
            
            Grille_redessine_Grille(G);
         //   Grille_attente_touche();
            
        }
        /*----------------------------------------------------------------------------------------------*/


        maj_bordure_graphe(Gz,B,sequence[i]);
    }

    cpt=len_chemin+strategie_max_bordure2(G,Gz,B,dim,nbcl,aff);


    free(sequence);
    detruit_graphe_zone(Gz,dim);
    detruit_bordure_graphe(B,nbcl);
    return cpt;
}

/*-------------------------------------------------------------------------------*/
/* Mise à jour de la fonction de l'exo 5 avec l'ajout des champs distance et pere*/
/*-------------------------------------------------------------------------------*/

Graphe_zone *creer_graphe_zone3(int **M, int dim){
  
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
    (G->mat)[i]=(Sommet **)malloc(dim* sizeof (Sommet *)); //pointeurs sur des sommets
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
        S->marque=2;
        S->pere=NULL;
        S->distance=2147483647; //valeur maximale d'un int
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
      
      //on récupère les sommets à comparer
      s1=G->mat[i][j];
      if(j+1<dim) {
        s2=G->mat[i][j+1]; //à droite
        if (s1!=s2){
          //on vérifie si les sommets sont déjà marqués adjacents dans la structure
          if (adjacent(s1,s2)==0){
            ajoute_voisin(s1,s2);
            
          } 
        }
      }
      
      if(i+1<dim){
        s3=G->mat[i+1][j]; //en bas
        
        if (s1!=s3){
          //on vérifie si les sommets sont déjà marqués adjacents dans la structure
          if (adjacent(s1,s3)==0){
            
            ajoute_voisin(s1,s3);
            
          }
        }

      }
    
    }
  }
  
  return G;
  
}
/*========================================================================*/
int strategie_max_bordure2( Grille *G,Graphe_zone *Gr,Bordure_graphe *B, int dim, int nbcl, int aff){
    int sequence=0;
    int i_max, //couleur dominante dans la bordure
        len_max;//taille max dans le tableau 
    
    while (B->NbElemTab!=0){
        
        i_max=0;  
        len_max=0;

        for (int i=0;i<nbcl;i++){
            if ((B->TabLen)[i]>len_max){
                i_max=i;
                len_max=B->TabLen[i]; //Recherche du max
            }
        }


        maj_bordure_graphe(Gr,B,i_max);
        sequence++;

        /* Modification de la couleur de la zone supérieure gauche dans la grille si aff=1 ----------------*/
        if (aff==1){
            Cellule_som *Zsg=B->Zsg;
            ListeCase C; 
            while(Zsg !=NULL) {
                C= Zsg->sommet->cases;
                while (C!=NULL){
                    Grille_attribue_couleur_case(G,C->i,C->j,i_max);
                    C= C->suiv ;
                }
            
                Zsg=Zsg->suiv;
            }

            /*  affichage*/
            
            Grille_redessine_Grille(G);
         //   Grille_attente_touche();
            
        }
        /*----------------------------------------------------------------------------------------------*/


        
    }
  //  detruit_bordure_graphe(B,nbcl);
 //   detruit_graphe_zone(Gr,dim);
    return sequence;
    
}