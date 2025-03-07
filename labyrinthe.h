#ifndef LABYRINTHE_H
 #define LABYRINTHE_H

 #include "glm/glm.hpp"
 #include "glm/gtx/transform.hpp"
 #include "glm/gtc/type_ptr.hpp"

 #include <array>

 #include "hitbox.h"
 #include "mur.h"


 #define NB_MURS 32

class Labyrinthe {

  public:

   Labyrinthe (std::string vertex_shader, std::string fragment_shader);
   ~Labyrinthe ();
   Hitbox get_hitbox (size_t const i) const;
   std::array <Hitbox, NB_MURS> get_hitbox () const;
   void print (glm::mat4 view, glm::mat4 projection, glm::mat4 model, glm::vec3 lightPos, glm::vec3 posCamera, glm::vec3 light_ambient, glm::vec3 light_diffuse, glm::vec3 light_specular) const;
   std::array <bool, 2500> get_grid () const;
   bool get_member_grid (const int x, const int y) const;

  private:

   std::array <Mur, NB_MURS> m_murs;
   std::array <Hitbox, NB_MURS> m_hitboxs;
   std::array <bool, 2500> m_colision_map; // = colision_map [50][50]
};

#endif
