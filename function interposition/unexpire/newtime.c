#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dlfcn.h>

// Name: Jessica Scheier
// netID: jls772
// RUID: 209002385
// your code for time() goes here

typedef time_t (*original_time_t)(time_t *);

time_t time(time_t *tloc) {
    
    static int first_call = 1;
    if (first_call==1) {
        if (tloc != NULL) {
            first_call = 0;
            // return 1640995200;
            struct tm custom_time;
            strptime("2022-01-02 00:00:00", "%Y-%m-%d %H:%M:%S", &custom_time);
            // printf("%ld\n", (long)mktime(&custom_time)); 
            *tloc = mktime(&custom_time);
            return mktime(&custom_time);
        }
    }

    if (tloc != NULL) {
        original_time_t original_time = (original_time_t)dlsym(RTLD_NEXT, "time");
        // printf("%ld\n", (long)original_time(tloc));
        return original_time(tloc);
    }
    
    return -1;
}
