/**
 *  This program shows the use of two error function:
 *  strerror() and perror()
 * 
 * Section 1.7 on page 15 (English 3rd edition)
 *
 * Created by hydrogen on 10/5/17.
 * Operating System: Centos 7 x86_64
 * IDE: CLion 2017.2
 */

#include "apue.h"

#include <errno.h>

int
main(int argc, char** argv){
    fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
    errno = ENOENT;
    perror(argv[0]);
    exit(0);
}
