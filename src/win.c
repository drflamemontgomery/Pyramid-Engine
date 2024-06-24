#include <stdio.h>
#include <stdbool.h>
#include <GL/gl.h>

#include "err.h"
#include "include/pyramid-types.h"

extern pyramid_context_t pyramid_context;
PYRAMIDmainloopfun pyramid_main_loop_fun = NULL;

GLuint _pyramid_internal_texture_id = -1;

extern void _pyramid_setup_event_loop(void);
extern void _pyramid_context_resize(int width, int height);
extern void _pyramid_context_destroy(void);
extern void _pyramid_terminate_interactives(void);

void
_pyramid_event_framebuffer_resize(GLFWwindow* window, int width, int height)
{
  pyramid_context.width = width;
  pyramid_context.height = height;

  _pyramid_context_resize(width, height);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  glDeleteTextures(1, &_pyramid_internal_texture_id);
  glGenTextures(1, &_pyramid_internal_texture_id);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, _pyramid_internal_texture_id);
  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB,
      0,
      GL_RGBA,
      width,
      height,
      0,
      GL_BGRA,
      GL_UNSIGNED_BYTE,
      NULL);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

bool 
pyramid_init(int width, int height, const char *title)
{
  if(!glfwInit()) {
    errtrace("Failed to initialize GLFW");
    return false;
  }


  glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
  glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_DECORATED, GL_FALSE);

  pyramid_context.window = glfwCreateWindow(width, height, title, NULL, NULL);

  if(pyramid_context.window == NULL) {
    errtrace("Failed to create window");
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(pyramid_context.window);
  glfwSetInputMode(pyramid_context.window, GLFW_STICKY_KEYS, GL_TRUE);

  _pyramid_setup_event_loop();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_RECTANGLE_ARB);

  _pyramid_event_framebuffer_resize(pyramid_context.window, width, height);

  return true;
}

void
pyramid_terminate(void)
{
  _pyramid_terminate_interactives();
  _pyramid_context_destroy();
  if(pyramid_context.window != NULL) glfwDestroyWindow(pyramid_context.window);
  glfwTerminate();

  pyramid_context.ctx = NULL;
  pyramid_context.window = NULL;
  pyramid_context.surface = NULL;
  pyramid_context.surface_data = NULL;
}

void
pyramid_set_main_loop(PYRAMIDmainloopfun loop)
{
  pyramid_main_loop_fun = loop;
}

void
pyramid_main_loop(void)
{
  static double curTime = 0.0;
  curTime = glfwGetTime();
  do {
    if(pyramid_context.ctx != NULL) {
      cairo_set_source_rgb(pyramid_context.ctx, 0.0, 0.0, 0.0);
      cairo_rectangle(pyramid_context.ctx,
          0, 0, pyramid_context.width, pyramid_context.height);
      cairo_fill(pyramid_context.ctx);
    }
    if(pyramid_main_loop_fun != NULL) pyramid_main_loop_fun();
    if(pyramid_context.window == NULL) break;
    if(pyramid_context.ctx == NULL) goto renderEnd;


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, _pyramid_internal_texture_id);
    glTexImage2D(GL_TEXTURE_RECTANGLE_ARB,
        0,
        GL_RGBA,
        pyramid_context.width,
        pyramid_context.height,
        0,
        GL_BGRA,
        GL_UNSIGNED_BYTE,
        pyramid_context.surface_data);

    glColor3f (0.0f, 0.0f, 0.0f);
    glBegin (GL_QUADS);

    glTexCoord2f (0.0f, (GLfloat) pyramid_context.height);
    glVertex2f (0.0f, 0.0f);
    
    glTexCoord2f ((GLfloat) pyramid_context.width, (GLfloat) pyramid_context.height);
    glVertex2f (1.0f, 0.0f);
    
    glTexCoord2f ((GLfloat) pyramid_context.width, 0.0f);
    glVertex2f (1.0f, 1.0f);
    
    glTexCoord2f (0.0f, 0.0f);
    glVertex2f (0.0f, 1.0f);
    glEnd ();

    glPopMatrix ();

renderEnd:
    glfwSwapBuffers(pyramid_context.window);
    glfwPollEvents();

    double time = glfwGetTime();
    pyramid_context.deltaTime = time - curTime;
    curTime = time;
  } while(glfwWindowShouldClose(pyramid_context.window) == 0);
}
