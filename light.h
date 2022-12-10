#ifndef LIGHT_H
 #define LIGHT_H

 #include <GLES3/gl3.h>
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_image.h>
 #include <string>
 #include <iostream>
 #include <string>
 #include "Texture.h"
 #include "Shader.h"
 #include "utilities.h"

class Light {

  public:

   Light (std::string vertex_path, std::string fragment_path);
   ~Light ();

   void afficher (glm::mat4 view, glm::mat4 projection, glm::mat4 model);
   void use_shader (bool must_use);
   unsigned int get_shaderID ();
   glm::vec3 get_pos ();
   glm::vec3 get_ambient ();
   glm::vec3 get_diffuse ();
   glm::vec3 get_specular ();

  private:

   glm::vec3 m_pos;

   float m_vertices [108];
//   unsigned int m_indices [36];

   unsigned int m_VBO;
   unsigned int m_VAO;
//   unsigned int m_EBO;

   Shader m_shader;
};

#endif
