#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: fork
 *function: create a new process
 *include: unistd.h
 *params: void
 *return: father process get son pid,son process get 0, get -1 when failed.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern pid_t fork(void);


int glo = 6;

int main(int argc, char const *argv[])
{
    /* code */
    int val = 3;
    pid_t pid = 0;

    printf("before fork\n");

    if( (pid = fork())<0){
        printf("error");
        exit(0);
    }else if(pid ==0){
        glo++;
        val++;
    }else{
        sleep(2);
    }

    printf("glo = %d , val =%d ,pid = %d\n",glo,val,pid);
    return 0;
}





