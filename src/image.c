#include <stdio.h>
#include <stdlib.h>
#include "err.h"
#include <png.h>
#include <cairo/cairo.h>

cairo_surface_t *
pyramid_load_png(const char *file)
{

  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if(!png)
  {
    errtrace("Failed to create PNG struct");
    return NULL;
  }

  png_infop info = png_create_info_struct(png);
  if(!info)
  {
    errtrace("Failed to create PNG info struct");
    png_destroy_read_struct(&png, NULL, NULL);
    return NULL;
  }

  if(setjmp(png_jmpbuf(png))) {
    errtrace("Failed to set PNG jump");
    png_destroy_read_struct(&png, &info, NULL);
    return NULL;
  }

  FILE *fp = fopen(file, "rb");
  if(fp == NULL)
  {
    errtrace("Failed to open \'%s\'", file);
    png_destroy_read_struct(&png, &info, NULL);
    return NULL;
  }

  png_destroy_read_struct(&png, &info, NULL);
  return NULL;
}
