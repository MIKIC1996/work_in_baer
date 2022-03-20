#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: vfork
 *function: create a new process,father wait until the son process executes exit() or exec();
 *include: unistd.h
 *params: void
 *return: father process get son pid,son process get 0, get -1 when failed.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern pid_t vfork(void);

int glo = 6;

int main(int argc, char const *argv[])
{
    /* code */
    int val = 3;
    pid_t pid = 0;

    printf("before fork\n");

    if( (pid = vfork())<0){
        printf("error");
        exit(0);
    }else if(pid ==0){
        glo++;
        val++;
        _exit(0);  // 如果调用 exit(0) ,会关闭输出流，下面的printf会报错
    }else{
        printf("glo = %d , val =%d ,pid = %d\n",glo,val,pid);
    }

    
    return 0;
}
