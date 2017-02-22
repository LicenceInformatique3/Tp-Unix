#include <stdio.h>
#include <stdlib.h>        
#include <unistd.h>
#include <sys/wait.h>                //waitq
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>


void usage(int argc,  char *argv[]){
	if(argc-1 < 1){
		fprintf(stderr, "usage %s [-n nbfois] [-s] com [arg,... ]\n",argv[0]);
		exit(1);
	}
}

int indice_mot(int argc , char *argv[], char * mot ){
	for (int i = 0; i < argc; ++i)        {
		if (strcmp(mot,argv[i])==0){
			return i;
		}
	}
	return -1;
}

int main(int argc , char *argv[]){
	usage(argc,argv);
	int flag_n=0;
	int flag_s=0;
	int k=1;
	int temp=1;
	long int temps_sec,temps_usec;
	struct timeval tvalBefore, tvalAfter;
	if (strcmp("-n",argv[temp])==0){
		flag_n=1;
		k=atoi(argv[temp+1]);
		temp+=2;
	}
	if (strcmp("-s",argv[temp])==0){
		flag_s=1;
		temp++;
	}

	gettimeofday (&tvalBefore,NULL);
	for (int i = 0; i < k; ++i)
	{
		pid_t p=fork();
		if(p<0) {perror("fork"); exit (1); }
		if (p==0)
		{        //fils        
		if (flag_s!=1){
			int fd = open("/dev/ttyS0", O_WRONLY);
			dup2(fd, 1);  // redirect stdout
		}
		execvp(argv[temp],argv+temp);
		}        //finfils
		//suite pere
		wait(NULL);
	}
	gettimeofday (&tvalAfter,NULL);

	temps_sec=(tvalAfter.tv_sec-tvalBefore.tv_sec);
	temps_usec=(tvalAfter.tv_usec-tvalBefore.tv_usec);

	if (temps_usec < 0){
		temps_usec+=1000000;
	}
	double temps_final=temps_sec+((double) temps_usec/1000000);
	printf("temps total :%lf\n",temps_final );
	if (flag_n){
		printf("temps moyen :%lf\n",temps_final/k );
	}
	exit(0);
}
