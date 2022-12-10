#ifndef HITBOX_H
 #define HITBOX_H

 #include <glm/glm.hpp>
 #include <glm/gtx/transform.hpp>
 #include <glm/gtc/type_ptr.hpp>

class Hitbox {

  public:

   Hitbox ();
   Hitbox (glm::vec3 pos, glm::vec3 taille);
   ~Hitbox ();
   bool pt_is_in (glm::vec3 const pt);
   bool hitbox_is_in (Hitbox const hitbox);
   glm::vec3 get_pos ();
   glm::vec3 get_taille ();
   void set_hitbox (glm::vec3 pos, glm::vec3 taille);
   void set_pos (glm::vec3 pos);
   void set_taille (glm::vec3 taille);

   private:

   glm::vec3 m_pos;
   glm::vec3 m_taille;
};

#endif
