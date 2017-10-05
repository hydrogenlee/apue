//
// Created by hydrogen on 9/29/17.
//

#ifndef APUE_MYLOG_H
#define APUE_MYLOG_H


int log_to_stderr = 0;      /* must redefined this variable*/

/* ============= function proto ============== */
// Note: __attribute__((noreturn))                                              //
// This attribute tells the compiler that the function won't ever return,       //
// and this can be used to suppress errors about code paths not being reached.  //

/* -------------- log_ method ---------------- */

void    log_msg(const char*, ...);
void    log_open(const char*, int, int);
void    log_quit(const char*, ...) __attribute__((noreturn));
void    log_ret(const char*, ...);
void    log_sys(const char*, ...) __attribute__((noreturn));
void    log_exit(int, const char*, ...) __attribute__((noreturn));

/* ========= function proto end ============ */

#endif //APUE_MYLOG_H
