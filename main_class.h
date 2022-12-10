#ifndef MAIN_CLASS_H
 #define MAIN_CLASS_H

 #define G 9.81

 #include <SDL2/SDL.h>
 #include <GLES3/gl3.h>

 #include "Input.h"
 #include "camera.h"
 #include "mur.h"
 #include "labyrinthe.h"

class Main {

  public:

   Main ();
   ~Main ();

   void init ();
   void boucle ();
   void do_events (std::array <bool, 2500> colision_grid);
   void go_on (const std::array <bool, 2500> colision_grid);
   void go_back (const std::array <bool, 2500> colision_grid);
   void go_left (const std::array <bool, 2500> colision_grid);
   void go_right (const std::array <bool, 2500> colision_grid);
   void accroupir ();
   void jump ();
   bool tomber ();

  private:

   SDL_Window* m_window;
   SDL_GLContext m_contexteOpenGL;
   Input m_input;
   Camera m_camera;

   int m_weight, m_height;

   float V_z; // vitesse de chutte
   unsigned long int m_ticks_last_jump;
};

#endif
