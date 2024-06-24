#include <stdio.h>
#include <stdlib.h>
#include "include/pyramid-types.h"

pyramid_context_t pyramid_context = {
  .window = NULL,
  .ctx = NULL,
  .surface = NULL,
  .surface_data = NULL,
  .width = 640,
  .height = 640,
  .deltaTime = 1.0/60.0,
};

void
_pyramid_context_resize(int width, int height)
{
  if(pyramid_context.ctx != NULL) cairo_destroy(pyramid_context.ctx);
  if(pyramid_context.surface != NULL) free(pyramid_context.surface);
  if(pyramid_context.surface_data != NULL) free(pyramid_context.surface_data);

  pyramid_context.surface_data = calloc(4 * width * height, sizeof(unsigned char));
  pyramid_context.surface = cairo_image_surface_create_for_data(
      pyramid_context.surface_data,
      CAIRO_FORMAT_ARGB32, 
      width, height,
      4 * width);
  pyramid_context.ctx = cairo_create(pyramid_context.surface);
}

void
_pyramid_context_destroy(void)
{
  if(pyramid_context.ctx != NULL) cairo_destroy(pyramid_context.ctx);
  if(pyramid_context.surface != NULL) free(pyramid_context.surface);
}
