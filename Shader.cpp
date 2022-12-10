#include "Shader.h"

/********************************************
 * constructeur de la classe Shader         *
 * --------------------------------         *
 * crée le shader à partir des fichiers     *
 * spécifiés par vertexPath et fragmentPath *
 ********************************************/

Shader::Shader (const GLchar* vertexPath, const GLchar* fragmentPath) {

      // 1. récupère le code du vertex/fragment shader depuis filePath
   std::string vertexCode;
   std::string fragmentCode;
   std::ifstream vShaderFile;
   std::ifstream fShaderFile;

      // s'assure que les objets ifstream peuvent envoyer des exceptions:
   vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
   fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

   try {

         // ouverture des fichiers
      vShaderFile.open (vertexPath);
      fShaderFile.open (fragmentPath);
      std::stringstream vShaderStream, fShaderStream;

         // lecture des fichiers et placement des contenus dans des flux
      vShaderStream << vShaderFile.rdbuf ();
      fShaderStream << fShaderFile.rdbuf ();

         // fermeture des fichiers
      vShaderFile.close ();
      fShaderFile.close ();

         // convertions des flux en string
      vertexCode = vShaderStream.str ();
      fragmentCode = fShaderStream.str ();

   }
   catch (std::ifstream::failure e) {
      std::cout << "error : cannot read " << vertexPath << " | " << fragmentPath << std::endl;
   }

   const char* vShaderCode = vertexCode.c_str ();
   const char* fShaderCode = fragmentCode.c_str ();


      // 2. compiler les shaders
   unsigned int vertex, fragment;

   int success;
   char infoLog [512];

      // vertex shader
   vertex = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertex, 1, &vShaderCode, NULL);
   glCompileShader(vertex);

      // affiche les erreurs de compilation si besoin
   glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "error : compilation error for vertex shader " << vertexPath << std::endl << infoLog << std::endl;
   };

      // fragment shader
   fragment = glCreateShader (GL_FRAGMENT_SHADER);
   glShaderSource (fragment, 1, &fShaderCode, NULL);
   glCompileShader (fragment);

      // affiche les erreurs de compilation si besoin
   glGetShaderiv (fragment, GL_COMPILE_STATUS, &success);
   if (!success) {
      glGetShaderInfoLog (fragment, 512, NULL, infoLog);
      std::cout << "error : compilation error for fragment shader " << fragmentPath << std::endl << infoLog << std::endl;
   };

      // program shader
   m_shaderID = glCreateProgram ();
   glAttachShader (m_shaderID, vertex);
   glAttachShader (m_shaderID, fragment);
   glLinkProgram (m_shaderID);

      // affiche les erreurs d'édition de liens si besoin
   glGetProgramiv (m_shaderID, GL_LINK_STATUS, &success);
   if (!success) {
      glGetProgramInfoLog (m_shaderID, 512, NULL, infoLog);
      std::cout << "error : linking error for the shader program\n" << infoLog << std::endl;
   }
      // supprime les shaders qui sont maintenant liés dans le programme et qui ne sont plus nécessaires
   glDeleteShader (vertex);
   glDeleteShader (fragment);
}


Shader::~Shader () {
   glDeleteProgram (m_shaderID);
}


   // Activation du shader
void Shader::use (bool use) const {
   if (use)
      glUseProgram (m_shaderID);
   else
      glUseProgram (0);
}


/*****************************************
 * set_bool :                            *
 * ----------                            *
 * affecte à la variable uniforme 'name' *
 * du shader la valeur 'value'           *
 *****************************************/

void Shader::set_bool (const std::string &name, bool value) const {
   glUniform1i (glGetUniformLocation(m_shaderID, name.c_str()), (int)value);
}

/*****************************************
 * set_int :                             *
 * ----------                            *
 * affecte à la variable uniforme 'name' *
 * du shader la valeur 'value'           *
 *****************************************/

void Shader::set_int (const std::string &name, int value) const {
   glUniform1i (glGetUniformLocation(m_shaderID, name.c_str()), value);
}

/*****************************************
 * set_float :                           *
 * ----------                            *
 * affecte à la variable uniforme 'name' *
 * du shader la valeur 'value'           *
 *****************************************/

void Shader::set_float (const std::string &name, float value) const {
   glUniform1f (glGetUniformLocation(m_shaderID, name.c_str()), value);
}


/*******************************
 * getID :                     *
 * --------                    *
 * retourne le shader lui-même *
 *******************************/

unsigned int Shader::getID () const {
   return m_shaderID;
}


