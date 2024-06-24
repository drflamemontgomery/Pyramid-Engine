#include "scene.h"

scene_t *cur_scene;

void
scene_swap(scene_t *scene)
{
  if(cur_scene != NULL) 
    if(cur_scene->deinit != NULL)
      cur_scene->deinit();
  scene->init();
  cur_scene = scene;
}

void
scene_main_loop(pyramid_context_t *context)
{
  if(cur_scene == NULL) return;
  if(cur_scene->main_loop == NULL) return;
  cur_scene->main_loop(context);
}
