#include "sol.h"

Sol::Sol (std::string sources_vertex, std::string sources_fragment) : m_VBO {0}, m_VAO {0},/* m_EBO {0},*/ m_shader ("shaders/basicShaderColor.vertex", "shaders/basicShaderColor.fragment"){


      // un objet cubique
    float vertices [] = {
         // sommets
        -25.0f, -25.0f,  0.0f,
         25.0f, -25.0f,  0.0f,
         25.0f,  25.0f,  0.0f,
         25.0f,  25.0f,  0.0f,
        -25.0f,  25.0f,  0.0f,
        -25.0f, -25.0f,  0.0f
    };

    for (size_t i = 0; i < 18; ++i) {
       m_vertices [i] = vertices [i];
    }

    m_create_buffers_withoutEBO (&m_VAO, &m_VBO, m_vertices, 18);
}


Sol::~Sol () {

}


void Sol::afficher (glm::mat4 view, glm::mat4 projection, glm::mat4 model) {

      // render container
   m_shader.use (true);

      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "projection"), 1, GL_FALSE, glm::value_ptr (projection));
      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "view"), 1, GL_FALSE, glm::value_ptr (view));
      glUniformMatrix4fv (glGetUniformLocation (m_shader.getID (), "model"), 1, GL_FALSE, glm::value_ptr (model));

      glBindVertexArray (m_VAO);

         glDrawArrays (GL_TRIANGLES, 0, 6);
}


void Sol::use_shader (bool must_use) {
   m_shader.use (must_use);
}

unsigned int Sol::get_shaderID () {
   return m_shader.getID ();
}

void Sol::m_create_buffers_withoutEBO (unsigned int* VAO, unsigned int* VBO, float vertices [], size_t size_vertices) {

   glGenVertexArrays (1, VAO);
   glGenBuffers (1, VBO);

   glBindVertexArray (*VAO);

      glBindBuffer (GL_ARRAY_BUFFER, *VBO);
         glBufferData (GL_ARRAY_BUFFER, sizeof(vertices [0]) * size_vertices, vertices, GL_STATIC_DRAW);

            // position attribute
         glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
         glEnableVertexAttribArray (0);
}
