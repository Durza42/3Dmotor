#include "mur.h"

Mur::Mur (std::string sources_vertex, std::string sources_fragment, float height, float lenght, float weight, glm::vec3 pos) : m_VBO {0}, m_VAO {0},/* m_EBO {0},*/ m_shader ("shaders/basicShader.vertex", "shaders/basicShader.fragment"), m_pos (pos), m_taille (lenght, height, weight) {


      // un objet cubique
    float vertices [] = {
         // sommets           // normales       // texture coords
         0.0f,  0.0f,  0.0f,  0.0,  0.0, -1.0,  0.0, 0.0,   // face du bas
        lenght, 0.0f,  0.0f,  0.0,  0.0, -1.0,  1.0, 0.0,
        lenght,weight, 0.0f,  0.0,  0.0, -1.0,  1.0, 1.0,
        lenght,weight, 0.0f,  0.0,  0.0, -1.0,  1.0, 1.0,
         0.0f, weight, 0.0f,  0.0,  0.0, -1.0,  0.0, 1.0,
         0.0f,  0.0f,  0.0f,  0.0,  0.0, -1.0,  0.0, 0.0,

         0.0f,  0.0f, height, 0.0,  0.0,  1.0,  0.0, 0.0,// face du haut
        lenght, 0.0f, height, 0.0,  0.0,  1.0,  1.0, 0.0,
        lenght,weight,height, 0.0,  0.0,  1.0,  1.0, 1.0,
        lenght,weight,height, 0.0,  0.0,  1.0,  1.0, 1.0,
         0.0f, weight,height, 0.0,  0.0,  1.0,  0.0, 1.0,
         0.0f,  0.0f, height, 0.0,  0.0,  1.0,  0.0, 0.0,

         0.0f, weight,height,-1.0,  0.0,  0.0,  1.0, 1.0,   // face de droite
         0.0f, weight, 0.0f, -1.0,  0.0,  0.0,  1.0, 0.0,
         0.0f,  0.0f,  0.0f, -1.0,  0.0,  0.0,  0.0, 0.0,
         0.0f,  0.0f,  0.0f, -1.0,  0.0,  0.0,  0.0, 0.0,
         0.0f,  0.0f, height,-1.0,  0.0,  0.0,  0.0, 1.0,
         0.0f, weight,height,-1.0,  0.0,  0.0,  1.0, 1.0,

        lenght,weight,height, 1.0,  0.0,  0.0,  1.0, 1.0,   // face de gauche
        lenght,weight, 0.0f,  1.0,  0.0,  0.0,  1.0, 0.0,
        lenght, 0.0f,  0.0f,  1.0,  0.0,  0.0,  0.0, 0.0,
        lenght, 0.0f,  0.0f,  1.0,  0.0,  0.0,  0.0, 0.0,
        lenght, 0.0f, height, 1.0,  0.0,  0.0,  0.0, 1.0,
        lenght,weight,height, 1.0,  0.0,  0.0,  1.0, 1.0,

         0.0f,  0.0f,  0.0f,  0.0, -1.0,  0.0,  0.0, 0.0,     // face de devant
        lenght, 0.0f,  0.0f,  0.0, -1.0,  0.0,  1.0, 0.0,
        lenght, 0.0f, height, 0.0, -1.0,  0.0,  1.0, 1.0,
        lenght, 0.0f, height, 0.0, -1.0,  0.0,  1.0, 1.0,
         0.0f,  0.0f, height, 0.0, -1.0,  0.0,  0.0, 1.0,
         0.0f,  0.0f,  0.0f,  0.0, -1.0,  0.0,  0.0, 0.0,

         0.0f, weight, 0.0f,  0.0,  1.0,  0.0,  0.0, 0.0,  // face de derriere
        lenght,weight, 0.0f,  0.0,  1.0,  0.0,  1.0, 0.0,
        lenght,weight,height, 0.0,  1.0,  0.0,  1.0, 1.0,
        lenght,weight,height, 0.0,  1.0,  0.0,  1.0, 1.0,
         0.0f, weight,height, 0.0,  1.0,  0.0,  0.0, 1.0,
         0.0f, weight, 0.0f,  0.0,  1.0,  0.0,   0.0, 0.0,
    };

    for (size_t i = 0; i < 288; ++i) {
       m_vertices [i] = vertices [i];
    }

    m_create_buffers_withoutEBO (&m_VAO, &m_VBO, m_vertices, 288);
    create_texture (&m_texture, "texture.jpg", true);

    m_shader.use (true);
    m_shader.set_int("material.diffuse", 0);
}


