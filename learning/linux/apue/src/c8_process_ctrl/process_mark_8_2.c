#include <unistd.h>
#include <stdio.h>




/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getpid
 *function: get current process id
 *include: unistd.h
 *params: void
 *return: process id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern pid_t getpid();

/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getppid
 *function: get current father process id
 *include: unistd.h
 *params: void
 *return: process id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern pid_t getppid();

/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getuid
 *function: get actual user id
 *include: unistd.h
 *params: void
 *return: user id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern uid_t getuid();

/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: geteuid
 *function: get vaild user id
 *include: unistd.h
 *params: void
 *return: user id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern uid_t geteuid();

/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getgid
 *function: get actual group id
 *include: unistd.h
 *params: void
 *return: group id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern gid_t getgid();

/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getegid
 *function: get vaild group id
 *include: unistd.h
 *params: void
 *return: group id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern gid_t getegid();

/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getresuid
 *function: get saved set user id
 *include: unistd.h
 *params: void
 *return: user id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern uid_t getresuid();


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getresgid
 *function: get saved set group id
 *include: unistd.h
 *params: void
 *return: group id
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern gid_t getresgid();


int main(int argc, char const *argv[])
{
    /* code */

    printf("pid:%d\n", getpid());
    printf("ppid:%d\n", getppid());
    printf("uid:%d\n",getuid());
    printf("euid:%d\n", geteuid());
    printf("resuid:%d\n",getresuid());
    printf("gid:%d\n", getgid());
    printf( "egid:%d\n",getegid());
    printf("resgid:%d\n",getresgid());

    return 0;
}
