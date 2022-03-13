#include <unistd.h>
#include <stdio.h>
#include <grp.h>


/*
struct group
{
    char* gr_name   :group name
    char* gr_passwd :group encryptied password
    int gr_gid  :group id
    char* gr_men[]  :group member user name
}

//file : /etc/group


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getgrgid
 *function: get passwd bu uid
 *include: group.h
 *params: 1. gid
 *return: pointer to group when successing ,else return NULL
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct group* getgrgid(gid_t gid);


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getgrnam
 *function: get struct group bu group name
 *include: group.h
 *params: 1. group name
 *return: pointer to group when successing ,else return NULL
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct group* getgrnam(const char* name);



/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: setgrent
 *function: back to the top of /etc/group.
 *include: group.h
 *params: void
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void setgrent(void); 


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: getpwent
 *function: get next record in /etc/group
 *include: group.h
 *params: void
 *return: pointer to group when successing ,else return NULL.
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern struct group* getgrent(void); 


/*++++++++++++++++++++++++++++++++++++++++++++++
 *name: endgrent
 *function: close /etc/group.
 *include: group.h
 *params: void
 *return: void
 *+++++++++++++++++++++++++++++++++++++++++++++ */
extern void endgrent(void); 

int main(int argc, char const *argv[])
{
    /* code */
    //遍历文件
    setgrent();
    struct group* pw = NULL;
    while(pw = getgrent()){
        printf("gid is %d , group name is %s\n",pw->gr_gid, pw->gr_name);
        char** men = pw->gr_mem;
        char* str;
        while(str = *men){
            printf("member %s\n",*men);
            ++men;
        }
    }
    endgrent();

    //根据 用户名root 查询
    if(argc ==2){
        const char* name =argv[1];
        pw =  getgrnam(name);
        if(pw){
            printf("group %s ,gid is %d\n",pw->gr_name,pw->gr_gid);
        }else{
            printf("no this group name!");
        }
    }

    return 0;
}
