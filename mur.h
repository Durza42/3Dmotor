#ifndef MUR_H
 #define MUR_H

 #include <GLES3/gl3.h>
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_image.h>
 #include <string>
 #include <iostream>
 #include <string>
 #include "Texture.h"
 #include "Shader.h"
 #include "utilities.h"

class Mur {

  public:

   Mur (std::string sources_vertex, std::string sources_fragment, float height, float lenght, float weight, glm::vec3 pos);
   Mur (std::string sources_vertex, std::string sources_fragment, float height, float lenght, float weight, glm::vec3 pos, unsigned int text);
   ~Mur ();

   void afficher (glm::mat4 view, glm::mat4 projection, glm::mat4 model, glm::vec3 lightPos, glm::vec3 posCamera, glm::vec3 light_ambient, glm::vec3 light_diffuse, glm::vec3 light_specular) const;
   void use_shader (bool must_use);
   unsigned int get_shaderID ();
   void m_create_buffers_withoutEBO (unsigned int* VAO, unsigned int* VBO, float vertices [], size_t size_vertices);
   glm::vec3 get_pos ();
   glm::vec3 get_taille ();
   

  private:

   float m_vertices [288];

   unsigned int m_VBO;
   unsigned int m_VAO;
//   unsigned int m_EBO;
   Shader m_shader;

   glm::vec3 m_pos;
   glm::vec3 m_taille;

   unsigned int m_texture;
//   unsigned int m_texture2;

};

#endif
