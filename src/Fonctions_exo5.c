#include<stdio.h>
#include "Entete_Fonctions5.h"

/*========================================================================
                                EXERCICE 5
 =========================================================================*/

Bordure_graphe *cree_graphe_bordure(Graphe_zone *G,int nbcl){
    
    if (G!=NULL){
        
        /* Allocation mémoire */
        Bordure_graphe *BG=(Bordure_graphe *)malloc(sizeof(Bordure_graphe));
        BG->ListeSom=(Cellule_som **)malloc (nbcl*sizeof(Cellule_som*));
        
        BG->TabLen=(int *)malloc(nbcl * sizeof(int));
        BG->Zsg=(Cellule_som *)malloc(sizeof(Cellule_som));
        BG->NbElemTab=0;
        
        /*Initialisation du tableau de listes de sommets et le tableau
        de tailles associé*/
        for (int i=0;i<nbcl;i++){
            BG->ListeSom[i]=NULL;
            BG->TabLen[i]=0;
        }
        
        /* Initialisation du sommet de*/ 
        
        BG->Zsg->sommet=(G->mat)[0][0];
        BG->Zsg->suiv=NULL;
        BG->Zsg->sommet->marque=0;
        
        /* Initialisation par les données du graphe G*/ 
        Cellule_som *tmp=BG->Zsg->sommet->sommet_adj;
        while (tmp!=NULL){
            
            tmp->sommet->marque=1; /*On le marque comme apprtenant à la bordure de Zsg*/
           
            //Insertion en tete
            Cellule_som *nouv_cell=(Cellule_som *) malloc (sizeof (Cellule_som));
            nouv_cell->sommet=tmp->sommet;
            nouv_cell->suiv=BG->ListeSom[tmp->sommet->cl];
            BG->ListeSom[tmp->sommet->cl]=nouv_cell;
          
            BG->TabLen[tmp->sommet->cl]++;
            BG->NbElemTab++;
            tmp=tmp->suiv;
                  

        }
        return BG;
    }
    return NULL; 
}

/*=========================================================================*/
void maj_bordure_graphe(Graphe_zone *G,Bordure_graphe *B,int cl){
    
    //mise à jour de la liste à la case cl
    B->NbElemTab-=B->TabLen[cl];
    Cellule_som *adj_Zsg=B->ListeSom[cl];//On récupère les sommets qui correspondent à la couleur cl dans la bordure    
     
    Cellule_som *tmp;
   
    
    B->ListeSom[cl]=NULL;
    B->TabLen[cl]=0;
    

    //Mise à jour de la couleur des sommets Zsg  
    Cellule_som *S=B->Zsg;
    while (S!=NULL){
        S->sommet->cl=cl;
        S=S->suiv;
    }

    //Ajout des sommets adjacents à Zsg de couleur cl à la Zsg
    //Mise à jour de la bordure par les sommets adjacents à la suite de sommets adj_cl
    while (adj_Zsg!=NULL){
        if (adj_Zsg->sommet->marque!=0){
            adj_Zsg->sommet->marque=0;//Ajout à Zsg

            Cellule_som *nouv_zsg=(Cellule_som *) malloc (sizeof (Cellule_som));
            nouv_zsg->sommet=adj_Zsg->sommet;
            nouv_zsg->suiv=B->Zsg;
            B->Zsg=nouv_zsg;
            
            //Mise à jour de la bordure par les adjacents de l'ancienne bordure
            Cellule_som * adj_cl=adj_Zsg->sommet->sommet_adj;
            while (adj_cl!=NULL){
                
                if (adj_cl->sommet->marque==2){
                    adj_cl->sommet->marque=1; //Ajout à la bordure

                    //Insertion en tete
                    Cellule_som *nouv_cell=(Cellule_som *) malloc (sizeof (Cellule_som));
                    nouv_cell->sommet=adj_cl->sommet;
                    nouv_cell->suiv=B->ListeSom[adj_cl->sommet->cl];
                    B->ListeSom[adj_cl->sommet->cl]=nouv_cell;

                    //maj des tailles
                    B->TabLen[adj_cl->sommet->cl]++; 
                    B->NbElemTab++;
              
                }
                adj_cl=adj_cl->suiv;
            }
        }
        tmp=adj_Zsg;
        adj_Zsg=adj_Zsg->suiv;
        free(tmp);
    }  

}

/*=========================================================================*/
int strategie_max_bordure(int **M, Grille *G, int dim, int nbcl, int aff){
    //Création des structures
    Graphe_zone *Gr=creer_graphe_zone2(M,dim);
    Bordure_graphe *B=cree_graphe_bordure(Gr,nbcl);
    
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
            //Grille_attente_touche();
            
        }
        /*----------------------------------------------------------------------------------------------*/


        
    }
    
    detruit_graphe_zone(Gr,dim);
    detruit_bordure_graphe(B,nbcl);
    return sequence;
    
}
/*=========================================================================*/
void detruit_bordure_graphe(Bordure_graphe *B,int nbcl){
   
    //On libère les cellules de la Zsg   
    Cellule_som *tmp;
    while(B->Zsg){
      tmp=B->Zsg;
      B->Zsg=B->Zsg->suiv;
      free(tmp);
    }

    //On libère les cellules formant la bordure
    for (int i=0;i<nbcl;i++){
        while (B->ListeSom[i]){
          tmp=B->ListeSom[i];
          B->ListeSom[i]=B->ListeSom[i]->suiv;
          free(tmp);
        }
    }
    free(B->ListeSom);
    //On libere le tableau des tailles
    free(B->TabLen);
    free (B);
}
/*=========================================================================*/

/*------------------------------------------------------------------------------*/
/* Mise à jour de la fonction de l'exo 4 avec l'ajout du champ int marque       */
/*------------------------------------------------------------------------------*/

Graphe_zone *creer_graphe_zone2(int **M, int dim){
  
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
    (G->mat)[i]=(Sommet **)malloc(dim* sizeof (Sommet * )); //pointeurs sur des sommets
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
