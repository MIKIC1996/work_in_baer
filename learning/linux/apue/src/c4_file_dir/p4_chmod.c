#include <sys/stat.h>
#include "apue.h"




/*++++++++++++++++++++++++++++++++++++++++
 *#include <sys/stat.h>
 * the following 3 functions are used to modify the visit access
 * chmod need a absolute path or a relative path;
 * fchmod need a fd
 *
 * mode:{
 	S_ISUID	-> set the file user id with proccess user id when executing the file 
 	S_ISGID -> set the group id with process group id when executing the file
 	S_ISVTX ->
	
	S_IRWXU 
	S_IRUSR
	S_IWUSR
	S_IXUSR

	S_IRWXG
	S_IRGRP
	S_IWGRP
	S_IXGRP

	S_IRWXO
	S_IROTH
	S_IWOTH
	S_IXOTH
 * }
 * +++++++++++++++++++++++++++++++++++++++*/
int chmod(const char* pathname,mode_t mode);

int fchmod(int fd ,mode_t mode);

int fchmodat(int fd,const char* pathname,mode_t mode,int flags);



int main(int argc,char* argv[]){

	struct stat buf;

	


	exit(0);
}








