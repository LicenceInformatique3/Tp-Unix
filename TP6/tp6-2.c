#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, getpid, getppid

int main (int argc, char*argv[]) {
	if (argc-1 < 1){//argc-1 = nombre d'arguments
		fprintf(stderr,"Erreur, 2 entiers attendus\n");
		exit(1);
	}	
	pid_t p1;
	pid_t p2;
	int i=1;
	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	while (i <= x){
		p1 = fork();
		if (p1 < 0){ 
			perror("fork"); 
			exit (1); 
		}
		if (p1 == 0){  /* Fils  */
			printf ("Je suis %d fils %d de %d\n", (int) getpid(), i , (int) getppid());
			exit (0);
		} /* Fin fils  */
		int j = 1;
		while (j <= y){
			p2 = fork();
			if (p2 < 0){ 
				perror("fork"); 
				exit (1); 
			}
			if (p2 == 0){  /* Petit Fils  */
				printf ("Je suis %d petit fils %d de %d\n", (int) getpid(), j , (int) getppid());
				exit (0);
			} /* Fin petit fils  */
			j++;
		}
		i++;
	}

	/* Suite du pere */
	//printf ("je suis %d pere de %d\n", (int) getpid(), (int) p1);
	exit (0);
}
