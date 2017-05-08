//TD 6

//I - Creation
//1)
#include <stdio.h>     //printf, perror
#include <stdlib.h>    //exit
#include <sys/types.h> //pid_t
#include <unistd.h>    //fork, getpid, getppid

int main(){
	pid_t p1 = fork();
	if(p1 < 0){
		perror("fork");
		exit(1);
	}

	if(p1 == 0) // fils 1{
		printf("Je suis %d fils 1 de %d\n", (int)getpid(), (int)getppid());
		exit(0);
	} // fin fils 1

	// suite du père
	pid_t p2 = fork();
	if(p2 < 0){
		perror("fork");
		exit(1);
	}


	if(p2 == 0) // fils 2{
		printf("Je suis %d fils 2 de %d\n", (int)getpid(), (int)getppid());
		exit(0);
	} // fin fils 2

	// suite du père
	printf("Je suis %d pere de %d et %d\n", (int)getpid(), (int)p1, (int)p2);
	exit(0);
}

//2)
#include <stdio.h>     //printf, perror
#include <stdlib.h>    //exit
#include <sys/types.h> //pid_t
#include <unistd.h>    //fork, getpid, getppid

int main(){
	pid_t p1 = fork();
	if(p1 < 0){
		perror("fork");
		exit(1);
	}

	if(p1 == 0) // fils 1{
		printf("Je suis %d fils 1 de %d\n", (int)getpid(), (int)getppid());
		pid_t p2 = fork();
		if(p2 < 0){
			perror("fork");
			exit(1);
		}
		if(p2 == 0) // petit-fils 1-1{
			printf("Je suis %d petit-fils 1 de %d\n", (int)getpid(), (int)getppid());
			exit(0);
		} // fin petit-fils 1
		exit(0);
	} // fin fils 1

	// suite du père
	printf("Je suis %d pere de %d et grand-pere de %d\n", (int)getpid(), (int)p1, (int)p2);
	exit(0);
}

//3)
#include <stdio.h>     //printf, perror
#include <stdlib.h>    //exit
#include <sys/types.h> //pid_t
#include <unistd.h>    //fork, getpid, getppid

int main(){
	while(1){
		sleep(2);
		pid_t p1 = fork();
		if(p1 < 0){
			perror("fork");
			exit(1);
		}
		if(p1 > 0)
			exit(0); //pere
		// suite du fils, avec un nouveau pid
		printf("Mon pid est %d\n", (int)getpid());
	}
	exit(0);
}

// II - Terminaison
//1)
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
	pid_t p;
	p = fork();
	if(p < 0){
		perror("fork");
		exit(1);
	}

	if(p == 0) // fils{
		printf("Je suis %d fils de %d\n", (int)getpid(), (int)getppid());
		sleep(5);
		printf("Fin fils\n");
		exit(0);
	} // fin fils

	// suite du père
	printf("Je suis %d pere de %d\n", (int)getpid(), (int)p);
	wait(NULL);
	printf("Fin pere qpres detection fin fils\n");
	exit(0);
}

//2)
int main(){
	pid_t p;
	p = fork();
	if(p < 0){
		perror("fork");
		exit(1);
	}

	if(p == 0) // fils{
		printf("Je suis %d fils de %d\n", (int)getpid(), (int)getppid());
		printf("Fin fils\n");
		exit(37);
	} // fin fils

	// suite du père
	printf("Je suis %d pere de %d\n", (int)getpid(), (int)p);
	int stat_info;
	wait(&stat_info);
	int s = WEXITSTATUS(stat_info);
	printf("Fin pere qpres detection fin fils, qui termine avec le status = %d\n", s);
	exit(0);
}

// III - Recouvrement
//1)
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(){
	printf("Je suis %d\n", (int)getpid());
	char *argv[] = {"ls", "-l", "/home", NULL};
	execvp("ls", argv);
	perror("exec ls");
	exit(1);
}
