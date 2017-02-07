#include <stdio.h>
#include <stdlib.h>                                                     
#include <string.h>

#define DNBMAXTRAVAUX 5

void extraireSeuil(double seuil[], char *argv[], int argc);
void valideSeuil(int taille, double seuil[]);
int valideNbNotes();
void pondererNote(int nbNotes, int ponderation[]);
void notesMaximales(int nbNote, int notesMax[]);
void validerCodePermanent(int taille, char codePerm[]);
float moyenneEtudiant(int nbNotes, int ponderation[], int notesMax[]);
void ajouterNote(double seuil[], int notesEtudiant[], float moyenne); 

int main(int argc, char *argv[]){                                                                               
	
	double seuil[argc-1];
	extraireSeuil(seuil,argv,argc);

	valideSeuil(argc,seuil);
	
	int nbNotes = valideNbNotes();

	int ponderation[nbNotes];
	pondererNote(nbNotes,ponderation);
		
	int notesMax[nbNotes];
	notesMaximales(nbNotes,notesMax);
	
	const int TAILLECODEPERM = 12;
	char codePermanent[TAILLECODEPERM];
	
	int nbEtudiant = 0;
	int notesEtudiant[]={0,0,0,0,0,0,0,0,0,0,0,0};
	
	while(scanf("%s",codePermanent) != EOF){

		validerCodePermanent(TAILLECODEPERM,codePermanent);
		float moyenne = moyenneEtudiant(nbNotes, ponderation, notesMax);
		nbEtudiant++;
		
		ajouterNote(seuil, notesEtudiant, moyenne);		
	}
	
	int x;
	for(x = 0; x < 12; x++){
		printf("%lf = %d\n",seuil[x],notesEtudiant[x]);
	}
	return 0;
}

void extraireSeuil(double seuil[], char *argv[],int argc){
	
	int i;
	for(i = 1;i < argc;i++){
		seuil[i-1] = atof(argv[i]); 
	} 

}

void ajouterNote(double seuil[], int notesEtudiant[], float moyenne){	

	int i;
	for(i = 0; i < 11; i++){
		if(moyenne >= seuil[i]){
			notesEtudiant[i] = notesEtudiant[i] + 1;
			break;

		}else if(moyenne < seuil[10]){
			notesEtudiant[11] = notesEtudiant[11] + 1;
			break;
		}
	}
} 

float moyenneEtudiant(int nbNotes,int ponderation[], int notesMax[]){
	float moyenne = 0.0;
	float note;

	int i;
	for(i = 0; i < nbNotes; i++){
		scanf("%f",&note);

		if(note <= notesMax[i]){
			moyenne = moyenne + (note*ponderation[i]);
		}else{
			printf("note supérieur au maximum\n");
			exit(1);
		}		
	}

	return moyenne/100;
}

void validerCodePermanent(int taille, char codePerm[]){
	
	const int NBLETTRES = 4;
	int i;
	for(i = 0; i < taille; i++){
		if(i < NBLETTRES){
			if(codePerm[i] < 'A' || codePerm[i] > 'Z'){
				printf("erreur lettre code permanent\n");
				exit(1);
			}		
		}else{
			if(codePerm[i] < '0' || codePerm[i] > '9'){
				printf("erreur chiffre code permanent\n");
				exit(1);
			}
		}
			
	}
}

void notesMaximales(int nbNote,int notesMax[]){
	int i;

	for(i = 0; i < nbNote; i++){
		scanf("%d",&notesMax[i]);

		if(notesMax[i] < 1){
			printf("ERRREUR6\n");
			exit(1);
		}
	}
	
}

void pondererNote(int nbNotes, int ponderation[]){
	int v;
	int total = 0;

	for(v = 0; v < nbNotes; v++){
		scanf("%d",&ponderation[v]);
		total += ponderation[v];

		if(ponderation[v] < 0 || ponderation[v] > 100){
			printf("ERRREUR4\n");
			exit(1);
		}
	}
	if(total != 100){
		printf("ERREUR5\n");
		exit(1);
	}
	
}

int valideNbNotes(){
	const int NBMINTRAVAUX = 1;
	int nbNotes;
	scanf("%d",&nbNotes);
	
	if(nbNotes < NBMINTRAVAUX || nbNotes > DNBMAXTRAVAUX){
		printf("ERRRREUR3\n");
		exit(1);
	}
	
	return nbNotes;
}

void valideSeuil(int taille, double seuil[]){

	if(taille != 12){
		printf("ERRRRREUR\n");
		exit(1);
	}

	int i;
	for(i = 0; i < taille-1; i++){
		int n;
		for(n = i+1; n < taille; n++){
			if(seuil[i] <= seuil[n]){
				printf("ERRREUR 2\n");
				exit(1);
			} 
		}            
	}
}

