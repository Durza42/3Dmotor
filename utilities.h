#ifndef UTILITIES_H
 #define UTILITIES_H

 #include <array>
 #include <iostream>
 #include <fstream>

 #include <GLES3/gl3.h>

 #include "glm/glm.hpp"
 #include "glm/gtx/transform.hpp"
 #include "glm/gtc/type_ptr.hpp"

 #include <SDL2/SDL_image.h>
 #include <SDL2/SDL.h>

 #include "mur.h"


std::array <float, 24> getcube (float taille, glm::vec3 center);
bool pt_is_in_cube (glm::vec3 pt, glm::vec3 center, float taille);
bool pt_is_in_pave (glm::vec3 pt, glm::vec3 haut_gauche_deriere, glm::vec3 bas_droite_devant);
void change_window_size (int width, int height);
unsigned int compile_shader (int type, std::string file_path);
bool show_errors_shader (unsigned int shader);
void create_buffers (unsigned int* VAO, unsigned int* VBO, unsigned int* EBO, float vertices [], size_t size_vertices, unsigned int indices [], size_t size_indices);
void create_buffers_withoutEBO (unsigned int* VAO, unsigned int* VBO, float vertices [], size_t size_vertices);
void create_texture (unsigned int* texture, const char* path, bool inverser);
SDL_Surface* inverserPixels (SDL_Surface *imageSource);
glm::vec3 rotate_vector (glm::vec3 vector, glm::vec3 axis, float angle);
bool point_is_in_pave (glm::vec3 pos, glm::vec3 taille, glm::vec3 pt);

#endif
