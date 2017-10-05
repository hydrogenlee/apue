/**
 * Print process ID.
 * 
 * Section 1.6 on page 11 (English 3rd edition)
 *
 * Created by hydrogen on 10/5/17.
 * Operating System: Centos 7 x86_64
 * IDE: CLion 2017.2
 */

#include "apue.h"

int
main(void){

    // getpid() is declared in <unistd.h>
    printf("The process ID of this program is %ld.\n", (long)getpid());

    exit(0);
}