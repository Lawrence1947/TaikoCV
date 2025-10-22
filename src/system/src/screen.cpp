#include "screen.h"

#include <X11/Xlib.h>

namespace system_utils
{

screen::screen ()
{
  Display *display = XOpenDisplay (nullptr);
  Screen *screen = DefaultScreenOfDisplay (display);
  
  width = screen->width;
  height = screen->height;
}

int screen::get_width () const { return width; }

int screen::get_height () const { return height; }

screen::~screen () {}

}