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

pid_t p1;

void capter_pere(int sig) {
	printf("pere capte %d \n", SIGUSR1);
	kill (p1, SIGUSR1);
}

void capter_fils(int sig) {
	printf("Fils capte %d \n", SIGUSR1);
}

int main(int argc, char *argv[]){
	int  n = atoi(argv[1]);
	int i;
	printf("je suis %d\n", (int) getpid());

	p1 = fork();
	if (p1 < 0) { 
    perror("fork"); 
    exit (1); 
  }
	if (p1 == 0) {  /* Fils  */
		mysignal(SIGUSR1, capter_fils, SA_RESTART);
		for(i=0; i < n; i++){
			printf("signal emis \n");
			printf("je meurs\n");
			kill (getppid(), SIGUSR1);
			while(1) pause();
		}
    	exit(0);
	}/*  fin du fils*/

	/*suite pere*/
	mysignal(SIGUSR1, capter_pere, SA_RESTART);
	printf("fin fils, je meurs\n");
	wait(NULL);
	exit(0);  
}
