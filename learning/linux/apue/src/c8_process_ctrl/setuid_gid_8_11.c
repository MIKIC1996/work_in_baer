#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>






/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: setuid
 *function: if current process has root access , set the process actual user id, vaild user id and saved set user id  as uid
            else set vaild user id as uid which is equal to actual user id or saved set user id.
 *include: unistd.h
 *params: uid
 *return: 0 when success ,else -1.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int setuid(uid_t uid);




extern int setgid(gid_t gid);





/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: seteuid
 *function: if current process has root access , set vaild user id as uid
            else set vaild user id as uid which is equal to actual user id or saved set user id.
 *include: unistd.h
 *params: uid
 *return: 0 when success ,else -1.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int seteuid(uid_t uid);



extern int setegid(gid_t gid);




/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: setreuid
 *function: if current process has root access , set actual user id as ruid,
                set vaild user id and saved set user id as euid.
            else exchange ruid and euid, or set vaild user id as saved set user id.
 *include: unistd.h
 *params:   1 ruid: actual user id.
            2 euid: vaild user id.
 *return: 0 when success ,else -1.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern int setreuid(uid_t ruid,uid_t euid);


extern int setregid(gid_t rgid,gid_t egid);



























