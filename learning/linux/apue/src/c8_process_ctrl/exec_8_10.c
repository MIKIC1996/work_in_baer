#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>




/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: execve
 *function: execute a new program in current process,this is a system call;
 *include: unistd.h
 *params:   1. program abs path,
            2. args
            3. env variable table
 *return: no return when success,else return -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int execve(const char* pathname,char* const argv[],char* const envp[]);



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: fexecve
 *function: execute a new program in current process,this is a system call,
            it call execve by build path from /proc/self/fd;
 *include: unistd.h
 *params:   1. program abs path,
            2. args
            3. env
 *return: no return when success,else return -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int fexecve(int fd,char* const argv[],char* const envp[]);
/*
{
    const char * pathname = build path by fd;
    execve(path,argv,envp);
}
*/



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: execv
 *function: execute a new program in current process,this is a system call,
            it call execve by using envrion an param 3;
 *include: unistd.h
 *params:   1. program abs path,
            2. args
 *return: no return when success,else return -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int execv(const char* pathname, char* const argv[]);
/*
{   
    extern char* const envrion[];
    execve(pathname , argv , envrion); 
}
*/


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: execvp
 *function: execute a new program in current process,this is a system call,
            it call execv by finding file name in envrion path set;
 *include: unistd.h
 *params:   1. program name,
            2. args
 *return: no return when success,else return -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int execvp(const char* filename, char* const argv[]);
/*
{   
    extern char* const envrion[];
    const char* pathname = find filename in envrion;
    execv(pathname , argv ); 
}
*/


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: execl
 *function: execute a new program in current process,this is a system call,
            it call execv by transforming arg0... to argv[];
 *include: unistd.h
 *params:   1. program name,
            2. args...
 *return: no return when success,else return -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int execl(const char* pathnname,const char* arg0,.../*(char*)0*/);


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: execlp
 *function: execute a new program in current process,this is a system call,
            it call execvp by transforming arg0... to argv[];
 *include: unistd.h
 *params:   1. program name,
            2. args
 *return: no return when success,else return -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int execlp(const char* filename,const char* arg0,.../*(char*)0*/);


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: execvp
 *function: execute a new program in current process,this is a system call,
            it call execve by transforming arg0... to argv[];
 *include: unistd.h
 *params:   1. program name,
            2. args
 *return: no return when success,else return -1;
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int execle(const char* pathname,const char* arg0,.../* (char*)0，char* const envp[] */);


char* env_init[]= {"USER=unknow","PATH=/tmp",NULL};

int main(int argc, char const *argv[])
{
    /* code */
    pid_t pid=0;
    const char* pathname = "/home/mikic/jmq_code/apue/src/c7_process_env/echoall.exe";
    const char* filename = "echoall.exe";

    pid = fork();
    if(pid == 0){
        if( execle( pathname,"echoall","arg0","arg1",(char*)0,env_init )<0){
            printf("error in fork1\n");
            exit(0);
        }
    }

    if(waitpid(pid,NULL,0)<0){
        printf("error in wait\n");
        exit(0);
    }


    pid = fork();
    if(pid == 0){
        //当前环境变量中找不到filename,手动设置下
        if(execlp(filename,"echoall","arg0","arg1",(char*)0)<0){
             printf("error in fork2\n");
            exit(0);
        }
    }


    return 0;
}
