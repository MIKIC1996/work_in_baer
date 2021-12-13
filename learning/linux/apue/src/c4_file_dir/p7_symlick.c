#include <unistd.h>
#include "apue.h"
#include <stdio.h>
#include <fcntl.h>


/*++++++++++++++++++++++++++++++++++++++++++=
 *
 *name: symlink
 *function: create a symlink
 *include: unistd.h
 *params: 
 	1 actualpath
	2 sympath
 *return: 0 success,-1 failed
 * ++++++++++++++++++++++++++++++++++++++++*/
int symlink(const char* actualpath,const char* sympath);

int symlinkat(const char* actualpath,int fd,const char* sympath);




/*++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: readlink
 *function: open will follow symlink,the following function can open symlink,read the content,
 	and close the symlink
 *include: unistd.h
 *params: 
 	1 pathname
	2 buf,used to save content readed from symlink
	3 bufsize
 *return: actual read count if success,else -1
 * ++++++++++++++++++++++++++++++++++++++++++*/
ssize_t readlink(const char* restrict pathname,char* restrict buf,size_t bufsize);


ssize_t readlinkat(int fd,const char* restrict pathname,char* restrict buf,size_t bufsize);


int main(){
	
	char buf[200];

	if(open("temp1",O_RDWR|O_CREAT)<0)err_sys("open error");

	if( symlink("temp1","tempfile")<0)err_sys("symlink error");

	if(unlink("temp1")<0)err_sys("unlink1");
	

	int readcount = readlink("tempfile",buf,200);
	if(readcount<0)err_sys("read symlink error ");
	buf[readcount]='\0';
	printf("%s\n",buf);
	
	sleep(10);

	if(unlink("tempfile")<0)err_sys("unlink2");

	return 0;
}









