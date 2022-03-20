#include <unistd.h>
#include <stdio.h>


//通过全局变量访问 环境变量表
extern char** environ;


int main(int argc, char const *argv[])
{
    /* code */

    char** env = environ;
    while(*env != NULL){
        printf("%s\n", *env);
        ++env;
    }

    return 0;
}
