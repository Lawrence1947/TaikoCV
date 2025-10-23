#include "screen.h"

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

#include <stdio.h>

namespace system_utils
{

screen::screen ()
{
  Display *display = XOpenDisplay (nullptr);

  Window root = DefaultRootWindow (display);

  int count = 0;
  XRRMonitorInfo *monitors = XRRGetMonitors (display, root, True, &count);
  if (!monitors || count == 0) 
    {
      XCloseDisplay(display);
      return;
    }

  XRRMonitorInfo *primary = nullptr;
  for (int i = 0; i < count; ++i) 
    {
      if (monitors[i].primary) 
        {
          primary = &monitors[i];
          break;
        }
    }
    
  if (!primary) 
    {
      primary = &monitors[0];
    }
  
  width = primary->width;
  height = primary->height;

  XRRFreeMonitors (monitors);
  XCloseDisplay (display);
}

int screen::get_width () const { return width; }

int screen::get_height () const { return height; }

screen::~screen () {}

}