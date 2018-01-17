#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define Nb_Sommet 376 //Nombre Sommets
#define MAX 10000 //Distance Max affiché dans le tableau pour les sommets n'ayant pas de correspondance

//########## Definition de la structure Chemin #########//
typedef struct{
	int temps;
}Chemin;

//########## Definition de la structure Sommet #########//

typedef struct{
	char nom[55];
	int numSommet;
	int type_ligne;
}Sommet;

//### Definition de la structure tableau de Djikstra ###//
typedef struct{
	int temps_t;
	int sommet;
	int etat;
	int pere;
}CaseD;

//########## Initialisation Tableau De Chemins #########//

void initChemins(Chemin C[Nb_Sommet][Nb_Sommet])
{
	int i,j;
	
	for(i=0;i<Nb_Sommet;i++)
	{
		for(j=0;j<Nb_Sommet;j++)
		{
			C[i][j].temps=MAX;
			//####### Test de récupération ######// 
			//printf("%d %d %d\n",i,j,C[i][j].temps);
			//###################################//
		}
	}

}

//########## Recuperation Chemins #########//

void recupChemins(Chemin C[Nb_Sommet][Nb_Sommet]){
	
	int check,i,j,t;
	FILE* fichierChemins = NULL;
	
	initChemins(C);
	
	fichierChemins = fopen("Chemins.txt","r");
	
	if (fichierChemins != NULL){
	
		printf("\nRécuperation des données du fichier Chemins.txt\n");
		printf("***********************************************\n");
			while(check!=-1)
			{
					check=fscanf(fichierChemins,"%d %d %d",&i, &j,&t);
					C[i][j].temps=t;
					C[j][i].temps=t;
					//####### Test de récupération ######// 
					//printf("%d %d %d \n",i,j,C[i][j].temps);
					//##################################//
			}	
				
		fclose(fichierChemins);
	}
	else{
		printf("Erreur lors de l'ouverture du fichier Chemins.txt\n");
	}
	
	
}

//########## Affichage Chemins #########//

void afficheChemins(Chemin C[Nb_Sommet][Nb_Sommet])
{
	int a,b;
	
	for(a=0;a<Nb_Sommet;a++)
	{
		for(b=0;b<Nb_Sommet;b++)
		{
			printf("%d %d %d\n",a,b,C[a][b].temps);
		}
	}
}

//########## Initialisation Sommets #########//

void initSommets(Sommet S[Nb_Sommet])
{
	int i;
	
	for(i=0;i<Nb_Sommet;i++)
	{
			strcpy(S[i].nom,"nom");
			S[i].numSommet=i;
			S[i].type_ligne=0;
			//####### Test de récupération ######// 
			//printf("%d %d %s \n",S[i].numSommet,S[i].type_ligne,S[i].nom);
			//###################################//
	}
}

//########## Affichage Sommets #########//

void afficheSommets(Sommet S[Nb_Sommet])
{
	int i;
	
	for(i=0;i<Nb_Sommet;i++)
	{
		printf("%d %d %s \n",i,S[i].type_ligne,S[i].nom);
	}
}

//########## Recuperation Sommets #########//

void recupSommets(Sommet S[Nb_Sommet]){
	
	FILE* fichierSommet;
	
	int i;
	initSommets(S);
	
	fichierSommet = fopen("Sommet.txt","r");
	
		if(fichierSommet != NULL)
		{
			printf("Récuperation des données du fichier Sommet.txt\n");
			printf("**********************************************\n");
			
			for (i = 0; i < Nb_Sommet; i++)
			{
				
				fscanf(fichierSommet,"%d",&(S[i].numSommet));
				fscanf(fichierSommet,"%d",&(S[i].type_ligne));
				fscanf(fichierSommet,"%s",S[i].nom);	
				
				//####### Test de récupération ######// 
				//printf("%d %d %s\n",S[i].numSommet,S[i].type_ligne,S[i].nom);
				//##################################//	
			}
		
			fclose(fichierSommet);
		}
		
		else{
			printf("Erreur lors de l'ouverture du fichier Sommet.txt\n");
		} 
}

//########## Affichage Du Temps #########//

void affiche_temps(CaseD D[Nb_Sommet], int s){
	printf("Le trajet devrait vous prendre");
	if ( D[s].temps_t/60 != 0) printf(" %d min", D[s].temps_t/60);
	printf(" %d seconde\n", D[s].temps_t%60);
	
}

//########## Initialisation Djikstra #########//

void init_Djikstra(CaseD D[Nb_Sommet], int sommet_depart){
	
	int i;
	
	printf("Initialisation tableau Djikstra\n");
	printf("***********************************************\n");
	
	for (i = 0; i < Nb_Sommet; i++)
	{
		D[i].sommet = i;
		D[i].etat = 0;
		D[i].pere = -1;
		D[i].temps_t = MAX;
	}
	
	D[sommet_depart].sommet = sommet_depart;
	D[sommet_depart].etat = 1;
	D[sommet_depart].pere = -1;
	D[sommet_depart].temps_t = 0;
	
	//printf("Initialisation réussi\n");
}

