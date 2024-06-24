#include "err.h"
#include <GLFW/glfw3.h>
#include "include/pyramid-types.h"

#define generate_event(fun_name, body, ...) void\
  fun_name (pyramid_interactive_t* interactive)\
  {\
    if(interactive == NULL) return;\
    if(interactive->onevent == NULL) return;\
    pyramid_interactive_event_t event = {\
      .interactive = interactive,\
      .relX = (_mouseX - interactive->x),\
      .relY = (_mouseY - interactive->y),\
      __VA_ARGS__\
    } ;\
    body;\
    interactive->onevent(event);\
  }

static double _mouseX = 0.0;
static double _mouseY = 0.0;
static double _scrollX = 0.0;
static double _scrollY = 0.0;
static int _button = 0;
static int _key = 0;
static int _scancode = 0;
static int _action = 0;
static int _mods = 0;


extern pyramid_context_t pyramid_context;
extern void _pyramid_event_framebuffer_resize(GLFWwindow* window, int width, int height);

extern void _pyramid_interactive_cursor_move(double x, double y);
extern void _pyramid_interactives_send_event(void (*event_generator)(pyramid_interactive_t*));

generate_event(_pyramid_move_event_generator, ;,
      .type = MOVE,
      )
generate_event(_pyramid_click_event_generator, ;,
      .type = CLICK,
      .button = _button,
      .action = _action,
      .mods = _mods,
      )
generate_event(_pyramid_key_event_generator, ;,
    .type = KEY,
    .key = _key,
    .scancode = _scancode,
    .action = _action,
    .mods = _mods
    )
generate_event(_pyramid_scroll_event_generator, ;,
    .type = WHEEL,
    .scrollX = _scrollX,
    .scrollY = _scrollY,
    )


void
_pyramid_event_cursor_pos(GLFWwindow* window, double x, double y)
{
  _mouseX = pyramid_context.mouse.x = x;
  _mouseY = pyramid_context.mouse.y = y;
  //_pyramid_interactive_cursor_move(x, y);
  _pyramid_interactives_send_event(_pyramid_move_event_generator);
}

void
_pyramid_event_mouse_button(GLFWwindow* window, int button, int action, int mods)
{
  _button = button;
  _action = action;
  _mods = mods;
  _pyramid_interactives_send_event(_pyramid_click_event_generator);
}

void
_pyramid_key_event(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  _key = key;
  _scancode = scancode;
  _action = action;
  _mods = mods;
  _pyramid_interactives_send_event(_pyramid_key_event_generator);
}

void
_pyramid_scroll_event(GLFWwindow* window, double scrollX, double scrollY)
{
  _scrollX = scrollX;
  _scrollY = scrollY;
  _pyramid_interactives_send_event(_pyramid_scroll_event_generator);
}

void
_pyramid_setup_event_loop(void)
{
  glfwSetFramebufferSizeCallback(pyramid_context.window, _pyramid_event_framebuffer_resize);
  glfwSetCursorPosCallback(pyramid_context.window, _pyramid_event_cursor_pos); 
  glfwSetMouseButtonCallback(pyramid_context.window, _pyramid_event_mouse_button);
  glfwSetKeyCallback(pyramid_context.window, _pyramid_key_event);
  glfwSetScrollCallback(pyramid_context.window, _pyramid_scroll_event);
}
