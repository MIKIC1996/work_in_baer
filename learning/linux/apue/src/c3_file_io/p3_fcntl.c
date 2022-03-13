#include <fcntl.h>
#include "apue.h"

/*++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: fcntl
 *function: change file attributions.
 *include: fcntl.h
 *params: 
 	1 fd
	2 cmd[
		F_DUPFD  F_DUPFD_CLOEXEC        copy the file fd
		F_GETFD				get file fd
		F_SETFD				set file fd
		F_GETFL				get file statues
		F_SETFL 			set file statues
		F_GETOWN
		F_SETOWN
		F_GETLK
		F_SETLK
		F_SETLKW
	
	]
	3 .../ int args/
 *return: depending on cmd.
 * +++++++++++++++++++++++++++++++++++++++++*/

int fcntl(int fd,int cmd,.../*int args*/);



/*++++++++++++++++++++++++++++++++++++++
 * int atoi(const char* str) :change str to int.
 * ++++++++++++++++++++++++++++++++++*/
int fcntl_test(int argc,char* argv[]){

	if(argc!=2){
		err_sys("argc error");
	}

	int fl;

	if((fl = fcntl(atoi(argv[1]),F_GETFL,0))<0){
		err_sys("fcntl error");
	}

	switch(fl & O_ACCMODE){
	case O_RDONLY:
		printf("read only");
		break;
	
	case O_WRONLY:
		printf("write only");
		break;
	case O_RDWR:
		printf("read and write");
		break;
	default:
		err_sys("unknow access");
	}

	if(fl & O_APPEND){
		printf("append");
	}

	if(fl& O_NONBLOCK){
		printf("non block");
	}

	if(fl& O_SYNC){
		printf("sync write");
	}

	putchar('\n');
	return 0;


}



int main(int argc,char* argv[]){

	fcntl_test(argc,argv);
	return 0;
}



