#include <sys/stat.h>
#include <unistd.h>
#include "apue.h"
#include <fcntl.h>

/*+++++++++++++++++++++++++++++++++++++++++++++++++++=
 *
 *name: mkdir
 *function: create dir
 *include: sys/stat.h
 *params: 
 	1 pathname
	2 mode : file mode
 *return: 0 success,-1 failed
 * ++++++++++++++++++++++++++++++++++++++++++++++++*/
int mkdir(const char* pathname,mode_t mode);

int mkdirat(int fd,const char* pathname,mode_t mode);




/*++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: rmdir
 *function: remove a dir
 *include: unistd.h
 *params: 1 pathname
 *return: 0 success, -1 failed
 * +++++++++++++++++++++++++++++++++++++++++++++++*/
int rmdir(const char* pathname);




/*+++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: chdir
 *function: change current working directory
 *include: unistd.h
 *params: 1 pathname
 *return: 0 success,-1 failed.
 * +++++++++++++++++++++++++++++++++++++++++++++++*/
int chdir(const char* pathname);
int fchdir(int fd);


/*+++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: getcwd
 *function: get the absolute path of current working directory
 *include: unistd.h
 *params:
 	1 buf 
	2 size
 *return: buf if success ,else return NULL.
 * +++++++++++++++++++++++++++++++++++++++++++++++++*/
char* getcwd(char* buf , size_t size);



int main(int argc,char* argv[]){
	int ret;
	if(argc != 2)err_sys("argc error");
	if(*( argv[1]) =='d'){
	//	ret =  rmdir("tempdir");
		ret = unlink("tempfile");
	}

	if(*( argv[1])=='c'){
	//	ret=mkdir("tempdir",0700);
		ret = open("tempfile",O_RDWR|O_CREAT,0700);
	}

	if(ret<0)err_sys("error");
	return 0;


}
