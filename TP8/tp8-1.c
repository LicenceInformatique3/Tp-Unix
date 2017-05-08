#define _GNU_SOURCE
#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, getpid, getppid
#include <signal.h> 
#include <sys/types.h>
#include <sys/wait.h>

int mysignal (int sig, void (*h)(int), int options){
	struct sigaction s;
	s.sa_handler = h;
	sigemptyset (&s.sa_mask);
	s.sa_flags = options;
	int r = sigaction (sig, &s, NULL);
	if (r < 0) perror (__func__);
	return r;
}

void capter(int sig){
	static int compteur = 0;
	compteur ++;
	printf("Recu signal %d fois \n", compteur);
}

int main(int argc, char *argv[]){
	int  n = atoi(argv[1]);
	int i;
	printf ("je suis %d\n",(int) getpid());
	pid_t p1;
	p1 = fork();
	if (p1 < 0) { 
    perror("fork"); 
    exit (1); 
  }
	if (p1 == 0) {  /* Fils  */
		for(i=0; i < n; i++){
			printf("signal emis %d fois\n", i+1);
			kill (getppid(), SIGUSR1);
		}
    	exit(0);
	}/*  fin du fils*/

	/*suite pere*/
	mysignal(SIGUSR1, capter, SA_RESTART);
	wait(NULL);
	exit(0);  
}
