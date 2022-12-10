#ifndef SHADER_H
 #define SHADER_H

 #include <iostream>
 #include <string>
 #include <sstream>
 #include <fstream>
 #include <GLES3/gl3.h>
 #include <SDL2/SDL.h>
 #include <SDL2/SDL_image.h>

class Shader {

  public:

   Shader (const GLchar* vertexPath, const GLchar* fragmentPath);
   ~Shader ();

      // Activation du shader
   void use (bool use) const;

      // fonctions utiles pour l'uniform
   void set_bool (const std::string &name, bool value) const;
   void set_int (const std::string &name, int value) const;
   void set_float (const std::string &name, float value) const;

   unsigned int getID () const;

  private:

      // the program ID
   unsigned int m_shaderID;
};

#endif
