#include "light.h"

Light::Light (std::string vertex_path, std::string fragment_path) : m_VBO {0}, m_VAO {0}/*, m_EBO {0},*/, m_shader (vertex_path.c_str (), fragment_path.c_str ()), m_pos (0.0f, 0.0f, 100.0f) {

      // une lampe cubique
    float vertices [] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    for (size_t i = 0; i < 108; ++i) {
       m_vertices [i] = vertices [i];
    }

    create_buffers_withoutEBO (&m_VAO, &m_VBO, m_vertices, 180);

/*
    create_texture (&m_texture, "texture.jpg", true);
    create_texture (&m_texture2, "texture2.jpg", true);

    m_shader.use (true);
    m_shader.setInt("texture1", 0);
    m_shader.setInt("texture2", 1);
*/
}


Light::~Light () {

}


void Light::afficher (glm::mat4 view, glm::mat4 projection, glm::mat4 model) {

   m_pos = rotate_vector (m_pos, glm::vec3 (1.0f, 0.0f, 0.0f), 0.01);

      // render container
   m_shader.use (true);

      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "projection"), 1, GL_FALSE, glm::value_ptr (projection));
      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "view"), 1, GL_FALSE, glm::value_ptr (view));
      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "model"), 1, GL_FALSE, glm::value_ptr (model));

      glBindVertexArray (m_VAO);

         glDrawArrays (GL_TRIANGLES, 0, 36);
}


void Light::use_shader (bool must_use) {
   m_shader.use (must_use);
}

unsigned int Light::get_shaderID () {
   return m_shader.getID ();
}

glm::vec3 Light::get_pos () {
   return m_pos;
}

glm::vec3 Light::get_ambient () {
   return glm::vec3 (1.0, 1.0, 1.0);
}

glm::vec3 Light::get_diffuse () {
   return glm::vec3 (0.9, 0.9, 0.9);
}

glm::vec3 Light::get_specular () {
   return glm::vec3 (1.0, 1.0, 1.0);
}
