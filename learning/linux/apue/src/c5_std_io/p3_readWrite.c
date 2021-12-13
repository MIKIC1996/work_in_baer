#include <stdio.h>
#include "apue.h"


/*+++++++++++++++++++++++++++++++++++
 *
 *name: getc ,fgetc , getchar
 *function:get a char from fp
 *include: stdio.h
 *params: 1 fp
 *return: char if success,else EOF
 * ++++++++++++++++++++++++++++++++*/
int getc(FILE* fp);
int fgetc(FILE* fp);

// getchar is equal to getc(stdin)
int getchar(void);



/*+++++++++++++++++++++++++++++++++++++
 *
 *name: ferror
 *function: test the fp if has error
 *include: stdio.h
 *params: 1 fp
 *return: !0 if success,else 0;
+++++++++++++++++++++++++++++++++++++*/
int ferror(FILE* fp);



/*++++++++++++++++++++++++++++++++++++
 *
 *name: feof
 *function:test the fp if has eof
 *include: stdio.h
 *params: 1 fp
 *return: !0 if success,else 0;
 * +++++++++++++++++++++++++++++++++*/
int feof(FILE* fp);


//clear the error and eof flag
void clearerr(FILE* fp);




/*++++++++++++++++++++++++++++++++++
 *
 *name: ungetc
 *function: push c to fp
 *include: stdio.h
 *params:
 	1 c .char
	2 fp
 *return: c if success,else EOF
 * ++++++++++++++++++++++++++++++++*/
int ungetc(int c,FILE* fp);




/*++++++++++++++++++++++++++++++++++++
 *
 *name: putc , fputc
 *function: write a byte.
 *include: stdio.h
 *params:
 	1. c .char
	2. fp
 *return:  c if success,else EOF.
 * ++++++++++++++++++++++++++++++++++*/
int putc(int c,FILE* fp);
int fputc(int c,FILE* fp);


//putchar(int c) is equal to putc(c,stdin);
int putchar(int __c);


/*+++++++++++++++++++++++++++++++++++
 *
 *name: fgets
 *function: read a line from fp
 *include: stdio.h
 *params:
 	1. buf,save bytes read from fp
	2. buf length, fgets only read n-1 bytes,last byte is \0.
	3. fp
 *return: buf if success ,else NULL
 * +++++++++++++++++++++++++++++++++*/
char* fgets(char* restrict buf,int n,FILE* restrict fp);



//gets is equal to fgets(buf,stdin);
char* gets(char* buf);



/*+++++++++++++++++++++++++++++++++++
 *
 *name: fputs
 *function: write a string ended with \0(C custom) into fp. PS: \o not writed into fp.
 *include: stdio.h
 *params:
 	1. str
	2. fp
 *return: >=0 if success,else EOF.
 * +++++++++++++++++++++++++++++++*/
int fputs(const char* restrict str,FILE* restrict fp);


//puts is equal to fputs(char* str,stdout)
int puts(const char* str);




int main(void){

	char buffer[10];
	while( fgets(buffer,10,stdin) != NULL){
		if(fputs(buffer,stdout)==EOF){
			err_sys("fputs error");
		}
	}

	if(ferror(stdin))
		err_sys("input error");


	return 0;
}



















