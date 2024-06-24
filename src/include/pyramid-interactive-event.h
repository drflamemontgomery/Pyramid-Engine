#ifndef __PYRAMID_INTERACTIVE_EVENT_H
#define __PYRAMID_INTERACTIVE_EVENT_H

enum pyramid_interactive_event_type {
  CHECK,
  CLICK,
  FOCUS,
  FOCUS_LEFT,
  KEY,
  MOVE,
  OUT,
  OVER,
  RELEASE,
  RELEASE_OUTSIDE,
  WHEEL,
};

struct pyramid_interactive_struct;

struct pyramid_interactive_event_struct {
  enum pyramid_interactive_event_type type;
  struct pyramid_interactive_struct *interactive;

  double relX;
  double relY;

  union {
    struct {
      union {
        int button;
        struct {
          int key;
          int scancode;
        };
      };
      int action;
      int mods;
    };
    
    struct {
      double scrollX;
      double scrollY;
    };
  };
};

typedef struct pyramid_interactive_event_struct pyramid_interactive_event_t;

#endif//__PYRAMID_INTERACTIVE_EVENT_H
