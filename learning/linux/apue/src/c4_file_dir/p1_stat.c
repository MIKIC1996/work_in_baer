#include <sys/stat.h>
#include <apue.h>




/*++++++++++++++++++++++++++++++++++++++++++++++
 *
 *struct stat{
 	mode_t  st_mode    file type| file access
	ino_t   st_ino    i node number
	dev_t   st_dev    ?????
 	dev_t   st_rdev   ?????
	nlink_t st_link   hard link number
	uid_t   st_uid    user id of owner
	gid_t   st_gid    group id of owner
	off_t   st_size   file length
	struct timespec  st_atime  ?????
	struct timespec  st_mtime  ?????
	struct timespec  st_ctime  ?????
	blksize_t  st_blksize   ?????
	blksize_t  st_blocks    ????? 
 
 }
 *+++++++++++++++++++++++++++++++++++++++++++++ */






int main(int argc,char* argv[]){
	
	int i=0;
	struct stat buf;
	char* ptr = NULL;

	for(i = 1;i<argc;++i){
		printf("%s:",argv[i]);
		if(lstat(argv[i],&buf)<0){
			err_ret("lstat error");
			continue;
		}
	
	}

	if(S_ISREG(buf.st_mode)){
		ptr = "regular";
	}else if(S_ISDIR(buf.st_mode)){
		ptr = "directory";
	}else if(S_ISCHR(buf.st_mode)){
		ptr = "character special";
	}else if(S_ISBLK(buf.st_mode)){
		ptr = "block special";
	}else if(S_ISFIFO(buf.st_mode)){
		ptr = "fifo";
	}else if(S_ISLNK(buf.st_mode)){
		ptr = "symbol link";
	}else if(S_ISSOCK(buf.st_mode)){
		ptr = "socket";
	}else{
		ptr="unknow";
	}
	printf("%s\n",ptr);
	return 0;
}
