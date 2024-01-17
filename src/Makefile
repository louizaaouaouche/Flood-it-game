all: Flood-It_Partie

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
	gcc -c API_Gene_instance.c

API_Grille.o: API_Grille.c API_Grille.h
	gcc -c API_Grille.c

Liste_case.o: Liste_case.c Liste_case.h
	gcc -c Liste_case.c

Fonctions_exo1.o: Fonctions_exo1.c Entete_Fonctions1.h Liste_case.h
	gcc -c Fonctions_exo1.c

Fonctions_exo2.o: Fonctions_exo2.c Entete_Fonctions2.h Liste_case.h
	gcc -c Fonctions_exo2.c

Fonctions_exo3.o: Fonctions_exo3.c Entete_Fonctions3.h Liste_case.h
	gcc -c Fonctions_exo3.c

Fonctions_exo4.o: Fonctions_exo4.c Entete_Fonctions4.h Entete_Fonctions1.h
	gcc -c Fonctions_exo4.c

Fonctions_exo5.o: Fonctions_exo5.c Entete_Fonctions5.h Entete_Fonctions1.h Entete_Fonctions4.h
	gcc -c Fonctions_exo5.c 

Fonctions_exo6.o: Fonctions_exo6.c Entete_Fonctions6.h Entete_Fonctions1.h Entete_Fonctions4.h Entete_Fonctions5.h
	gcc -c Fonctions_exo6.c 

Flood-It_Partie.o: Flood-It_Partie.c
	gcc -c Flood-It_Partie.c 

Flood-It_Partie: Flood-It_Partie.o Liste_case.o API_Grille.o  API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o Fonctions_exo3.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o
	gcc -o bin/Flood-It_Partie Flood-It_Partie.o Liste_case.o  API_Grille.o API_Gene_instance.o Fonctions_exo1.o Fonctions_exo2.o Fonctions_exo3.o Fonctions_exo4.o Fonctions_exo5.o Fonctions_exo6.o -I include -L lib -lmingw32 -lSDL2main -lSDL2

clean:
	rm -f *.o Flood-It_Partie
