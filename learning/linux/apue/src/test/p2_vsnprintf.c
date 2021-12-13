#include <stdarg.h>
#include <stdio.h>


#define MAXSIZE 200

int log_info(char* format,... ){

	char buffer[MAXSIZE];
	int i=0;
	va_list ap;
	va_start(ap,format);
	vsnprintf(buffer,MAXSIZE,format,ap);
	va_end(ap);
	printf("%s\r\n",buffer);
	return i;

}


int main(int argc , char* argv[]){

	log_info("%s,%d,%d","abc",10,20);



	return 0;
}
