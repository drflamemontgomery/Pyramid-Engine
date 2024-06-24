#ifndef __PYRAMID_TYPES_H
#define __PYRAMID_TYPES_H

#include <cairo/cairo.h>
#include <GLFW/glfw3.h>

#include "pyramid-interactive-event.h"

typedef void (* PYRAMIDmainloopfun)(void);
typedef int PYRAMIDmousebutton;

typedef struct {
  int width;
  int height;

  GLFWwindow *window;
  cairo_t *ctx;
  cairo_surface_t *surface;
  unsigned char *surface_data;

  double deltaTime;

  struct {
    double x;
    double y;
  } mouse;
} pyramid_context_t;


typedef struct {
  float x;
  float y;
  float width;
  float height;

  void (*onevent)(struct pyramid_interactive_event_struct);
} pyramid_interactive_t;

typedef struct {
  size_t max_len;
  size_t len;
  size_t stride;

  void *values;
} pyramid_list_t;

extern pyramid_interactive_t *pyramid_focused_interactive;
extern pyramid_list_t pyramid_interactives;

#endif//__PYRAMID_TYPES_H