Mur::Mur (std::string sources_vertex, std::string sources_fragment, float height, float lenght, float weight, glm::vec3 pos, unsigned int text) : m_VBO {0}, m_VAO {0},/* m_EBO {0},*/ m_shader ("shaders/basicShader.vertex", "shaders/basicShader.fragment"), m_pos (pos), m_taille (lenght, height, weight), m_texture {text} {


      // un objet cubique
    float vertices [] = {
         // sommets           // normales       // texture coords
         0.0f,  0.0f,  0.0f,  0.0,  0.0, -1.0,  0.0, 0.0,   // face du bas
        lenght, 0.0f,  0.0f,  0.0,  0.0, -1.0,  1.0, 0.0,
        lenght,weight, 0.0f,  0.0,  0.0, -1.0,  1.0, 1.0,
        lenght,weight, 0.0f,  0.0,  0.0, -1.0,  1.0, 1.0,
         0.0f, weight, 0.0f,  0.0,  0.0, -1.0,  0.0, 1.0,
         0.0f,  0.0f,  0.0f,  0.0,  0.0, -1.0,  0.0, 0.0,

         0.0f,  0.0f, height, 0.0,  0.0,  1.0,  0.0, 0.0,// face du haut
        lenght, 0.0f, height, 0.0,  0.0,  1.0,  1.0, 0.0,
        lenght,weight,height, 0.0,  0.0,  1.0,  1.0, 1.0,
        lenght,weight,height, 0.0,  0.0,  1.0,  1.0, 1.0,
         0.0f, weight,height, 0.0,  0.0,  1.0,  0.0, 1.0,
         0.0f,  0.0f, height, 0.0,  0.0,  1.0,  0.0, 0.0,

         0.0f, weight,height,-1.0,  0.0,  0.0,  1.0, 1.0,   // face de droite
         0.0f, weight, 0.0f, -1.0,  0.0,  0.0,  1.0, 0.0,
         0.0f,  0.0f,  0.0f, -1.0,  0.0,  0.0,  0.0, 0.0,
         0.0f,  0.0f,  0.0f, -1.0,  0.0,  0.0,  0.0, 0.0,
         0.0f,  0.0f, height,-1.0,  0.0,  0.0,  0.0, 1.0,
         0.0f, weight,height,-1.0,  0.0,  0.0,  1.0, 1.0,

        lenght,weight,height, 1.0,  0.0,  0.0,  1.0, 1.0,   // face de gauche
        lenght,weight, 0.0f,  1.0,  0.0,  0.0,  1.0, 0.0,
        lenght, 0.0f,  0.0f,  1.0,  0.0,  0.0,  0.0, 0.0,
        lenght, 0.0f,  0.0f,  1.0,  0.0,  0.0,  0.0, 0.0,
        lenght, 0.0f, height, 1.0,  0.0,  0.0,  0.0, 1.0,
        lenght,weight,height, 1.0,  0.0,  0.0,  1.0, 1.0,

         0.0f,  0.0f,  0.0f,  0.0, -1.0,  0.0,  0.0, 0.0,     // face de devant
        lenght, 0.0f,  0.0f,  0.0, -1.0,  0.0,  1.0, 0.0,
        lenght, 0.0f, height, 0.0, -1.0,  0.0,  1.0, 1.0,
        lenght, 0.0f, height, 0.0, -1.0,  0.0,  1.0, 1.0,
         0.0f,  0.0f, height, 0.0, -1.0,  0.0,  0.0, 1.0,
         0.0f,  0.0f,  0.0f,  0.0, -1.0,  0.0,  0.0, 0.0,

         0.0f, weight, 0.0f,  0.0,  1.0,  0.0,  0.0, 0.0,  // face de derriere
        lenght,weight, 0.0f,  0.0,  1.0,  0.0,  1.0, 0.0,
        lenght,weight,height, 0.0,  1.0,  0.0,  1.0, 1.0,
        lenght,weight,height, 0.0,  1.0,  0.0,  1.0, 1.0,
         0.0f, weight,height, 0.0,  1.0,  0.0,  0.0, 1.0,
         0.0f, weight, 0.0f,  0.0,  1.0,  0.0,   0.0, 0.0,
    };

    for (size_t i = 0; i < 288; ++i) {
       m_vertices [i] = vertices [i];
    }

    m_create_buffers_withoutEBO (&m_VAO, &m_VBO, m_vertices, 288);

    m_shader.use (true);
    m_shader.set_int("material.diffuse", 0);
}


