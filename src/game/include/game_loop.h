

namespace game
{

class main_loop
{
public:
  main_loop ();

  int run ();

  ~main_loop ();
  
private:
  int screen_width;
  int screen_height;
};

}