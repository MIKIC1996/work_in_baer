#include <unistd.h>
#include <fcntl.h>
#include "apue.h"

#define MAXSIZE 200
#define SRC_PATH "./src/p1"

/*++++++++++++++++++++++++++++++++++++++++++++++++++
 *name: open
 *function: this function used to open a file 
 *include: <fcntl.h>
 *params:
	 1.path: absolute path or relative path
	 2 oflag:
	 [
	 	/you must chose one of the following 5 options/
		O_REONLY  only read
		O_WRONLY  only write
		O_RDWR    read and write
		O_EXEC    exec only
		O_SEARCH  search only

		/other choices/
		O_APPEND
		O_CLOEXEC
		O_CREAT   creat the file when the file not exist,but you must set the mode
		O_DIRECTORY
		O_EXCL   if you set the O_CREAT ande O_EXCL together,it will return error when 
			 file has been existed ,else it will create the file. it make testing and 
			 creation be a automic operation.
		O_NOCTTY
		O_NOFOLLOW
		O_NONBLOCK
		O_SYNC
		O_TRUNC
		O_TTY_INIT
		O_DSYNC
		O_RSYNC
	 ]
	 3.modes :visiting access
 ++++++++++++++++++++++++++++++++++++++++++++++++++*/
int open(const char* path,int oflag,.../*mode_t modes*/ );

//example
void open_test(){
	
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: openat
 *function: open a file (fd/path)
 *include: <fcntl.h>
 *params: 
 	1. fd: if the path is a absolute path,fd is ignored,else fd should be the 
		parent absolute path; if fd == AT_FDCWD,fd is equal to current work path.
		
 +++++++++++++++++++++++++++++++++++++++++++++++++++++ */
int openat(int fd,const char* path,int oflag,.../*mode_t modes*/);

//example
void openat_test(){
	char* buf = "hello";

	int fd =0;
	fd = open(SRC_PATH,O_RDONLY|O_DIRECTORY);
	if(fd <0){
		err_sys("openat_test:open error");
	
	}
	
	mode_t mode = 0640; //rw_ r__ ___

	fd = openat(fd,"openat.txt",O_WRONLY|O_CREAT,mode);
	if(fd <0){
		err_sys("openat_test_openat error");
	}
	if( write(fd,buf,5)<0){
		err_sys("wirte error");
	}

}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: creat
 *function: it is equal to open(const char*path,O_RDWR|O_CREAT|O_TRUNC);
 *include: <fcntl.h>
 *params: paths and mode 
 *return: <0 when error.
 +++++++++++++++++++++++++++++++++++++++++++++++++++ */
int creat(const char* path,mode_t mode);



/*+++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: close
 *function: close a file 
 *include <unistd.h>
 *params : 1.fd:  file fd
 +++++++++++++++++++++++++++++++++++++++++++++++++++*/
int close(int fd);




/*++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: lseek
 *function: this function used to set the current file offset
 *include: <unistd.h>
 *params:
	 1.fd :file fd
	 2.offset :offset value
	 3.whence:
	 	[
			SEEK_SET new file offset is the param offset
			SEEK_CUR new file offset is current file offset added the offset
			SEEK_END new file offset is file length added the offset
		]
 *return: new offset when ok,else -1.
 *+++++++++++++++++++++++++++++++++++++++++++++++++++ */
off_t lseek(int fd,off_t offset,int whence);





/*++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: read
 *function: read file 
 *include: unistd.h
 *params:
 	1 fd 
	2 buf record the bytes readed from file
	3 nbytes  read count
 *return: if success ,return the actual read count ,else -1
 *+++++++++++++++++++++++++++++++++++++++++++++++++ */
ssize_t read(int fd,void* buf,size_t nbytes);


void read_exp(int argc, char* argv[]){
	
	

}



/*++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: write
 *function: write file
 *include: unistd.h
 *params:
 	1 fd 
	2 buf bytes to write
	3 nbytes write count
 *return: if success,return nbytes,else return -1
+++++++++++++++++++++++++++++++++++++++++++++++++++*/
ssize_t write(int fd,const  void* buf,size_t nbytes);


void write_exp(){

	int fd ;
	if( (fd = open("./src/p1/src.txt",O_WRONLY|O_CREAT|O_TRUNC,0640))<0){
		err_sys("write_exp:open error");
	}

	char* buf = "hello world\n";
	
	if(write(fd,buf,strlen(buf))<0){
		err_sys("write_exp:write error");
	}


}

/*++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: dup
 *function: copy a current fd, it is equal to "fcntl(fd,F_DUPFD,0)".
 *include: unistd.h
 *params: 1. fd
 *return: new fd which is smallest and can be used,if failed, return -1.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
int dup(int fd);



/*++++++++++++++++++++++++++++++++++++++++++++++++
 *
 *name: dup2
 *function: you can point the fd you want
 *include: unistd.h
 *params: 
 	1.fd
	2.fd2 new fd you want
 *return: return fd2 if success,else return -1.
 * +++++++++++++++++++++++++++++++++++++++++++++++*/
int dup2(int fd,int fd2);



int main(){
	
	write_exp();
	return 0;
}
