#ifndef MENU_H
 #define MENU_H

 #include <vector>
 #include <array>
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_ttf.h>

 #include "field_menu.h"

class Menu {

  public:

   Menu ();
   ~Menu ();
   void add_field (Field field_added);
   SDL_Texture* get_result () const;

  private:

   size_t m_nb_field; // nbr of fields
   std::vector <Field> m_fields; // fields

   SDL_Texture* m_result; // final menu
};

#endif
