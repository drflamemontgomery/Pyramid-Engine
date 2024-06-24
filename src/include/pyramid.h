#ifndef __PYRAMID_H
#define __PYRAMID_H

#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "pyramid-types.h"
#include "pyramid-interactive.h"
#include "pyramid-list.h"

extern pyramid_context_t pyramid_context;


extern bool pyramid_init(int width, int height, const char *title);
extern void pyramid_terminate(void);
extern void pyramid_set_main_loop(PYRAMIDmainloopfun loop);
extern void pyramid_main_loop(void);

#endif//__PYRAMID_H
