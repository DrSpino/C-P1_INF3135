#include <stdio.h>
#include <stdlib.h>                                                     
#include <string.h>
#include <math.h>

#define DNBMAXTRAVAUX 5

void valideSeuil(int taille, char *argv[], double seuil[]);
int valideNbNotes();
void pondererNote(int nbNotes, int ponderation[]);
void notesMaximales(int nbNote, int notesMax[]);
void validerCodePermanent(int taille, char codePerm[]);
float moyenneEtudiant(int nbNotes, int ponderation[], int notesMax[]);
void ajouterNote(double seuil[], int notesEtudiant[], float moyenne); 
void dessinerHisto(int taille, int notesEtudiant[]);
int nbMaxEtudiant(int nbEtudiants[],int taille);
void noteHisto(char note[],int i);

int main(int argc, char *argv[]){                                                                               
	
	double seuil[argc-1];
	valideSeuil(argc,argv,seuil);
	
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
	
	dessinerHisto(argc-1,notesEtudiant);

	return 0;
}

void noteHisto(char note[],int i){
	
	if(i == 0){
		note[0] = 'A';
		note[1] = '+';
		note[2] = '\0';
	}else if(i == 1){
		note[0] = 'A';
		note[1] = ' ';
		note[2] = '\0';
	}else if(i == 2){
		note[0] = 'A';
		note[1] = '-';	
		note[2] = '\0';
	}else if(i == 3){
		note[0] = 'B';
		note[1] = '+';
		note[2] = '\0';
	}else if(i == 4){
		note[0] = 'B';
		note[1] = ' ';
		note[2] = '\0';
	}else if(i == 5){
		note[0] = 'B';
		note[1] = '-';
		note[2] = '\0';
	}else if(i == 6){
		note[0] = 'C';
		note[1] = '+';
		note[2] = '\0';
	}else if(i == 7){
		note[0] = 'C';
		note[1] = ' ';
		note[2] = '\0';
	}else if(i == 8){
		note[0] = 'C';
		note[1] = '-';
		note[2] = '\0';
	}else if(i == 9){
		note[0] = 'D';
		note[1] = '+';
		note[2] = '\0';
	}else if(i == 10){
		note[0] = 'D';
		note[1] = ' ';
		note[2] = '\0';
	}else if(i == 11){
		note[0] = 'E';
		note[1] = ' ';
		note[2] = '\0';
	}
}

int nbMaxEtudiant(int nbEtudiants[],int taille){
	int nbEtudiantMax = 0;

	int i;
	for(i = 0;i < taille;i++){
		if(nbEtudiantMax < nbEtudiants[i]){
			nbEtudiantMax = nbEtudiants[i];
		}
	}
	
	return nbEtudiantMax;
}
void dessinerHisto(int taille, int notesEtudiant[]){
	
	int nbEtudiantMax = nbMaxEtudiant(notesEtudiant,taille);

	const double largeurHistogramme = 50.00;
	
	int i;
	for(i = taille; i >= 0;i--){
		int result = ceil(notesEtudiant[i]/ceil(nbEtudiantMax/largeurHistogramme));
		
		char note[3];
		noteHisto(note,i);
		
		printf("%s  ",note);
		
		int j;
		for(j = result;j > 0;j--){
			printf("%c",'X');
		}
		printf("%c",'\n');

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
		
		int ret = scanf("%f",&note);
		if(ret == 0){
			fprintf(stderr,"Un éleve à une note manquante !\n");			
			exit(1);
		}

		if(note <= notesMax[i]){
			moyenne = moyenne + (note*ponderation[i]);
		}else{
			fprintf(stderr,"Une note est supérieur à sont maximum autorisée !\n");
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
				fprintf(stderr,"Les 4 premiers caracteres du code permanent ne sont pas des lettres majuscules !\n");
				exit(1);
			}		
		}else{
			if(codePerm[i] < '0' || codePerm[i] > '9'){
				fprintf(stderr,"Le code permanent ne se termine pas par 8 chiffres !\n");
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
			fprintf(stderr,"Une note maximale est strictement inférieur à 1 !\n");
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
			fprintf(stderr,"Les pondérations ne sont pas comprises entre 1 et 100 !\n");
			exit(1);
		}
	}
	if(total != 100){
		fprintf(stderr,"La somme des pondérations n'est pas égale à 100 !\n");
		exit(1);
	}
	
}

int valideNbNotes(){
	const int NBMINTRAVAUX = 1;
	int nbNotes;
	scanf("%d",&nbNotes);
	
	if(nbNotes < NBMINTRAVAUX || nbNotes > DNBMAXTRAVAUX){
		fprintf(stderr,"le nombre d'évaluations n'est pas compris dans la limite autorisée !\n");
		exit(1);
	}
	
	return nbNotes;
}

void valideSeuil(int taille, char *argv[], double seuil[]){

	int i;
	for(i = 1;i < taille;i++){
		seuil[i-1] = atof(argv[i]); 
	} 

	const int NBVALEURSEUIL = 12;
	if(taille != NBVALEURSEUIL){
		fprintf(stderr,"Le nombre d'arguments valeur seuil est invalide !\n");
		exit(1);
	}

	for(i = 0; i < taille-1; i++){
		int n;
		for(n = i+1; n < taille; n++){
			if(seuil[i] <= seuil[n]){
				fprintf(stderr,"Les arguments ne sont pas spécifiées par ordre décroissant !\n");
				exit(1);
			} 
		}            
	}
}

