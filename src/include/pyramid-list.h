#ifndef __PYRAMID_LIST_H
#define __PYRAMID_LIST_H

#include "pyramid-types.h"

extern void pyramid_initialize(pyramid_list_t *list, size_t size, size_t stride);
extern void pyramid_list_push(pyramid_list_t *list, void **val);
extern void pyramid_list_remove(pyramid_list_t *list, void **val);
extern void pyramid_list_destroy(pyramid_list_t *list);
extern void **pyramid_list_get_elem(pyramid_list_t *list, size_t index);

#endif//__PYRAMID_LIST_H
