#include <unistd.h>
#include <stdio.h>
#include <grp.h>



//  in file /etc/passwd,user has a basic group id, it can belong to other groups,which is called as suppleMentary group.
//  you can search groups user belongs to in file /etc/group,all of them is supplementary group, except the basic group recorded in /etc/passwd.



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getgroups
 *function: get the group ids which current user process belongs to;
 *include: unistd.h
 *params:   1. size of grouplist.
            2. space to record the result.
 *return:   actual count of items which recorded into grouplist when success , else -1.
            if(gidsetsize ==0),return the supplementray group counts without writing grouplist.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int getgroups(int gidsetsize,gid_t grouplist[]);


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: setgroups
 *function: set the group ids which current user process belongs to;
 *include: grp.h
 *params:   1. size of grouplist.
            2. data used to set groupid.
 *return:  return 0 when success,else return -1.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int setgroups(int ngroups, const gid_t grouplist[]);



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: initgroups
 *function: set the group ids which current user process belongs to;
 *include: grp.h
 *params:   1. size of grouplist.
            2. data used to set groupid.
 *return:  return 0 when success,else return -1.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int initgroups(const char* username,gid_t basegid);

