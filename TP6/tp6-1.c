#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, getpid, getppid

int main (int argc, char*argv[]){
	if (argc-1 < 1){//argc-1 = nombre d'arguments
		fprintf(stderr,"Erreur, 1 entier attedu\n");
		exit(1);
	}	
	pid_t p;
	int i = 1;
	int x = atoi(argv[1]);

	while (i <= x){
		p = fork();
		if (p < 0) { 
			perror("fork"); 
			exit (1); 
		}
		if (p == 0) {  /* Fils  */
			printf ("Je suis %d fils %d de %d\n", (int) getpid(), i , (int) getppid());
			exit (0);
		} /* Fin fils  */
		i++;
	}

	/* Suite du pere */
	printf ("je suis %d pere de %d\n", (int) getpid(), (int) p);
	exit (0);
}
