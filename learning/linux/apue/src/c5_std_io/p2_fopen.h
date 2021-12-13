#include <stdio.h>




/*+++++++++++++++++++++++++++++++++++++
 *
 *name: fopen
 *function: open a file ,return FILE*
 *include: stdio.h
 *params:
 	1 pathname
	2 type .
		r  | rb
		w  | wb
		a  | ab 
		r+ | r+b | rb+
		w+ | w+b | wb+
		a+ | a+b | ab+
 *return: FILE* if success , NULL if failed.
 * ++++++++++++++++++++++++++++++++++*/

FILE* fopen(const char* restrict pathname,const char* restrict type);

FILE* fdopen(int fd,const char* type);


/*++++++++++++++++++++++++++++++++++++++++
 *
 *name: freopen
 *function: open a file on stream fp,if fp is opened , close fp first.
 		this function can also remove the stream orientaion like fwide,
 *include: stdio.h
 *params:
 	1. pathname
	2. type
	3. fp
 *return: FILE* if success,else NULL .
 * +++++++++++++++++++++++++++++++++++++*/

FILE* freopen(const char* restrict pathname,const char* restrict type,FILE* restrict fp);








