#include "hitbox.h"

Hitbox::Hitbox () : m_pos {1.0}, m_taille {1.0} {
   
}

Hitbox::Hitbox (glm::vec3 pos, glm::vec3 taille) : m_pos {pos}, m_taille {taille} {
   
}

Hitbox::~Hitbox () {
   
}


bool Hitbox::pt_is_in (glm::vec3 const pt) {

   if (pt.x < m_pos.x || pt.x > m_pos.x + m_taille.x)
      return false;
   else if (pt.y < m_pos.y || pt.y > m_pos.y + m_taille.y)
      return false;
   else if (pt.z < m_pos.z || pt.z > m_pos.z + m_taille.z)
      return false;
   else
      return true;
}

bool Hitbox::hitbox_is_in (Hitbox const hitbox) {

   if (hitbox.m_pos.x > m_pos.x + m_taille.x || hitbox.m_pos.x + hitbox.m_taille.x < m_pos.x)
      return false;

   if (hitbox.m_pos.y > m_pos.y + m_taille.y || hitbox.m_pos.y + hitbox.m_taille.y < m_pos.y)
      return false;

   if (hitbox.m_pos.z > m_pos.z + m_taille.z || hitbox.m_pos.z + hitbox.m_pos.z < m_pos.z)
      return false;

   return true;













   /* this function tests the collision for all the corners of a grid, which created with i and j */
/*
   for (float i = 0 ; i < hitbox.m_taille.x / (hitbox.m_taille.x / 0.25) ; i += hitbox.m_taille.x / 0.25) {
      for (size_t j = 0 ; j < hitbox.m_taille.x / (hitbox.m_taille.x / 0.25) ; j += hitbox.m_taille.x / 0.25) {

            /* along the x axis */
/*
            if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + i, hitbox.m_pos.y + j, hitbox.m_pos.z + j)))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + i, hitbox.m_pos.y + j + (hitbox.m_taille.y - j * 2), hitbox.m_pos.z + j)))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + i, hitbox.m_pos.y + j, hitbox.m_pos.z + j + (hitbox.m_taille.z - j * 2))))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + i, hitbox.m_pos.y + j + (hitbox.m_taille.y - j * 2), hitbox.m_pos.z + j + (hitbox.m_taille.z - j * 2))))
            return true;
      }
   }

   for (float i = 0 ; i < hitbox.m_taille.y / (hitbox.m_taille.y / 0.25) ; i += hitbox.m_taille.y / 0.25) {
      for (size_t j = 0 ; j < hitbox.m_taille.x / (hitbox.m_taille.x / 0.25) ; j += hitbox.m_taille.x / 0.25) {

            /* along the y axis */
/*
         if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j, hitbox.m_pos.y + j + i, hitbox.m_pos.z + j)))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + (hitbox.m_taille.x - j * 2), hitbox.m_pos.y + j + i, hitbox.m_pos.z + j)))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j, hitbox.m_pos.y + j + i, hitbox.m_pos.z + j + (hitbox.m_taille.z - j * 2))))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + (hitbox.m_taille.x - j * 2), hitbox.m_pos.y + j + i, hitbox.m_pos.z + j + (hitbox.m_taille.z - j * 2))))
            return true;
      }
   }

   for (float i = 0 ; i < hitbox.m_taille.z / (hitbox.m_taille.z / 0.25) ; i += hitbox.m_taille.z / 0.25) {
      for (size_t j = 0 ; j < hitbox.m_taille.x / (hitbox.m_taille.x / 0.25) ; j += hitbox.m_taille.x / 0.25) {

            /* along the z axis */
/*
         if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j, hitbox.m_pos.y + j, hitbox.m_pos.z + j + i)))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + (hitbox.m_taille.x - j * 2), hitbox.m_pos.y + j, hitbox.m_pos.z + i)))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j, hitbox.m_pos.y + j + (hitbox.m_taille.y - j * 2), hitbox.m_pos.z + i)))
            return true;
         else if (pt_is_in (glm::vec3 (hitbox.m_pos.x + j + (hitbox.m_taille.x - j * 2), hitbox.m_pos.y + j + (hitbox.m_taille.y - j * 2), hitbox.m_pos.z + i)))
            return true;
      }
   }

   return false;

*/
}

glm::vec3 Hitbox::get_pos () {
   return m_pos;
}

glm::vec3 Hitbox::get_taille () {
   return m_taille;
}

void Hitbox::set_hitbox (glm::vec3 pos, glm::vec3 taille) {
   m_pos = pos;
   m_taille = taille;
}

void Hitbox::set_pos (glm::vec3 pos) {
   m_pos = pos;
}

void Hitbox::set_taille (glm::vec3 taille) {
   m_taille = taille;
}

