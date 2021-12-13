#include <unistd.h>




/*+++++++++++++++++++++++++++++++++++++++
 *
 *name: sync 
 *function: flush all file buffer aera
 *include: unistd.h
 *params: void
 *return: void
 *++++++++++++++++++++++++++++++++++++++ */
void sync(void);


/*++++++++++++++++++++++++++++++++++++++++
 *
 *name: fsync
 *function: flush file buffer aera
 *include: unistd.h
 *params: 1.fd
 *return: success 0,failed -1
 *++++++++++++++++++++++++++++++++++++++ */
int fsync(int fd);




/*+++++++++++++++++++++++++++++++++++++++++++
 *
 *name: fdatasync
 *function: only flush file data to disk.
 *include: unistd.h
 *params: 1.fd
 *return: success 0 , failed -1
 * +++++++++++++++++++++++++++++++++++++++*/
int fdatasync(int fd);



