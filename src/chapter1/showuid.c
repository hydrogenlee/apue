/**
 * This program prints the user ID and group ID.
 * 
 * Section 1.8 on page 17 (English 3rd edition)
 *
 * Created by hydrogen on 10/5/17.
 * Operating System: Centos 7 x86_64
 * IDE: CLion 2017.2
 */

#include "apue.h"

int
main(void){
    printf("uid = %d, gid = %d", getuid(), getgid());
    exit(0);
}
