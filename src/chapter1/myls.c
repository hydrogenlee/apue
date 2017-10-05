/**
 * Listing the names of all the files in a directory.
 *
 * Section 1.4 on page 5 (English 3rd edition)
 *
 * Created by hydrogen on 10/3/17.
 * Operating System: Centos 7 x86_64
 * IDE: CLion 2017.2
 */

#include "apue.h"       /* in lib directory */
#include "myerror.h"    /* in lib directory */

#include <dirent.h>     /* for DIR and dirent */


int
main(int argc, char** argv){

    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        err_quit("Usage: %s <directory_name>", argv[0]);
    }

    // open directory
    if ((dp = opendir(argv[1])) == NULL) {
        err_sys("can't open file %s", argv[1]);
    }

    // read directory
    while ((dirp = readdir(dp)) != NULL) {
        printf("%s\n", dirp->d_name);
    }

    //close directory
    closedir(dp);

    exit(0);
}
