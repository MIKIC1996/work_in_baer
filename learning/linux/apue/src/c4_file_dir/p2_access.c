#include "apue.h"
#include <unistd.h>



/*+++++++++++++++++++++++++++++++++++++++++++
 *this function used to vetify if the actual process user ID is accessed to use file with mode 
 mode:{
	F_OK: if file has been existed; 
	R_OK: read access;
	W_OK: write access;
	X_OK: exec access;
 }
 +++++++++++++++++++++++++++++++++++++++++++*/
int access(const char* pathname ,int mode);






int main(int argc,char* argv[]){

	if(argc!=2){
		err_sys("error argc");
	}

	if(access(argv[1],R_OK)){
		err_ret("read access ok");
	}else{
		err_ret("read access fail");
	}

	return 0;

}
