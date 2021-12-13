#include <stdio.h>
#include "apue.h"


/*+++++++++++++++++++++++++++++++++++++
 *
 *name: setbuf
 *function: open or close stream buffer 
 *include: stdio.h
 *params:
 	1 FILE* fp 
	2 char* buf . a new buffer ,size is BUFSIZ.if buf is NULL ,close the stream buffer.
 *return: void
 * +++++++++++++++++++++++++++++++++++*/
void setbuf(FILE* restrict fp,char* restrict buf);




/*++++++++++++++++++++++++++++++++++++++
 *
 *name: setvbuf
 *function: open or close stream buffer.
 *include: stdio.h
 *params:
 	1 FILE* fp .
	2 char* buf .
	3 int mode .
		_IOFBF  all buffer {buf == !NULL,user buffer,buf ==NULL,system buffer }
		_IOLBF  line buffer{ buf == !NULL,user buffer;  buf ==NULL,system buffer }
		_IONBF  none buffer{ none buffer  }
	4 size_t size .
 *return: 0 success,!0 failed
 * ++++++++++++++++++++++++++++++++++++*/
int setvbuf(FILE* restrict fp,char* restrict buf,int mode,size_t size);




//flush
int fflush(FILE* fp);







#define BUFFERSIZE 10

int main(void){
	
	char buffer[BUFFERSIZE];
	if(setvbuf(stdout,buffer,_IOLBF,BUFFERSIZE)!=0){
		err_sys("servbuf error!");
	}

	char getbuf[200];
	while(fgets());
	
	
	return 0;
}












