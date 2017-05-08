#include <stdio.h>      // printf, perror
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, getpid, getppid

int main(){
	printf ("je suis %d\n",(int) getpid());
	pid_t p1;
	p1 = fork();
	if (p1 < 0) {
    perror("fork"); 
    exit (1);
  }
	if (p1 == 0) {  /* Fils  */
	    printf ("Je suis %d\n", (int) getpid());
	    execlp("who","who", NULL);
	    perror("exec who");
	    exit(1);
    }/*  fin du fils*/
    
	/*suite pere*/
	wait(NULL);
	pid_t p2;
	p2 = fork();
	if (p2 < 0){
    perror("fork"); 
    exit (1);
  }
	if (p2 == 0){  /* Fils 2  */
	    printf ("Je suis %d\n", (int) getpid());
	    execlp("pwd","pwd", NULL);
	    perror("exec pwd");
	    exit(1);
    }/*  fin du fils*/
    
	/*suite pere*/
	wait(NULL);

 	pid_t p3;
	p3 = fork();
	if (p3 < 0){ 
    perror("fork"); 
    exit (1);
  }
	if (p3 == 0){/* Fils 3  */
	    printf ("Je suis %d\n", (int) getpid());
	    execlp("ls","ls","-l", NULL);
	    perror("exec pwd");
	    exit(1);
    }/*  fin du fils*/
    
	/*suite pere*/
	wait(NULL);
	exit(0);   
}
