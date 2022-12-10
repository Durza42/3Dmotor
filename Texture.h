#ifndef DEF_TEXTURE
 #define DEF_TEXTURE

 #ifdef WIN32
  #include <GL/glew.h>
  #include <SDL2/SDL_image.h>

 #elif __APPLE__
  #define GL3_PROTOTYPES 1
  #include <OpenGL/gl3.h>
  #include <SDL2_image/SDL_image.h>

 #else
  #define GL3_PROTOTYPES 1
  #include <GLES3/gl3.h>
  #include <SDL2/SDL_image.h>

 #endif

 #include <SDL2/SDL.h>
 #include <iostream>
 #include <string>


class Texture {

  public:

   Texture();
   Texture(Texture const &textureACopier);
   Texture(const std::string fichierImage);
   ~Texture();

   Texture& operator=(Texture const &textureACopier);
   bool charger();
   SDL_Surface* inverserPixels(SDL_Surface *imageSource) const;

   unsigned int getID() const;
   void setFichierImage(const std::string &fichierImage);

   void Bind (bool must_bind);

  private:

   unsigned int m_id;
   std::string m_fichierImage;
};

#endif
