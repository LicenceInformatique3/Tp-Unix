#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	(void) argc;
	printf("Je suis %d\n", (int)getpid());
	execvp(argv[1], argv+1);
	perror("exec");
	exit(1);
}

//2)
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	(void) argc;
	printf("Je suis %d\n", (int)getpid());
	pid_t p = fork();
	if(p < 0){
		perror("fork");
		exit(1);
	}

	if(p == 0) // fils{
		printf("Je suis le fils %d\n", (int)getpid());
		execvp(argv[1], argv+1);
		perror("exec");
		exit(1);
	} // fin fils

	// suite pere
	int info;
	wait(&info);
	int r = WEXITSTATUS(info);
	printf("Fin pere: r = %d: %s\n", r, r==0? "succes":"echec");
}
