#include <unistd.h>
#include "apue.h"
#include <fcntl.h>
#include <stdlib.h>

/*++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name:link
 *function:  create a new  directory unit(hard link)  which point to the file
 *include: unistd.h
 *params:
 	1. existingpath: file will be pointed
	2. newpath: file will be created
 *return: 0 success , -1 failed
 * +++++++++++++++++++++++++++++++++++++++++++*/
int link(const char* existingpath,const char* newpath);


//if flag efd is AT_FDCWD , it will find file by current work dir + existPath.
int linkat(int efd,const char* existingpath,int nfd,const char* newpath,int flag);


/*++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: unlink
 *function: delete a directory unit(hard link)  pointing to the file
 *include: unistd.h
 *params: 1. file path.
 *return: 0 success, -1 failed.
 * +++++++++++++++++++++++++++++++++++++++++*/
int unlink(const char* pathname);

//if flags set AT_REMOVEDIR ,it can remove dir;
int unlinkat(int fd,const char* pathname,int flags);


int main(){
	if(open("tempfile",O_RDWR|O_CREAT)<0)err_sys("open_error");
	if(unlink("tempfile")<0)err_sys("unlink_error");
	printf("file unlinked\n");
	sleep(16);
	printf("done\n");
	exit(0);

}




