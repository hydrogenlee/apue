/**
 * Some log functions uses the variable-length argument list.
 *
    +----------------+-------------------------------+---------------------------+---------------+
    |    Function    |   Add string from strerror    |   Parameter to strerror   |   Terminate?  |
    +----------------+-------------------------------+---------------------------+---------------+
    |    log_ret     |               yes             |           errno           |    return;    |
    |    log_sys     |               yes             |           errno           |    exit(2);   |
    |    log_exit    |               yes             |       explict parameter   |    exit(2);   |
    |    log_msg     |               no              |             -             |    return;    |
    |    log_quit    |               no              |             -             |    exit(2);   |
    +----------------+-------------------------------+---------------------------+---------------+
 *
 * Created by hydrogen on 9/29/17.
 */

//1. global header defined by user
#include "apue.h"

//2. user defined header file which directly related to this source code
#include "mylog.h"

//3. standard C/C++ header file
#include <errno.h>           /* for definition of errno */
#include <stdarg.h>          /* ISO C variable arguments */
#include <syslog.h>          /* for openlog(),closelog() */

//4. other user defined header file


static void log_doit(int errnoflag, int error, int priority, const char* fmt, va_list ap);

/*
 * Caller must define and set this variable.
 * nonzero if interactive, zero if daemon.
 */
extern int log_to_stderr;

/**
 * Initialize syslog(), if running as daemon.
 * @param ident The string pointed to by ident is prepended to every message,
 *               and is typically set to the program name.  If ident is NULL, the program name is used.
 * @param option specify flags which control the operation of openlog() and subsequent calls to syslog().
 * @param facility specify what type of program is logging the message.
 */
void
log_open(const char* ident, int option, int facility){
    if(log_to_stderr == 0){
        openlog(ident, option, facility);
    }
}


/**
 * Nonfatal error related to a system call.
 * Print a message with the system's errno value and return.
 * @param fmt message
 * @param ... other arguments
 */
void
log_ret(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
}


/**
 * Fatal error related to system call.
 * Print a message and terminate.
 * @param fmt message
 * @param ... other arguments
 */
void log_sys(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);

    exit(2);
}

/**
 * Nonfatal error unrelated to system call.
 * Print a message and return.
 * @param fmt message
 * @param ... other arguments
 */
void
log_msg(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, errno, LOG_ERR, fmt, ap);
    va_end(ap);
}


/**
 * Nonfatal error related to system call.
 * Print a message and terminate.
 * @param fmt message
 * @param ... other arguments
 */
void
log_quit(const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, errno, LOG_ERR, fmt, ap);
    va_end(ap);

    exit(2);
}


/**
 * Fatal error related to a system call.
 * Error number pass as an explicit parameter.
 * Print a message and terminate.
 * @param error error code
 * @param fmt message
 * @param ... other arguments
 */
void
log_exit(int error, const char* fmt, ...){
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, error, LOG_ERR, fmt, ap);
    va_end(ap);

    exit(2);
}

/**
 * Print a message and return to caller.
 * Caller specifies "errnoflag" and "priority".
 * @param errnoflag adds strings from strerror?
 * @param error     error number
 * @param priority  log priority
 * @param fmt       message
 * @param ap        variable arguments list
 */
static void
log_doit(int errnoflag, int error, int priority, const char* fmt, va_list ap){
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE-1, fmt, ap);
    if(errnoflag){
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
    }

    //set the last character to "\n"
    strcat(buf, "\n");

    if(log_to_stderr){
        fflush(stdout);            /* in case stdout and stderr are the same */
        fputs(buf, stderr);
        fflush(stderr);
    }else{
        //if log_to_stderr sets to 0,  not put logs to stderr
        syslog(priority, ": %s", buf);
    }
}


