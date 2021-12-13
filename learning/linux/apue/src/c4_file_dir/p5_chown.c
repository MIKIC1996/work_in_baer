#include <unistd.h>


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: chown
 *function: change the file uid and gid ,
 	uid: only super user can change file uid. 
	gid: if ( process vaild user id == file user id ) and
       	( owner == -1 or owner == file user id)and
	(group == process vaild group id),
	then normal user can change the file gid.
 *include: unistd.h
 *params: 
 	1. pathname 
	2. owner
	3. group
 *return: 0 success , -1 error
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++*/

int chown(const char* pathname,uid_t owner,gid_t group);



int fchown(int fd,uid_t owner,gid_t group);


//change the link file  owner and group,not the file pointed by this link.
int lchown(const char* pathname,uid_t owner,gid_t group);


//if flag & AT_SYMLINK_NO_FOLLIW ,it is equal to lchown
int fchownat(int fd,const char *pathname,uid_t owner,gid_t group,int flag);
