

namespace game
{

class main_loop
{
public:
  main_loop ();

  int run ();

  ~main_loop ();
  
private:
  // system info  
  int screen_width;
  int screen_height;

  // internal loop data
  bool is_running;
};

}