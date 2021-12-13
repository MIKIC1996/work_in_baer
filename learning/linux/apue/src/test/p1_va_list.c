#include <stdarg.h>
#include <stdio.h>


typedef void* my_va_list;

#define my_va_start(ap,v) ( ap = (my_va_list)&v + sizeof(v)  )
#define my_va_arg(ap,t) ( *(t*) ((ap+= sizeof(t))-sizeof(t))  )
#define my_va_end(ap) ( ap=(my_va_list)0  )




int aveInt(int,...);

int my_aveInt(int,...);

int main(int argc,char* argv[]){
	
	

	int val = my_aveInt(3,3,6,9);
	printf("ave int is  %d\n",val);

	return 0;



}


int my_aveInt(int v,...){
	int returnVal = 0;
	int i=v;
	my_va_list ap;
	my_va_start(ap,v);
	while(i>0){
		int val = my_va_arg(ap,int);
		printf("%d\n", val );
		returnVal += val;
		i--;
	}
	my_va_end(ap);
	returnVal /=v;
	return returnVal;

}



int aveInt(int v,...){
	int returnVal =0;
	int i=v;
	va_list ap;
	va_start(ap,v);
	while(i>0){
		returnVal += va_arg(ap,int);
		i--;
	}
	va_end(ap);
	returnVal /= v;
	return returnVal;
	
}





