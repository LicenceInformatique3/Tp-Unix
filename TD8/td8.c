//TD 8

// I - Alarme
//1)
#define _GNU_SOURCE //en premier
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int mysignal (int sig, void (*h)(int), int options){
	struct sigaction s;
	s.sa_handler = h;
	sigemptyset (&s.sa_mask);
	s.sa_flags = options;
	int r = sigaction (sig, &s, NULL);
	if (r < 0) perror (__func__);
	return r;
}

void capter_ALRM(int sig){
	static int compteur = 0;
	compteur ++;
	printf("compteur = %d\n", compteur);
	if(compteur < 5) alarm(2);
	else exit(0);
}

int main(){
	mysignal(SIGALRM, capter_ALRM, SA_RESTART);
	alarm(2);
	int c;
	while((c = getchar()) != EOF)
		putchar(c);					//putchar(c);
	exit(0);						//ecrit le caractere
}									//c sur stdout

//2)
#define _GNU_SOURCE //en premier
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

pid_t pid_pere = 0;

void capter(int sig){
	printf("Recu signal %d\n", sig);
	alarm(1);
	if(kill(pid_pere, 0) < 0) //pid_pere == getpid(){
		printf("Fils detecte fin pere\n");
		exit(0);
	}
}

int main(){
	pid_pere = getpid();
	printf("Pere %d\n", (int)pid_pere);
	pid_t p = fork();
	if(p < 0){
		perror("fork");
		exit(1);
	}

	if(p == 0) // fils{
		printf("Fils %d\n", (int)getpid());
		mysignal(SIGALRM, capter, SA_RESTART);
		alarm(1);
		while(1) pause(); //maintient le fils vivant
		exit(0);
	} // fin fils

	//suite pere
	int c;
	while((c = getchar()) != EOF)
		putchar(c);
	exit(0);
}

//protege le fils de SIGINT
//mysignal(SIGINT, SIG_IGN, SA_RESTART);

// II - Transmission de valeur
//1)
#define _GNU_SOURCE //en premier
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int envoyer_signal_int(int sig, int val, int pid){
	union sigval value;
	value.sigval_int = val;
	int r = sigqueue(pid, sig, value);
	if(r < 0) perror(__func__);
	return r;
}

int main(int argc, char *argv[]){
	if(argc-1 != 3){
		fprintf(stderr, "Usage: %s sig val pid\n", argv[0]);
		exit(1);
	}
	int sig = atoi(argv[1]);
	int val = atoi(argv[2]);
	int pid = atoi(argv[3]);
	printf("Envoi du signal...\n");
	int k = envoyer_signal_int(sig, val, pid);
	exit(k == 0? 0:1);
}

//2)
int qsignal(int sig, void(*k)(int, sig_info_r*, void *), int options){
	struct sigaction s;
	s.SA_sigaction = h;
	sigemptyset(&s.sa_mask);
	s.sa_flags = options | SA_SIGINFO;
	int r = sigaction(sig, &s.NULL);
	if(r < 0) perror(__func__);
	return r;
}

void capter(int sig, sig_info_r *info, void(*ctx)){
	(void) ctx; //inutilisé
	printf("Signal %d capté\n", sig);
	if(info->si_code == SI_QUEUE)
		printf("PID emetteur %d, valeur %d\n", info->si_pid, info->si_value.sigval_int);
}

int main(){
	for(int i = r; i < NSIG; i++)
		qsignal(i, capter, SA_RESTART);
	//maintient le processus en vie
	while(1) pause();
	exit(0);
}
