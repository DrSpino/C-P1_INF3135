#include <stdio.h>
#include <stdlib.h>                                                     
#include <string.h>
#include <math.h>

//Defini le nombre de travaux max
#ifndef NBMAXTRAVAUX 
	#define NBMAXTRAVAUX 5
#endif

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

//Utile pour afficher le nom de l'executable dans les sorties d'erreur
const char * nomExe;

int main(int argc, char *argv[]){                                                                               

	nomExe = argv[0];
	double seuil[argc-1];
	valideSeuil(argc,argv,seuil);
	
	int nbNotes = valideNbNotes();

	int ponderation[nbNotes];
	pondererNote(nbNotes,ponderation);
		
	int notesMax[nbNotes];
	notesMaximales(nbNotes,notesMax);
	
	const int TAILLECODEPERM = 12;
	char codePermanent[TAILLECODEPERM];
	
	/*Partie qui permet de traiter les notes des étudiants.
	 */
	int notesEtudiant[12]={0};
	
	int ret = scanf("%s",codePermanent);	
	if(ret == 0){
		fprintf(stderr,"%s Le nombre de pondération ou de notes maximales doivent etre égale au nombre de note !\n",nomExe);
		exit(1);
	}	
	while(ret != EOF){

		validerCodePermanent(TAILLECODEPERM,codePermanent);
		float moyenne = moyenneEtudiant(nbNotes, ponderation, notesMax);
		
		ajouterNote(seuil, notesEtudiant, moyenne);		
		ret = scanf("%s",codePermanent);	
	}
	
	dessinerHisto(argc-1,notesEtudiant);

	return 0;
}

/*Cette fonction sert a tester les arguments 
 *entrees. Elle les stock en meme temps 
 *dans un tableau seuil[].
 */
void valideSeuil(int taille, char *argv[], double seuil[]){
	int i;
	for(i = 1;i < taille;i++){
		seuil[i-1] = strtod(argv[i], NULL); 
	} 

	const int NBVALEURSEUIL = 12;
	if(taille != NBVALEURSEUIL){
		fprintf(stderr,"%s Le nombre d'arguments valeur seuil est invalide !\n",nomExe);
		exit(1);
	}

	for(i = 0; i < taille-1; i++){
		int n;
		for(n = i+1; n < taille; n++){
			if(seuil[i] <= seuil[n]){
				fprintf(stderr,"%s Les arguments ne sont pas spécifiées par ordre décroissant !\n",nomExe);
				exit(1);
			} 
		}            
	}
}

/*Cette fonction permet de verifier que le nombre de travaux est
 *bien compris dans l'intervale demandée.
 *Elle retourne aussi le nombre de travaux dans nbNotes.
 */
int valideNbNotes(){
	const int NBMINTRAVAUX = 1;
	int nbNotes;
	scanf("%d",&nbNotes);
	
	if(nbNotes < NBMINTRAVAUX || nbNotes > NBMAXTRAVAUX){
		fprintf(stderr,"%s le nombre d'évaluations n'est pas compris dans la limite autorisée !\n",nomExe);
		exit(1);
	}
	
	return nbNotes;
}

/*pondererNote est utilisée pour verifier que les valeurs
 *des pondérations sont bien comprises entre 0 et 100.
 *Elle les stock ensuite dans le tableau des ponderations.
 */
void pondererNote(int nbNotes, int ponderation[]){
	int v;
	int total = 0;

	for(v = 0; v < nbNotes; v++){
		scanf("%d",&ponderation[v]);
		total += ponderation[v];

		if(ponderation[v] < 0 || ponderation[v] > 100){
			fprintf(stderr,"%s Les pondérations ne sont pas comprises entre 1 et 100 !\n",nomExe);
			exit(1);
		}
	}
	if(total != 100){
		fprintf(stderr,"%s La somme des pondérations n'est pas égale à 100 !\n",nomExe);
		exit(1);
	}
	
}

/*notesMaximales permet de verifier que les notes maximales sont positives.
 *Puis les stocks dans le tableau notesMax[].
 */
void notesMaximales(int nbNote,int notesMax[]){
	int i;

	for(i = 0; i < nbNote; i++){
		scanf("%d",&notesMax[i]);

		if(notesMax[i] < 1){
			fprintf(stderr,"%s Une note maximale est strictement inférieur à 1 !\n",nomExe);
			exit(1);
		}
	}
	
}

/*Cette fonction sert seulement à verifier que le code permanent
 *est valide selon les regles du devoir.
 */
void validerCodePermanent(int taille, char codePerm[]){
	
	const int NBLETTRES = 4;
	int i;
	for(i = 0; i < taille; i++){
		if(i < NBLETTRES){
			if(codePerm[i] < 'A' || codePerm[i] > 'Z'){
				fprintf(stderr,"%s Les 4 premiers caracteres du code permanent ne sont pas des lettres majuscules !\n",nomExe);
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

/*moyenneEtudiant est une fonction qui prend toutes les notes suivant
 *le codePermanent. Elle verifie que le nombre de note correspond à nbNotes
 *et que les notes ne sont pas supérieur à leur note maximale.
 *Ensuite elle calcul la moyenne grace aux ponderations puis la retourne.
 */
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

/*Cette fonction est utilisée pour attribuer une note selon
 *la moyenne obtenu par l'étudiant.
 */
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

/*dessinerHisto comme sont nom l'indique permet de dessiner
 *l'histogramme.
 *Elle fait appel aux fonctions nbEtudiantMax et noteHisto.
 */
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

//Retourne le nombre max d'etudiant toutes notes confondues.
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

/*Sert à savoir sur quel note nous opérons dans la 
 *boucle par grace à i. Elle Stock la chaine de caractere de la note
 *qui correspond dans le tableau note[].
 */
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
