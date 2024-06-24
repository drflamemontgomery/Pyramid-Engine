#include <stdlib.h>
#include <unistd.h>
#include <cairo/cairo.h>
#include <sys/signal.h>
#include "../../src/include/pyramid.h"
#include "err.h"
#include "fun.h"

void
sigint_handler(int sig)
{
  glfwSetWindowShouldClose(pyramid_context.window, GLFW_TRUE);
}

static void
test_interactive_onevent(pyramid_interactive_event_t event)
{
  switch(event.type)
  {
    case MOVE:
      trace("#(MouseMove [%.2f %.2f])", event.relX, event.relY);
      break;
    case CLICK:
      trace("#(MouseClick [%.2f %.2f] button=>%d action=>%d mods=>%d)", event.relX, event.relY, event.key, event.action, event.mods);
      break;
    case CHECK:
      trace("#(MouseCheck [%.2f %.2f])", event.relX, event.relY);
      break;
    case FOCUS:
      trace("#(Focus [%.2f %.2f])", event.relX, event.relY);
      break;
    case FOCUS_LEFT:
      trace("#(FocusLeft [%.2f %.2f])", event.relX, event.relY);
      break;
    case KEY:
      trace("#(Key [%.2f %.2f]) key=>%d scancode=>%d action=>%d mods=>%d", event.relX, event.relY, event.key, event.scancode, event.action, event.mods);
      break;
    case WHEEL:
      trace("#(MouseWheel [%.2f %.2f] scrollX=>%.2f scrollY=>%.2f)", event.relX, event.relY, event.scrollX, event.scrollY);
      break;


    default:
      trace("#(Event %d)", event.type);
      break;
  }
}

static pyramid_interactive_t test_interactive = {
 .x = 20,
 .y = 20,
 .width = 320,
 .height = 320, 

 .onevent = test_interactive_onevent,
};

void
main_loop()
{
  cairo_set_source_rgb(pyramid_context.ctx, 1.0, 1.0, 1.0);
  cairo_rectangle(pyramid_context.ctx,
      test_interactive.x,
      test_interactive.y,
      test_interactive.width,
      test_interactive.height);
  cairo_fill(pyramid_context.ctx);

  cairo_set_source_rgb(pyramid_context.ctx, 1.0, 0.0, 0.0);
  cairo_rectangle(pyramid_context.ctx,
      pyramid_context.mouse.x-5,
      pyramid_context.mouse.y-5,
      10,
      10);
  cairo_fill(pyramid_context.ctx);

  scene_main_loop(&pyramid_context);
}


int
main(int argc, char *argv[])
{
  signal(SIGINT, sigint_handler);
  if(!pyramid_init(640, 640, "Pyramid Testbed")) {
    errtrace("Failed to initialize Pyramid");
    return 1;
  }
  trace("Initialized Pyramid");

  pyramid_add_interactive(&test_interactive);
  pyramid_set_main_loop(main_loop);
  pyramid_main_loop();
  pyramid_terminate();
  return 0;
}
