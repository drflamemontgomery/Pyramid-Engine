#include <stdlib.h>
#include <memory.h>
#include "err.h"
#include "include/pyramid-types.h"

void
pyramid_initialize(pyramid_list_t *list, size_t size, size_t stride)
{
  list->len = -1;
  list->max_len = size;
  list->stride = stride;

  list->values = calloc(size, stride);
}

void
pyramid_list_push(pyramid_list_t *list, void **val)
{
  pyramid_interactives.len += 1;
  if(list->len >= list->max_len)
  {
    if(list->values == NULL)
      list->max_len = 32;
    else
      list->max_len += 32;

    list->values = realloc(list->values, list->max_len*list->stride);
  }

  memcpy(list->values + list->len*list->stride, val, list->stride);
}

void
pyramid_list_remove(pyramid_list_t *list, void **val)
{
  if(list->len == -1) return;
  size_t i;
  for(i = 0; i <= list->len; i++)
  {
    if(memcmp(list->values + i*list->stride, *val, list->stride)) break;
  }
  
  if(i > list->len) {
    return;
  }
  size_t size = list->len - i;

  void *ptr = malloc(size*list->stride);
  memcpy(ptr, list->values + (i+1)*list->stride, size*list->stride);
  memcpy(list->values + i*list->stride, ptr, size*list->stride);
  list->len -= 1;
}

void
pyramid_list_destroy(pyramid_list_t *list)
{
  list->len = -1;
  list->max_len = 0;
  list->stride = 0;
  if(list->values == NULL) return;
  free(list->values);
  list->values  = NULL;
}

void **
pyramid_list_get_elem(pyramid_list_t *list, size_t index)
{
  if(index > list->len) return NULL;
  else return (list->values + index*list->stride);
}
