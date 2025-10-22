#ifndef SCREEN_H
#define SCREEN_H

namespace system_utils 
{

class screen 
{
public:
  screen ();

  int get_width () const;

  int get_height () const;

  ~screen ();

private:
  int width;
  int height;
};

}

#endif