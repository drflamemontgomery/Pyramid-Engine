#include <stdlib.h>
#include <stdbool.h>
#include "err.h"
#include "include/pyramid-types.h"
#include "include/pyramid-list.h"

extern pyramid_context_t pyramid_context;
pyramid_interactive_t *pyramid_focused_interactive = NULL;
pyramid_list_t pyramid_interactives = {
  .len = -1,
  .max_len = 0,
  .stride = sizeof(pyramid_interactive_t*),
  .values = NULL,
};

void
pyramid_add_interactive(pyramid_interactive_t *interactive)
{
  pyramid_list_push(&pyramid_interactives, (void**)&interactive);
}

void
pyramid_remove_interactive(pyramid_interactive_t *interactive)
{
  pyramid_list_remove(&pyramid_interactives, (void**)&interactive);
  if(pyramid_focused_interactive != interactive) return;
  pyramid_focused_interactive = NULL;
}

void
pyramid_focus_interactive(pyramid_interactive_t *interactive)
{
  pyramid_focused_interactive = interactive;
}

void
pyramid_unfocus_interactive(pyramid_interactive_t *interactive)
{
  pyramid_focused_interactive = NULL;
}

void
_pyramid_terminate_interactives()
{
  pyramid_list_destroy(&pyramid_interactives);
}

static bool
_intersects(pyramid_interactive_t *interactive, double x, double y)
{

  if(x < interactive->x) return false;
  if(y < interactive->y) return false;
  if(x > interactive->x + interactive->width) return false;
  if(y > interactive->y + interactive->height) return false;
  return true;
}

void
_pyramid_interactive_cursor_move(double x, double y)
{
  bool focused_interactive_updated = false;
  for(int i = 0; i <= (int)pyramid_interactives.len; i++)
  {
    pyramid_interactive_t *t = *((pyramid_interactive_t**)pyramid_list_get_elem(&pyramid_interactives, i));
    if(!_intersects(t, x, y)) continue;
    if(!focused_interactive_updated && t == pyramid_focused_interactive)
      focused_interactive_updated = true;
    if(t->onevent == NULL) continue;
    pyramid_interactive_event_t move_event = {
      .type = MOVE,
      .relX = (x - t->x),
      .relY = (y - t->y),
    };
    t->onevent(move_event);
  }

  if(focused_interactive_updated) return;
  if(pyramid_focused_interactive->onevent == NULL) return;
  pyramid_interactive_event_t move_event = {
    .type = MOVE,
    .relX = (x - pyramid_focused_interactive->x),
    .relY = (y - pyramid_focused_interactive->y),
  };
  pyramid_focused_interactive->onevent(move_event);
}

void
_pyramid_interactives_send_event(void (*event_generator)(pyramid_interactive_t*))
{
  bool focused_interactive_updated = false;
  for(int i = 0; i <= (int)pyramid_interactives.len; i++)
  {
    pyramid_interactive_t *t = *((pyramid_interactive_t**)pyramid_list_get_elem(&pyramid_interactives, i));
    if(t == NULL) continue;
    if(!_intersects(t, pyramid_context.mouse.x, pyramid_context.mouse.y)) continue;

    event_generator(t);
    if(!focused_interactive_updated && t == pyramid_focused_interactive)
      focused_interactive_updated = true;
  }

  if(pyramid_focused_interactive == NULL) return;
  if(focused_interactive_updated) return;
  event_generator(pyramid_focused_interactive);
}
