#ifndef ERR_H
#define ERR_H

#include <stdio.h>

#ifndef RELEASE

#define stringize(s) __stringize(s)
#define __stringize(s) #s
#define errtrace(msg, ...) fprintf(stderr, "[ERROR " __FILE__ ":" stringize(__LINE__) "] " msg "\n" __VA_OPT__(,) __VA_ARGS__ )
#define trace(msg, ...) fprintf(stdout, "[" __FILE__ ":" stringize(__LINE__) "] " msg "\n" __VA_OPT__(,)  __VA_ARGS__)

#else

#define errtrace(msg, ...) ;
#define trace(msg, ...) ;

#endif

#endif//ERR_H
