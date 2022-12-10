#include "utilities.h"

std::array <float, 24> getcube (float taille, glm::vec3 center) {

   std::array <float, 24> cube {center.x - taille / (float)2.0, center.y - taille / (float)2.0, center.z - taille / (float)2.0,     // bas, gauche, devant
                                center.x + taille / (float)2.0, center.y - taille / (float)2.0, center.z - taille / (float)2.0,     // bas, droite, devant
                                center.x - taille / (float)2.0, center.y - taille / (float)2.0, center.z + taille / (float)2.0,     // haut, gauche, devant
                                center.x + taille / (float)2.0, center.y - taille / (float)2.0, center.z + taille / (float)2.0,     // haut, droite, devant
                                center.x - taille / (float)2.0, center.y + taille / (float)2.0, center.z - taille / (float)2.0,     // bas, gauche, deriere
                                center.x + taille / (float)2.0, center.y + taille / (float)2.0, center.z - taille / (float)2.0,     // bas, droite, deriere
                                center.x - taille / (float)2.0, center.y + taille / (float)2.0, center.z + taille / (float)2.0,     // haut, gauche, deriere
                                center.x + taille / (float)2.0, center.y + taille / (float)2.0, center.z + taille / (float)2.0};    // haut, droite, deriere
   return cube;
}

bool pt_is_in_cube (glm::vec3 pt, glm::vec3 center, float taille) {

   if (pt.x < center.x - taille / (float)2.0 || pt.x > center.x + taille / (float)2.0) // si x est plus grand ou plus petit
      return false;

   if (pt.y < center.y - taille / (float)2.0 || pt.y > center.y + taille / (float)2.0) // si y est plus grand ou plus petit
      return false;

   if (pt.z < center.z - taille / (float)2.0 || pt.z > center.z + taille / (float)2.0) // si z est plus grand ou plus petit
      return false;

   return true;
}

bool pt_is_in_pave (glm::vec3 pt, glm::vec3 haut_gauche_deriere, glm::vec3 bas_droite_devant) {

   if (pt.x < haut_gauche_deriere.x || pt.x > bas_droite_devant.x) // si x est plus grand ou plus petit
      return false;

   if (pt.y < bas_droite_devant.y || pt.y > haut_gauche_deriere.y) // si y est plus grand ou plus petit
      return false;

   if (pt.z < bas_droite_devant.z || pt.z > haut_gauche_deriere.z) // si z est plus grand ou plus petit
      return false;

   return true;
}

void change_window_size (int width, int height) {
   glViewport (0, 0, width, height);
}


unsigned int compile_shader (int type, std::string file_path) {

   unsigned int shader;

       // Création du shader
    shader = glCreateShader(type);
    if(shader == 0) {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }


       // Flux de lecture
    std::ifstream fichier (file_path.c_str());


       // Test d'ouverture
    if(!fichier) {
        std::cout << "Erreur le fichier " << file_path << " est introuvable" << std::endl;
        glDeleteShader(shader);
        return false;
    }

       // Strings permettant de lire le code source
    std::string ligne;
    std::string codeSource;


       // Lecture
    while(getline(fichier, ligne))
        codeSource += ligne + '\n';


       // Fermeture du fichier
    fichier.close();


       // Récupération de la chaine C du code source
    const GLchar* chaineCodeSource = codeSource.c_str();

    std::cout << "----===[sources]===----" << std::endl << std::endl << chaineCodeSource << std::endl << std::endl << "----===[fin source]===----" << std::endl;

       // Envoi du code source au shader
    glShaderSource(shader, 1, &chaineCodeSource, NULL);

       // Compilation du shader
    glCompileShader(shader);

       // Vérification de la compilation
    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

       // S'il y a eu une erreur
    if (erreurCompilation != GL_TRUE) {

           // Récupération de la taille de l'erreur
        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);

           // Allocation de mémoire
        char *erreur = new char[tailleErreur + 1];

           // Récupération de l'erreur
        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
        erreur [tailleErreur] = '\0';

           // Affichage de l'erreur
        std::cout << erreur << std::endl;

           // Libération de la mémoire et retour du booléen false
        delete [] erreur;
        glDeleteShader(shader);

        return 0;
    }

       // Sinon c'est que tout s'est bien passé
    else
        return shader;
}

bool show_errors_shader (unsigned int shader) {

   int success;
   char infoLog [512];
 
   glGetProgramiv (shader, GL_COMPILE_STATUS, &success);

   if (!success) {
      glGetShaderInfoLog (shader, 512, NULL, infoLog);
      std::cout << "error: " << infoLog << std::endl << "this error is not fatal, but maiby you can see an <erreur d'affichage> ." << std::endl;
      return false;
   }

   return true;
}



