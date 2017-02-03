#include <stdio.h>
#include <stdlib.h>                                                     

int main(int argc, char *argv[]){                                                                               

	if(argc != 12){                                                                                                                 
		printf("ERRRRREUR\n");                                                                                                  
		exit(1);
	}

	double bareme [11] = {atof(argv[1]),atof(argv[2]),atof(argv[3]),
			atof(argv[4]),atof(argv[5]),atof(argv[6]), 
			atof(argv[7]),atof(argv[8]),atof(argv[9]), 
			atof(argv[10]),atof(argv[11])};     

	int i;
	for(i = 1; i < argc-1; i++){
		int n;
		for(n = i+1; n < argc; n++){
			if(bareme[i] <= bareme[n]){
				printf("ERRREUR 2\n");
				exit(1);
			}
		}
	}

	return 0;
}
