/**
 * Some error functions uses the variable-length argument list.
 *
    +----------------+-------------------------------+---------------------------+---------------+
    |    Function    |   Add string from strerror    |   Parameter to strerror   |   Terminate?  |
    +----------------+-------------------------------+---------------------------+---------------+
    |    err_ret     |               yes             |           errno           |    return;    |
    |    err_sys     |               yes             |           errno           |    exit(1);   |
    |    err_cont    |               yes             |       explict parameter   |    return;    |
    |    err_exit    |               yes             |       explict parameter   |    exit(1);   |
    |    err_dump    |               yes             |           errno           |    abort();   |
    |    err_msg     |               no              |             -             |    return;    |
    |    err_quit    |               no              |             -             |    exit(1);   |
    +----------------+-------------------------------+---------------------------+---------------+
 *
 * Created by hydrogen on 9/23/17.
 */

/*
 *  ================= Note: The difference between return, exit, abort =================
 *  return: is a key word, not a system call, it will cause function return,
 *          but not cause process termination.
 *  exit: The exit() function causes normal process termination and the value of
 *          status & 0x0377 is returned to the parent.
 *  abort: The abort() function causes abnormal process termination unless the signal
 *          SIGABRT is caught and the signal handler does not return. If the abort()
 *          function causes program termination, all open streams are closed and flushed.
 *  ====================================================================================
 */

//1. global header defined by user
#include "apue.h"

//2. user defined header file which directly related to this source code
#include "myerror.h"

//3. standard C/C++ header file
#include <errno.h>           /* for definition of errno */
#include <stdarg.h>          /* ISO C variable arguments */

//4. other user defined header file


// the scope of static function is this file
static void err_doit(int errnoflag, int error, const char* fmt, va_list ap);

/**
 * Nonfatal error related to system call.
 * Print a message and return.
 * @param fmt message
 * @param ... other arguments
 */
void
err_ret(const char* fmt, ...){
    va_list ap;

    // fmt: the last argument of which the calling function knows the type.
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}


/**
 * Fatal error related to a system call.
 * Print a message and terminate.
 * @param fmt message
 * @param ... other arguments
 */
void
err_sys(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    err_doit(1,errno, fmt, ap);
    va_end(ap);

    exit(1);
}


/**
 * Nonfatal error unrelated to a system call.
 * Error code passed by as explicit parameter.
 * Print a message and return.
 * @param error error code
 * @param fmt message
 * @param ... other arguments
 */
void
err_cont(int error, const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
}


/**
 * Fatal error unrelated to system call.
 * Error code passed as explict parameter.
 * Print a message and terminate with a specific error code.
 * @param error error code
 * @param fmt message
 * @param ... other arguments
 */
void
err_exit(int error, const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);

    exit(1);
}


/**
 * Fatal error related to a system call.
 * Print a message, dump core and terminate.
 * @param fmt message
 * @param ... other arguments
 */
void
err_dump(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);

    abort();        /* dump core and terminate */
    exit(1);        /* should't get here */
}


/**
 * Nonfatal error unrelated to a system call.
 * Print a message and return.
 * @param fmt message
 * @param ... other arguments
 */
void
err_msg(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);        /* just print a message */
    va_end(ap);
}


/**
 * Fatal error unrelated to a system call.
 * Print a message and terminate.
 * @param fmt
 * @param ...
 */
void
err_quit(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    err_doit(0, 0, fmt, ap);        /* just print a message*/
    va_end(ap);

    exit(1);
}

/**
 * Print a message and return the caller.
 * Caller specifies "errnoflag"
 *
 * @param errnoflag    adds strings from strerror?
 * @param error         error number
 * @param fmt           message
 * @param ap            variable-length arguments list
 */
static  void
err_doit(int errnoflag, int error, const char* fmt, va_list ap){
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    // print specified error, such as Permission denied
    if (errnoflag) {
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
    }

    // add \n to the end of buf string
    strcat(buf, "\n");

    fflush(stdout);         /* in case stdout and stderr are the same, flush standard output*/
    fputs(buf, stderr);
    fflush(NULL);           /* if stream = NULL, flushes all stdio output streams */
}