Mur::~Mur () {

}


void Mur::afficher (glm::mat4 view, glm::mat4 projection, glm::mat4 model, glm::vec3 lightPos, glm::vec3 posCamera, glm::vec3 light_ambient, glm::vec3 light_diffuse, glm::vec3 light_specular) const {

   model = glm::mat4 (1.0);
   model = glm::translate (model, m_pos);

      // render container
   m_shader.use (true);

      glUniform3f (glGetUniformLocation (m_shader.getID (), "light.ambient"), light_ambient.x, light_ambient.y, light_ambient.z);
      glUniform3f (glGetUniformLocation (m_shader.getID (), "light.diffuse"), light_diffuse.x, light_diffuse.y, light_diffuse.z);
      glUniform3f (glGetUniformLocation (m_shader.getID (), "light.specular"), light_specular.x, light_specular.y, light_specular.z);

      glUniform3f (glGetUniformLocation (m_shader.getID (), "material.specular"), 0.332741f, 0.328634f, 0.346435);
      glUniform1f (glGetUniformLocation (m_shader.getID (), "material.shininess"), 38.4f);

      glUniform3f (glGetUniformLocation (m_shader.getID (), "lightColor"), 1.0f, 1.0f, 1.0f);
      glUniform3f (glGetUniformLocation (m_shader.getID (), "objectColor"), 1.0f, 0.5f, 0.31f);
      glUniform3f (glGetUniformLocation (m_shader.getID (), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
      glUniform3f (glGetUniformLocation (m_shader.getID (), "viewPos"), posCamera.x, posCamera.y, posCamera.z);

      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "projection"), 1, GL_FALSE, glm::value_ptr (projection));
      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "view"), 1, GL_FALSE, glm::value_ptr (view));
      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "model"), 1, GL_FALSE, glm::value_ptr (model));

      glBindVertexArray (m_VAO);

         glBindTexture(GL_TEXTURE_2D, m_texture);

            glDrawArrays (GL_TRIANGLES, 0, 36);
}


void Mur::use_shader (bool must_use) {
   m_shader.use (must_use);
}

unsigned int Mur::get_shaderID () {
   return m_shader.getID ();
}

void Mur::m_create_buffers_withoutEBO (unsigned int* VAO, unsigned int* VBO, float vertices [], size_t size_vertices) {

   glGenVertexArrays (1, VAO);
   glGenBuffers (1, VBO);

   glBindVertexArray (*VAO);

   glBindBuffer (GL_ARRAY_BUFFER, *VBO);
   glBufferData (GL_ARRAY_BUFFER, sizeof(vertices [0]) * size_vertices, vertices, GL_STATIC_DRAW);

      // position attribute
   glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray (0);

      // normale attribute
   glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray (1);

      // texture position attribute
   glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
   glEnableVertexAttribArray (2);
}

glm::vec3 Mur::get_pos () {
   return m_pos;
}


glm::vec3 Mur::get_taille () {
   return m_taille;
}

