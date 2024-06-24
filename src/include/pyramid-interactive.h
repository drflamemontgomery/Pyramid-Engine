#ifndef __PYRAMID_INTERACTIVE_H
#define __PYRAMID_INTERACTIVE_H

#include "pyramid-types.h"

extern void pyramid_focus_interactive(pyramid_interactive_t *interactive);
extern void pyramid_unfocus_interactive(pyramid_interactive_t *interactive);
extern void pyramid_add_interactive(pyramid_interactive_t *interactive);
extern void pyramid_remove_interactive(pyramid_interactive_t *interactive);

#endif//__PYRAMID_INTERACTIVE_H
