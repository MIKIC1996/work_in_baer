#include <unistd.h>
#include <stdio.h>
#include <shadow.h>



/*
struct spwd{
    char* sp_mamp   :user name
    char* sp_pwdp   :encrypted password 
    other...
}
*/


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getspnam
 *function: search /etc/shadow
 *include: pwd.h
 *params: const char* name
 *return: point to spwd when succesing else return NULL.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct spwd* getspnam(const char* name);


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: setspent
 *function: back to the top of /etc/shadow
 *include: pwd.h
 *params: void
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void setspent(void); 


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getspent
 *function: get next record in /etc/shadow
 *include: shadow.h
 *params: void
 *return: pointer to spwd when successing ,else return NULL.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct spwd* getspent(void); 


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: endspent
 *function: close /etc/shadow
 *include: shadow.h
 *params: void
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void endspent(void); 

//以上系统调用需要root权限

int main(int argc, char const *argv[])
{
    /* code */
    //遍历文件
    setspent();
    struct spwd* pw = NULL;
    while(pw = getspent()){ 
        printf(" user name is %s,passwd is %s\n",pw->sp_namp , pw->sp_pwdp);
    }
    endspent();

    //根据 用户名root 查询
    if(argc ==2){
        const char* name =argv[1];
        pw =  getspnam(name);
        if(pw){
            printf("user %s ,passwd is %s\n",pw->sp_namp,pw->sp_pwdp);
        }else{
            printf("no this user name!");
        }
    }

    return 0;
}