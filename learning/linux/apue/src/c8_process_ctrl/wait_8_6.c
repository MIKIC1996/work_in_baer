#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "apue.h"
#include <stdlib.h>




/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: wait
 *function: wait until a son process is terminated,get status infomation. 
            if a son process is terminated before execute wait(),
            wait will return soon;
 *include: sys/wait.h
 *params: 1. statloc , pointer to position which will be writed with son process end infomation 
 *return: return son pid if success ,else return 0 or -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern pid_t wait(int * statloc);




//对返回值进行分析的函数
void pr_exit(int status){

    if(WIFEXITED(status)){//正常退出
        printf("normal termination ,exit status = %d\n",WEXITSTATUS(status));//获取返回值
    }
    else if(WIFSIGNALED(status)){   //进程异常中止
        printf("abnormal termination , signal number = %d : %s\n",
        WTERMSIG(status), //获取中止信号
#ifdef WCOREDUMP
        WCOREDUMP(status) ? "core file generated" : "");
#else
        "");
#endif   
    }
    else if(WIFSTOPPED(status)) { //进程暂停
        printf("child stoped,signal number = %d\n",WSTOPSIG(status));//获取暂停信号
    }

}


int main(int argc, char const *argv[])
{
    /* code */
    //正常退出
    pid_t pid;
    int status;

    if((pid = fork())<0){
        err_sys("fork error");
    }else if(pid ==0){
        exit(7);
    }

    if(wait(&status) != pid ){
        err_sys("wait error");
    }
    pr_exit(status);

    //终止信号
    if((pid = fork())<0){
        err_sys("fork error");
    }else if(pid ==0){
        abort();
    }

    if(wait(&status) != pid ){
        err_sys("wait error");
    }
    pr_exit(status);

    //除0终止
    if((pid = fork())<0){
        err_sys("fork error");
    }else if(pid ==0){
        status /=0; //SINFPE 信号
    }

    if(wait(&status) != pid ){
        err_sys("wait error");
    }
    pr_exit(status);
    
    return 0;
}














