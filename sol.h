#ifndef SOL_H
 #define SOL_H

 #include <GLES3/gl3.h>
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_image.h>
 #include <string>
 #include <iostream>
 #include <string>
 #include "Texture.h"
 #include "Shader.h"
 #include "utilities.h"

class Sol {

  public:

   Sol (std::string source_vertex, std::string source_fragment);
   ~Sol ();

   void afficher (glm::mat4 view, glm::mat4 projection, glm::mat4 model);
   void use_shader (bool must_use);
   unsigned int get_shaderID ();
   void m_create_buffers_withoutEBO (unsigned int* VAO, unsigned int* VBO, float vertices [], size_t size_vertices);

  private:

   float m_vertices [18];

   unsigned int m_VBO;
   unsigned int m_VAO;
//   unsigned int m_EBO;
   Shader m_shader;

//   unsigned int m_texture2;

};

#endif
