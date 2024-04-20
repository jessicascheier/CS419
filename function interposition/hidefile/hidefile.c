#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>

// Name: Jessica Scheier
// netID: jls772
// RUID: 209002385
// your code for readdir goes here

typedef struct dirent *(*original_readdir_t)(DIR *);

struct dirent *readdir(DIR *dirp) {
    original_readdir_t original_readdir = (original_readdir_t)dlsym(RTLD_NEXT, "readdir");
    const char *hidden = getenv("HIDDEN");
    while (1) {
        struct dirent *entry = original_readdir(dirp);
        if (entry == NULL) {
            return NULL;
        }
        if (hidden != NULL && strcmp(entry->d_name, hidden) == 0) {
            continue;
        }
        return entry;
    }
}

// export LD_PRELOAD=$PWD/hidefile.so
