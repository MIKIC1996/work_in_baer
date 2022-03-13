#include <unistd.h>
#include <stdio.h>
#include <pwd.h>

/*
struct passwd
{
    char* pw_name   :username
    char* pw_passwd     :password
    uid_t pw_uid    :user id
    gid_t pw_gid    :user group id
    char* pw_gecos  :注释字段
    char* pw_dir    :initialized working directory
    char* pw_shell  :initialized shell program
}

example: root : x : 0 : 0 : super user : /root : /bin/bash
*/



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getpwuid
 *function: get passwd bu uid
 *include: pwd.h
 *params: 1. uid
 *return: pointer to passwd when successing ,else return NULL
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct passwd* getpwuid(uid_t uid);


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getpwnam
 *function: get passwd bu user name
 *include: pwd.h
 *params: 1. user name
 *return: pointer to passwd when successing ,else return NULL
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct passwd* getpwnam(const char* name);



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: setpwent
 *function: back to the top of /etc/passwd.
 *include: pwd.h
 *params: void
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void setpwent(void); 


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getpwent
 *function: get next record in /etc/passwd
 *include: pwd.h
 *params: void
 *return: pointer to passwd when successing ,else return NULL.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct passwd* getpwent(void); 


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: endpwent
 *function: close /etc/passwd.
 *include: pwd.h
 *params: void
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void endpwent(void); 

int main(int argc, char const *argv[])
{
    /* code */
    //遍历文件
    setpwent();
    struct passwd* pw = NULL;
    while(pw = getpwent()){
        printf("uid is %d , user name is %s\n",pw->pw_uid , pw->pw_name);
    }
    endpwent();

    //根据 用户名root 查询
    if(argc ==2){
        const char* name =argv[1];
        pw =  getpwnam(name);
        if(pw){
            printf("user %s ,uid is %d\n",pw->pw_name,pw->pw_uid);
        }else{
            printf("no this user name!");
        }
    }

    return 0;
}
