//########## Recherche noeud de distance minimale a partir de s_actuel #########//

int test_suivant_Djikstra(CaseD D[Nb_Sommet], int s_actuel){
	
	int min, i, sommet_a_traiter;
	
	min = 20000;
	sommet_a_traiter = -1;

	
	for (i = 0; i < Nb_Sommet; i++)
	{
		if (D[i].etat != 1 && D[i].temps_t < min)
		{
			min = D[i].temps_t;
			sommet_a_traiter = i;
			
			if (D[i].etat == 1)
			{
				printf(" PROBLEME \n");
			}
		}
	}
	
	return sommet_a_traiter;
}

//########## Tableau Djikstra #########//

void affiche_tableau_Djikstra(CaseD D[Nb_Sommet]){
	
	int i;
	printf("***********************************************\n");
	for (i = 0; i < Nb_Sommet; i++)
	{
		printf("sommet : %d ,",D[i].sommet);
		printf("etat : %d ,",D[i].etat);
		printf("pere : %d ,",D[i].pere);
		printf("temps : %d\n",D[i].temps_t);
	}
	printf("***********************************************\n\n");
}


//########## Algo Principal Djikstra #########//

void Djikstra(int s_actuel, CaseD D[Nb_Sommet], Sommet S[Nb_Sommet], Chemin C[Nb_Sommet][Nb_Sommet])
{
	int i=0;
	int sommet_a_traiter;
	
	while(i<Nb_Sommet)
	{
		
		if(C[s_actuel][i].temps!=MAX)
		{
		/*if(s_actuel == 4){  
			printf("\nsommet : %d ",s_actuel);
			printf("temps du sommet courant .: %d\n",D[s_actuel].temps_t);
			printf("temps du chemin .: %d\n",C[s_actuel][i].temps);
			printf("sommet pointé : %d\n",i);
			printf("temps du sommet pointé: %d\n",D[i].temps_t);
			printf("%d > %d + %d\n\n",D[i].temps_t,C[s_actuel][i].temps, D[s_actuel].temps_t );
		}*/
			if(D[i].temps_t >C[s_actuel][i].temps + D[s_actuel].temps_t)
			{
				//printf("Changement du temps\n");
				D[i].temps_t=C[s_actuel][i].temps + D[s_actuel].temps_t;
				D[i].pere=s_actuel;
				//printf("%d \n",D[i].pere);
			}
		}
		i++;
	}
	
	D[s_actuel].etat = 1;
	//if (s_actuel == 4) affiche_tableau_Djikstra(D);
	
	sommet_a_traiter = test_suivant_Djikstra(D,s_actuel);
	//printf("%d \n",sommet_a_traiter);
	
	if (sommet_a_traiter != -1)
	{
		Djikstra(sommet_a_traiter,D,S,C);
	}
}

//########## Affichage Du trajet #########//

void affiche_trajet(CaseD D[Nb_Sommet], Sommet S[Nb_Sommet],Chemin C[Nb_Sommet][Nb_Sommet], int depart, int arrive)
{
	int sommet_suivant=arrive;
	
	printf("Vous etes à %s ligne %d\n",S[arrive].nom,S[arrive].type_ligne); 
	while(sommet_suivant != depart) 
	{	
		sommet_suivant = D[sommet_suivant].pere;
		printf("Prenez la ligne %d à %s \n", S[sommet_suivant].type_ligne,S[sommet_suivant].nom);
	}
	
	printf("Vous arrivez à %s\n", S[depart].nom);
}

//COMPILATION: make  EXECUTION: ./Projet_Metro

int main(int argc, char * argv[])
{
	Chemin C[Nb_Sommet][Nb_Sommet];
	Sommet 	S[Nb_Sommet];
	CaseD	D[Nb_Sommet];
	int  depart, arrive;
	
	recupChemins(C);
	recupSommets(S);
	
	//afficheChemins(C);
	afficheSommets(S);
	
	do{
	printf("\nOù vous trouvez-vous ? \n");
	scanf("%d", &depart);
	}while(depart!=S[depart].numSommet);
	
		printf("Vous vous trouvez à : %s ligne %d\n",S[depart].nom,S[depart].type_ligne);
		printf("\n"); 
	
	do{
	printf("A quel endroit souhaitez-vous vous rendre ? \n");
	scanf("%d", &arrive);
	}while(arrive!=S[arrive].numSommet);
	
		printf("Vous voulez allez à : %s ligne %d\n",S[arrive].nom,S[arrive].type_ligne);
		printf("\n");
		
	if( depart != arrive){
		
		init_Djikstra(D,arrive);
		Djikstra(arrive,D,S,C);
		
		affiche_trajet(D,S,C,arrive,depart);
		affiche_temps(D, depart);
		
		
		printf("Fin du programme \n");
	}
	else 
	{
		printf("Vous êtes déjà sur place ...\n");
		printf("\nFin du programme \n");
	}
	 return 0;
}
