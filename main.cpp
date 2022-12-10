#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
#include <GLES3/gl3.h>

#include "utilities.h"
#include "main_class.h"

int main () {

   Main main_c;

      // initialisation
   main_c.init ();

      // boucle principale
   main_c.boucle ();

   return 0;
}


