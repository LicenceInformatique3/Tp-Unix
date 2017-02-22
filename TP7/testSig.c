#include <stdio.h>
#include <stdlib.h>        
#include <unistd.h>
#include <signal.h>

void capter_INT()
{
        printf("\nOuch !\n");
        alarm(5);
}

void capter_ALRM()
{
        printf("ARGGGH !\n");
        exit(0);
}

int main(){
        signal(SIGALRM, capter_ALRM);
        while (1){
                sleep(1);
                printf("Alive\n");
                signal(SIGINT, capter_INT);
        }
}