void create_buffers (unsigned int* VAO, unsigned int* VBO, unsigned int* EBO, float vertices [], size_t size_vertices, unsigned int indices [], size_t size_indices) {

   glGenVertexArrays(1, VAO);
   glGenBuffers(1, VBO);
   glGenBuffers(1, EBO);

   glBindVertexArray(*VAO);

   glBindBuffer(GL_ARRAY_BUFFER, *VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices [0]) * size_vertices, vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices [0]) * size_indices, indices, GL_STATIC_DRAW);

      // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
      // texture coord attribute
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);
}


void create_buffers_withoutEBO (unsigned int* VAO, unsigned int* VBO, float vertices [], size_t size_vertices) {

   glGenVertexArrays(1, VAO);
   glGenBuffers(1, VBO);

   glBindVertexArray(*VAO);

   glBindBuffer(GL_ARRAY_BUFFER, *VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices [0]) * size_vertices, vertices, GL_STATIC_DRAW);

      // position attribute
   glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray (0);
}


void create_texture (unsigned int* texture, const char* path, bool inverser) {

   glGenTextures (1, texture);
   glBindTexture (GL_TEXTURE_2D, *texture); 
      // set the texture wrapping parameters
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   SDL_Surface* img = IMG_Load (path);
   if (img) {

      if (inverser)
         img = inverserPixels (img);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img -> w, img -> h, 0, GL_RGB, GL_UNSIGNED_BYTE, img -> pixels);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else {
      std::cout << "Failed to load texture" << std::endl;
   }
   SDL_FreeSurface (img);
}


SDL_Surface* inverserPixels (SDL_Surface *imageSource) {

      // Copie conforme de l'image source sans les pixels
   SDL_Surface *imageInversee = SDL_CreateRGBSurface(0, imageSource -> w, imageSource -> h, imageSource -> format -> BitsPerPixel, imageSource -> format -> Rmask,
                                                     imageSource -> format -> Gmask, imageSource -> format -> Bmask, imageSource -> format -> Amask);

      // Tableau intermédiaires permettant de manipuler les pixels
   unsigned char* pixelsSources = (unsigned char*) imageSource->pixels;
   unsigned char* pixelsInverses = (unsigned char*) imageInversee->pixels;


      // Inversion des pixels
   for(int i = 0; i < imageSource->h; i++)
      for(int j = 0; j < imageSource->w * imageSource->format->BytesPerPixel; j++)
         pixelsInverses[(imageSource->w * imageSource->format->BytesPerPixel * (imageSource->h - 1 - i)) + j] = pixelsSources[(imageSource->w * imageSource->format->BytesPerPixel * i) + j];


      // Retour de l'image inversée
   return imageInversee;
}

glm::vec3 rotate_vector (glm::vec3 vector, glm::vec3 axis, float angle) {

   glm::vec4 result = glm::vec4 (vector.x, vector.y, vector.z, 1.0f);

   glm::mat4 rotate_matrix = {

      cos (angle) + pow (axis.x, 2) * (1 - cos (angle)),             axis.x * axis.y * (1 - cos (angle)) - axis.z * sin (angle),    axis.x * axis.z * (1 - cos (angle)) + axis.y * sin (angle),    0,
      axis.y * axis.x * (1 - cos (angle)) + axis.z * sin (angle),    cos (angle) + pow (axis.y, 2) * (1 - cos (angle)),             axis.y * axis.z * (1 - cos (angle)) - axis.x * sin (angle),    0,
      axis.z * axis.x * (1 - cos (angle)) - axis.y * sin (angle),    axis.z * axis.y * (1 - cos (angle)) + axis.x * sin (angle),    cos (angle) + pow (axis.z, 2) * (1 - cos (angle)),             0,
                              0,                                                                0,                                                          0,                                     1

                              };

   result = rotate_matrix * result;

   return glm::vec3 (result.x, result.y, result.z);
}


bool point_is_in_pave (glm::vec3 pos, glm::vec3 taille, glm::vec3 pt) {

   if (pt.x < pos.x || pt.x > pos.x + taille.x)
      return false;
   if (pt.y < pos.y || pt.y > pos.y + taille.y)
      return false;
   if (pt.z < pos.z || pt.z > pos.z + taille.z)
      return false;

   return true;
}


