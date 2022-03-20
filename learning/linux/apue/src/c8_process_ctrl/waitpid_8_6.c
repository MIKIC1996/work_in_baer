#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include "apue.h"
#include <stdlib.h>






/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: waitpid
 *function: wait until pid son process is terminated,get status infomation. if pid son process is terminated before execute wait(),
            wait will return soon;
 *include: sys/wait.h
 *params:   1. pid  ：  pid == -1 ,wait for any son process ,it is equal to wait();
                        pid > 0 ,wait for son process which's id is equal to pid;
                        pid == 0 ,wait for son process which's gid == current process's gid;
                        pid < -1 , wait for son proces which's gid ==  absolute value of (pid); 
            2. statloc , pointer to position which will be writed with son process end infomation ;
            3. option ;  0 , no option;
                        WNOHANG , don't wait,return 0;
 *return: return son pid if success ,else return 0 or -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern pid_t waitpid(pid_t pid,int * statloc,int options);




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


//如果不希望等待子进程，也不希望子进程处于 僵死状态（子进程结束，等待父进程获取其结束状态 ） 直到父进程结束。
int main(int argc, char const *argv[])
{
    
    /* code */
    pid_t pid;
    if((pid = fork())<0){
        err_sys("fork error");
    }
    else if(pid == 0){
        //子进程-----------------------
        if((pid = fork())<0){
            err_sys("son fork error");
        }else if(pid > 0){
            exit(0); //子进程退出
        }

        //子子进程
        sleep(2);//保证打印 的时候，上一个子进程 已经退出
        printf("second child ,parent id = %ld\n",(long)getppid()); //执行的时候，父进程 已经退出，他会被init进程接管
        exit(0);
        //子子进程

        //子进程
    }

    int statue;
    if( waitpid(pid,&statue,0) != pid ){
        err_sys("waitpid error");
    }else{
        pr_exit(statue);
    }

    return 0;
}

























