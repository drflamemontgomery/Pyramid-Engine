#ifndef __SCENE_H
#define __SCENE_H

#include "../../src/include/pyramid.h"

typedef struct {
  void (*init)(void);
  void (*main_loop)(pyramid_context_t*);
  void (*deinit)(void);
} scene_t;

#endif//__SCENE_H
