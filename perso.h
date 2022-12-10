#ifndef PERSO_CLASS_H
 #define PERSO_CLASS_H

 #include <SDL2/SDL.h>
 #include <GLES3/gl3.h>

class Perso {

  public:

   Perso ();
   ~Perso ();

  private:

   Camera m_camera;

   float V_z; // vitesse de chutte
   unsigned long int m_ticks_last_jump;
};

#endif
