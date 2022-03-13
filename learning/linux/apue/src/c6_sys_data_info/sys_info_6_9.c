#include <unistd.h>
#include <stdio.h>
#include <sys/utsname.h>



/*
struct utsname{
    char sysname[]  :name of os
    char nodename[] :name of this node
    char release[]  :current release of os;
    char version[]  :current version of this release;
    char machine[]  :name of hardware type;
}
*/


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getgroups
 *function: get system info
 *include: sys/utsname.h
 *params:   1. pointer to utsname
 *return:   0 when success,else -1
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int uname(struct utsname* name);


int main(int argc, char const *argv[])
{
    /* code */
    struct utsname uts;

    if( uname(&uts)<0){
        printf("error");
        return -1;
    }

    printf("os: %s\n",uts.sysname);
    printf("nodename: %s\n",uts.nodename);
    printf("current release of os: %s\n",uts.release);
    printf("current version of this release: %s\n",uts.version);
    printf("name of hardware type: %s\n",uts.machine);
    return 0;
}
