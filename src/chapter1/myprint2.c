/**
 * Reading from standard input and writing to standard output.
 * Using getc and putc function defined in <stdio.h>
 * 
 * Section 1.5 on page 10 (English 3rd edition)
 *
 * Created by hydrogen on 10/5/17.
 * Operating System: Centos 7 x86_64
 * IDE: CLion 2017.2
 */

#include "apue.h"
#include "myerror.h"

int
main(void){
    // remember this, because EOF == -1, so <char c> is uncorrected.
    int c;

    while ((c = getc(stdin)) != EOF){
        if(putc(c, stdout) == EOF){
            err_sys("output error");
        }
    }

    if(ferror(stdin)){          /* ferror() is declared in <stdio.h> */
        err_sys("input error");
    }

    exit(0);
}
