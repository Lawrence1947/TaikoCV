#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "kernel/include/timer.h"

namespace game
{

class taiko;

class main_loop
{
public:
  main_loop (taiko &taiko_game_);

  int run ();

  ~main_loop ();
  
private:
  // internal loop data
  bool is_running;
  kernel::timer timer;

  // game
  taiko &taiko_game;
};

}

#endif