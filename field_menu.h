#ifndef CHAMP_MENU_H
 #define CHAMP_MENU_H

 #define DEFAULT_HEIGHT 125
 #define DEFAULT_WHEIGHT 500

 #include <string>
 #include <vector>
 #include <array>
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_ttf.h>

class Field {

  public:

   Field ();
   Field (SDL_Rect pos, unsigned short int type, unsigned short int wheight, unsigned short int height);
   Field (SDL_Rect pos, unsigned short int type, unsigned short int wheight, unsigned short int height, std::string message);
   Field (SDL_Rect pos, unsigned short int type, unsigned short int wheight, unsigned short int height, std::string message, SDL_Renderer* renderer);
   ~Field ();
   void load (SDL_Renderer* renderer, TTF_Font* font, SDL_Color C);
   SDL_Texture* get_texture () const;
   SDL_Rect get_rect () const;

  private:

   unsigned int m_wheight, m_height; // weight
   unsigned short int m_type;

   std::string m_message; // message written

   SDL_Texture* m_field; // img of field
   SDL_Rect m_pos; // pos on the menu

   bool m_bool_option;
/*
   int m_int_option;
   /vector
   /string
   /list
*/
};

#endif
