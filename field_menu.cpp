
#ifndef CPP
 #define CPP
#endif

#include "include/miscellaneous/malo.h"

#include "field_menu.h"

Field::Field () : m_wheight {0}, m_height {0}, m_type {0}, m_message {""}, m_field {NULL} {

}

Field::Field (SDL_Rect pos, unsigned short int type, unsigned short int wheight, unsigned short int height) : m_wheight {wheight}, m_height {height}, m_type {type}, m_message {""} {
   
}

Field::Field (SDL_Rect pos, unsigned short int type, unsigned short int wheight, unsigned short int height, std::string message) : m_wheight {wheight}, m_height {height}, m_type {type}, m_message {message} {
   
}

Field::Field (SDL_Rect pos, unsigned short int type, unsigned short int wheight, unsigned short int height, std::string message, SDL_Renderer* renderer) : m_pos {pos},
                                                                                                    m_type {type}, m_message {message} {

   m_field = SDL_CreateTexture (renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, pos.w, pos.h);
}


Field::~Field () {
   
}


void Field::load (SDL_Renderer* renderer, TTF_Font* font, SDL_Color C) {

      /* write text on texture "text" */
   SDL_Texture* text {NULL};
   ttf_print_B_cpp (m_message.c_str (), &text, renderer, font, C); // write m_message on m_field

      /* get weight of text */
   Uint32 format;
   int access = 0;
   int weight = 0;
   int height = 0;
   SDL_QueryTexture (text, &format, &access, &weight, &height);

      // do the rect with weight and height
   SDL_Rect Rtext {0, 0, weight, height};

      /* copy the default img of y/n answer on texture y_n */
   SDL_Texture* y_n {NULL};
   ld_img_cpp (&y_n, renderer, "imgs/oui_non_default.bmp");

   SDL_Rect Ry_n {weight, 0, height * 2, height};


      /* copy them to m_field */
   SDL_SetRenderTarget (renderer, m_field);

   SDL_RenderCopy (renderer, text, NULL, &Rtext);
   SDL_RenderCopy (renderer, y_n, NULL, &Ry_n);

   SDL_RenderPresent (renderer);

   SDL_SetRenderTarget (renderer, NULL);
}

SDL_Texture* Field::get_texture () const {
   return m_field;
}

SDL_Rect Field::get_rect () const {
   return m_pos;
}
