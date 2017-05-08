//TD 7

// I - Recouvrement en sursis
//1)
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc-1 < 3){
		fprintf(stderr, "Usage: %s nbsec sig com[args...]\n", argv[0]);
		exit(1);
	}
	int nbsec = atoi(arg[1]);
	int sig = atoi(argv[2]);

	// recouvrement
	execvp(argv[3], argv+3);
	perror("exec");
	exit(1);
}

//2)
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc-1 < 3){
		fprintf(stderr, "Usage: %s nbsec sig com[args...]\n", argv[0]);
		exit(1);
	}
	int nbsec = atoi(arg[1]);
	int sig = atoi(argv[2]);

	pid_t p = fork();
	if(p < 0){
		perror("fork");
		exit(1);
	}

	if(p == 0) // fils{
		// recouvrement
		execvp(argv[3], argv+3);
		perror("exec");
		exit(1);
	} // fin fils

	// suite du pere
	printf("Pere attend %d secondes...\n", nbsec);
	sleep(nbsec);
	printf("Envoi du signal %d au fils %d\n", sig, (int)p);
	if(kill(p, sig) < 0)
		perror("Kill");
	printf("Pere attend fin fils\n");
	wait(NULL);
	printf("Fin pere\n");
	exit(0);
}

// II - La commande mywhile
//1)
int indice_mot(int argc, char *argv[], char *mot){
	for(int i=1; i < argc; i++){
		if(strcmp(mot, argv[i]) == 0)
			return i;
  }
	return -1;
}

//2)
void execute_com(char *argv[], int ind1, int ind2){
	argv[ind2] == NULL;
	execvp(argv[ind1], argv+ind1);
	perror("exec");
	exit(1);
}

//3)
int main(int argc, char *argv[]){
	int ind_do = indice_mot(argc, argv, "--do");
	int ind_done = indice_mot(argc, argv, "--done");
	if(ind_do < 2 || ind_done - ind_do < 2 || ind_done != argc-1){
		fprintf(stderr, "Usage: %s com1[arg...] --do com2[arg...] --done\n", argv[0]);
		exit(1);
	}
	while(1){
		pid_t p1 = fork();
		if(p1 < 0){
			perror("fork");
			exit(1);
		}

		if(p1 == 0) // fils 1{
			execute_com(argv, 1, ind_do);
		} // fin fils 1

		// suite pere
		int infos;
		wait(&infos);
		int s = WEXITSTATUS(infos);
		if(s != 0)
			exit(s); //fin while

// com1 a reussi, on execute com2
		pid_t p2 = fork();
		if(p2 < 0){
			perror("fork");
			exit(1);
		}

		if(p2 == 0) // fils 2{
			execute_com(argv, ind_do+1, ind_done);
		} // fin fils 2

		//suite pere
		wait(NULL);
	} 
}
