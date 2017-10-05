//
// Created by hydrogen on 9/23/17.
//

#ifndef APUE_MYERROR_H
#define APUE_MYERROR_H


/* ============= function proto ============== */
// Note: __attribute__((noreturn))                                              //
// This attribute tells the compiler that the function won't ever return,       //
// and this can be used to suppress errors about code paths not being reached.  //

/* -------------- err_ method ---------------- */

void    err_msg(const char*, ...);
void    err_dump(const char*, ...) __attribute__((noreturn));
void    err_quit(const char*, ...) __attribute__((noreturn));
void    err_cont(int, const char*, ...);
void    err_exit(int, const char*, ...) __attribute__((noreturn));
void    err_ret(const char*, ...);
void    err_sys(const char*, ...) __attribute__((noreturn));

/* ========== function proto end ============ */

#endif //APUE_MYERROR_H
