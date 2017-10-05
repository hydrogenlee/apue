/**
 * Reading commands from standard input and executing the commands.
 * Using fork(), exec() and waitpid().
 *
 * Section 1.6 on page 12 (English 3rd edition)
 *
 * Created by hydrogen on 10/5/17.
 * Operating System: Centos 7 x86_64
 * IDE: CLion 2017.2
 */

#include "apue.h"
#include "myerror.h"

#include <sys/wait.h>   /* for waitpid() */

int
main(void){

    char buf[MAXLINE];  /* from "apue.h" */
    pid_t pid;
    int status;

    printf("%% ");  /* print prompt %*/

    // type the end-of-file character(usually ctrl + D) to terminate the process
    while (fgets(buf, MAXLINE, stdin) != NULL){
        // replace "\n" with null
        // because the function execlp() wants a null-terminated argument,
        // not newline-terminated argument
        if(buf[strlen(buf) - 1] == '\n'){
            buf[strlen(buf) - 1] = '\0';
        }

        if((pid = fork()) < 0){
            err_sys("fork error");
        }else if(pid == 0){     /* child process */
            execlp(buf, buf, (char *)0);
            err_ret("couldn't execute: %s", buf);
            exit(127);
        }

        // parent process
        if(waitpid(pid, &status, 0) < 0){
            err_sys("waitpid error");
        }

        printf("%% ");
    }

    exit(0);
}


