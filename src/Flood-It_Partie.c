#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "API_Grille.h"
#include "API_Gene_instance.h"
#include "Entete_Fonctions1.h"
#include "Entete_Fonctions2.h"
#include "Entete_Fonctions3.h"
#include "Entete_Fonctions4.h"
#include "Entete_Fonctions5.h"
#include "Entete_Fonctions6.h"
#include "Liste_case.h"
 
 
int main(int argc,char** argv){

  int dim, nbcl, nivdif, graine, exo, aff;
  Grille *G;
  int i,j;
  int **M;

  clock_t
  temps_initial,      /* Temps initial en micro-secondes */
  temps_final;        /* Temps final en micro-secondes */
  float temps_cpu;    /* Temps total en secondes */ 
 


  if(argc!=7){
    printf("usage: %s <dimension> <nb_de_couleurs> <niveau_difficulte> <graine> <exo:1-2-3-4-5-6> <aff 0/1>\n",argv[0]);
    return 1;
  }

  dim=atoi(argv[1]);
  nbcl=atoi(argv[2]);
  nivdif=atoi(argv[3]);
  graine=atoi(argv[4]);
  exo=atoi(argv[5]);
  aff=atoi(argv[6]);

  /* Allocation puis generation de l'instance */

 /* M=(int **) malloc(sizeof(int*)*dim);
  for (i=0;i<dim;i++){
    M[i]=(int*) malloc(sizeof(int)*dim);
    if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
  }

  Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

  // Affichage de la grille 
  if (aff==1){ 
    Grille_init(dim,nbcl, 500,&G);
    Grille_ouvre_fenetre(G);

    for (i=0;i<dim;i++)
      for (j=0;j<dim;j++){
        Grille_attribue_couleur_case(G,i,j,M[i][j]);
      }

    Grille_redessine_Grille(G);
    Grille_attente_touche();
  }
  //----------------------------------------------------EXERCICES -------------------------------------------------
  //Calcul du temps 
  temps_initial = clock ();
  
  int compt;
  if (exo==1){
    compt=sequence_aleatoire_rec(M, G, dim, nbcl, aff);
    printf("%d essais ", compt); 
  }
  if (exo==2){
    compt=sequence_aleatoire_imp(M, G, dim, nbcl, aff);
    printf("%d essais ", compt); 
  }
  if (exo==3){
    compt=sequence_aleatoire_rapide(M, G, dim, nbcl, aff);
    printf("%d essais ", compt); 
  }
  if (exo==4){
    
    Graphe_zone *G=creer_graphe_zone(M,dim);
    affichage_graphe(G);
    detruit_graphe_zone(G,dim);
  }
  if (exo==5){
  
    int nb=strategie_max_bordure(M, G, dim, nbcl, aff);
   
    printf("\n\n|TAILLE DE LA SEQUENCE PAR LA STRATEGIE DE MAX BORDURE:%d",nb);
    
  }
  if (exo==6){
  
    int nb=strategie_parcours_largeur(M, G, dim, nbcl, aff);
   
    printf("\n\n|TAILLE DE LA SEQUENCE PAR PARCOURS EN LARGEUR:%d",nb);
    
  }
  temps_final = clock ();
  temps_cpu = (temps_final - temps_initial)/CLOCKS_PER_SEC;

  //Affichage console
  printf("\n|Temps:%f\n",temps_cpu);

  
  // Desallocation de la matrice 
  for(i = 0; i< dim; i++) {
    if (M[i])
        free(M[i]);
  }
  if (M) free(M);

  
  // Fermeture et désallocation de la grille 
  if (aff==1){ 
    Grille_ferme_fenetre();
    Grille_free(&G);
  }

*/

  /*====================================================================================
    PARTIE DU CODE UTILISEE A LA PLACE DES LIGNES PLUS HAUT POUR GENERER LES FICHIERS 
    DES JEUX D'ESSAIS
    ====================================================================================*/
  dim=20;
  nivdif=0;
  while (dim <=200){
    FILE *fichier=fopen("EXO.txt","a");
    if (fichier==NULL){
      fprintf(stderr,"Impossible d'ouvrir le fichier données en lecture\n");
      exit(1);
    }
    nbcl=10;
      
    while (nbcl<=80){
      // Allocation puis generation de l'instance 

      M=(int **) malloc(sizeof(int*)*dim);
      for (i=0;i<dim;i++){
        M[i]=(int*) malloc(sizeof(int)*dim);
        if (M[i]==0) printf("Pas assez d'espace mémoire disponible\n");
      }

      Gene_instance_genere_matrice(dim, nbcl, nivdif, graine, M);

      //Affichage de la grille 
      if (aff==1){ 
        Grille_init(dim,nbcl, 500,&G);
        Grille_ouvre_fenetre(G);

        for (i=0;i<dim;i++)
          for (j=0;j<dim;j++){
            Grille_attribue_couleur_case(G,i,j,M[i][j]);
          }

        Grille_redessine_Grille(G);
        //Grille_attente_touche();
      }

      //Calcul du temps 
      temps_initial = clock ();
      
      int compt;
      if (exo==1){
        compt=sequence_aleatoire_rec(M, G, dim, nbcl, aff);
        printf("%d essais ", compt); 
      }
      if (exo==2){
        compt=sequence_aleatoire_imp(M, G, dim, nbcl, aff);
        printf("%d essais ", compt); 
      }
      if (exo==3){
        compt=sequence_aleatoire_rapide(M, G, dim, nbcl, aff);
        printf("%d essais ", compt); 
      }
      if (exo==4){
        
        Graphe_zone *G=creer_graphe_zone(M,dim);
        //affichage_graphe(G);
        detruit_graphe_zone(G,dim);
      }
      if (exo==5){
      
        compt=strategie_max_bordure(M, G, dim, nbcl, aff);
       
        printf("\n\n|TAILLE DE LA SEQUENCE PAR LA STRATEGIE DE MAX BORDURE:%d \n",compt);
        
      }
      if (exo==6){
      
        compt=strategie_parcours_largeur(M, G, dim, nbcl, aff);
       
        printf("\n\n|TAILLE DE LA SEQUENCE PAR PARCOURS EN LARGEUR:%d \n",compt);
        
      }
      
      temps_final = clock ();
      temps_cpu = (float )(temps_final - temps_initial) /CLOCKS_PER_SEC;

      //Affichage console
      printf("%f\n",temps_cpu);

      //Ecriture fichier
      fprintf(fichier,"%4d\t\t\t%3d\t\t\t%4d\t\t\t%.5f\n",dim,nbcl,compt,temps_cpu);
      
      
      // Desallocation de la matrice 
      for(i = 0; i< dim; i++) {
        if (M[i])
            free(M[i]);
      }
      if (M) free(M);

      
      // Fermeture et désallocation de la grille
      if (aff==1){ 
        Grille_ferme_fenetre();
        Grille_free(&G);
      }
      nbcl+=10;
      
    }
    dim+=20;
    fclose(fichier);
  }
  

  return 0;
}
