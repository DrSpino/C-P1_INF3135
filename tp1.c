#include <stdio.h>
#include <stdlib.h>                                                     

#define DNBMAXTRAVAUX 5

void valideSeuil(int taille, double seuil[]);

int main(int argc, char *argv[]){                                                                               

	if(argc != 12){
		printf("ERRRRREUR\n");
		exit(1);
	}

	double seuil [11] = {atof(argv[1]),atof(argv[2]),atof(argv[3]),
			atof(argv[4]),atof(argv[5]),atof(argv[6]), 
			atof(argv[7]),atof(argv[8]),atof(argv[9]), 
			atof(argv[10]),atof(argv[11])};     

	valideSeuil(argc,seuil);
	
	int c;
	scanf("%d",&c);
	
	if(c < 1 || c > DNBMAXTRAVAUX){
		printf("ERRRREUR3\n");
		exit(1);
	}

	return 0;
}

void valideSeuil(int taille, double seuil[]){
	int i;
	for(i = 1; i < taille-1; i++){
		int n;
		for(n = i+1; n < taille; n++){
			if(seuil[i] <= seuil[n]){
				printf("ERRREUR 2\n");
				exit(1);
			} 
		}            
	}
}
