#include "menus.h"

Menu::Menu () : m_nb_field {0}, m_result {NULL} {
   
}

Menu::~Menu () {
   
}

void Menu::add_field (Field field_added) {
   m_fields.push_back (field_added);
}

SDL_Texture* Menu::get_result () const {
   return m_result;
}
