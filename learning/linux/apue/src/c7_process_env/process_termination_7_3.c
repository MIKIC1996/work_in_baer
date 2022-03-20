#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>




/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: _exit
 *function: just terminate the process
 *include: unistd.h
 *params: status
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void _exit(int status);



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: _Exit
 *function: just terminate the process
 *include: unistd.h
 *params: status
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void _Exit(int status);



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: atexit
 *function: register exit handler; the sequence of exit handler executing is reversed from the sequence of register exit handler;
 *include: stdlib.h
 *params: func
 *return: 0 when success,else !0;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int atexit(void (*func)(void));



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: exit
 *function: close all io stream,  execute all exit handler,then terninate the process . it's equal to return ;
 *include: stdlib.h
 *params: status
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void exit(int status);


static void my_exit1(void);

static void my_exit2(void);


int main(int argc, char const *argv[])
{
    /* code */

    atexit(my_exit1);
    atexit(my_exit2);
    printf("main is done\n");

    return 0;
}


static void my_exit1(void){
    printf("my_exit1\n");
}

static void my_exit2(void){
    printf("my_exit2\n");
}






















