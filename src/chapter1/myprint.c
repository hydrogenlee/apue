/**
 * Reading from standard input and writing to standard output.
 * Using read and write function defined in <unistd.h>
 *
 * Section 1.5 on page 9 (English 3rd edition)
 *
 * Created by hydrogen on 10/5/17.
 * Operating System: Centos 7 x86_64
 * IDE: CLion 2017.2
 */

#include "apue.h"
#include "myerror.h"

int
main(void){
    ssize_t n;      /* ssize_t = long  size_t = unsigned long */
    char buf[BUFFSIZE];

    // read and write function prototypes defined in <unistd.h>
    while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n){
            err_sys("write error");
        }
    }

    if(n < 0){
        err_sys("read error");
    }

    exit(0);
}