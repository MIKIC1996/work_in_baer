#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: signal
 *function: set signal handler for signo
 *include: sys/wait.h
 *params:   1. signo ;
            2. signal handler, or SIG_IGN , SIG_DFL;
 *return: return ord signal handler when success,else return SIG_ERR
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void(* signal(int signo,void(*func)(int)) )(int);


static void sig_handler(int signo);



int main(int argc, char const *argv[])
{
    /* code */
    if( signal(SIGUSR1,sig_handler)==SIG_ERR ){
        printf("error1");
        exit(0);
    }

    if( signal(SIGUSR2,sig_handler)== SIG_ERR ){
        printf("error2");
        exit(0);
    }

    for(;;)
        pause();



    return 0;
}

static void sig_handler(int signo){
    if(signo == SIGUSR1){

        printf("receive signal user1\n");
    }
    else if(signo == SIGUSR2){
        printf("received signal user2\n");
    }
    else{
        printf("dump\n");
        exit(0);
    }





}



