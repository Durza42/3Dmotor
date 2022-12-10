#include <iostream>

#include "main_class.h"
#include "utilities.h"
#include "Input.h"
#include "sol.h"
#include "mur.h"
#include "light.h"
#include "Shader.h"
#include "Texture.h"
#include "labyrinthe.h"

Main::Main () : m_window {NULL}, m_weight {800}, m_height {600}, m_camera (glm::vec3 (15, 15, 2), glm::vec3 (0, 0, 0), glm::vec3 (0, 0, 1), 0.4, 0.5), V_z {0}, m_ticks_last_jump {0} {
   m_camera.setVitesse (0.05);
}

Main::~Main () {
   
}

void Main::init () {

      // initialisation SDL
   if (SDL_Init (SDL_INIT_VIDEO) < 0) {
      std::cout << "error SDL2 Initialisation : " << SDL_GetError () << std::endl << "fatal error; abort." << std::endl;
      exit (1);
   }

      // compatibilité OpenGL3
   SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
   SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3);

      // création de la fenetre
   m_window = SDL_CreateWindow ("jeu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_weight, m_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
      // test de réussite
   if (m_window == NULL) {
      std::cout << "error Creating window : " << SDL_GetError () << std::endl << "fatal error; abort" << std::endl;
      exit (1);
   }

      // Création du contexte OpenGL
   m_contexteOpenGL = SDL_GL_CreateContext(m_window);

   if(m_contexteOpenGL == 0) {
      std::cout << "error creating OpenGL context : " << SDL_GetError() << std::endl << "fatal error; abort" << std::endl;

      SDL_DestroyWindow(m_window);
      SDL_Quit();

      exit (1);
   }

      /* Nous pourrions définir des dimensions plus petites pour la zone de rendu (viewport), et OpenGL effectuerait ses
rendus dans une zone plus petite, laissant la place restante pour d’autres affichages indépendants d’OpenGL. */
   glViewport(0, 0, 800, 600);

   glEnable (GL_DEPTH_TEST);
}



void Main::boucle () {

   Sol sol ("shaders/basicShader.vertex", "shaders/basicShader.fragment");

   Light light ("shaders/lightningShader.vertex", "shaders/lightningShader.fragment");

   Labyrinthe labyrinthe ("shaders/basicShader.vertex", "shaders/basicShader.fragment");

   glm::mat4 view = glm::mat4 (1.0);
   glm::mat4 projection = glm::mat4 (1.0);
   glm::mat4 model = glm::mat4 (1.0);

      // Caméra mobile
   m_input.afficherPointeur(false);
   m_input.capturerPointeur(true);
      // Placement de la caméra
   m_camera.lookAt (view);
   m_camera.setVitesse (0.5);


   float deltaTime, lastFrame, currentFrame;

   float cameraSpeed = 2.5f * deltaTime;

   float angle (0.0f);

      // boucle principale
   while (1) {

      glClearColor(0.1f, 0.15f, 0.15f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // gestion des évenements
      m_input.updateEvenements ();
      do_events (labyrinthe.get_grid());

      SDL_Delay (10);
      currentFrame = SDL_GetTicks () / 1000.0;
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

         // Placement de la caméra
      m_camera.lookAt (view);
      projection = glm::perspective(glm::radians(45.0f), (float)800.0 / (float)600.0, 0.1f, 100.0f);
      model = glm::mat4 (1.0);

      sol.afficher (view, projection, model);

      labyrinthe.print (view, projection, model, light.get_pos (), m_camera.getPos (), light.get_ambient (), light.get_diffuse (), light.get_specular ());

      model = glm::mat4 (1.0f);
      model = glm::scale (model, glm::vec3 (0.5f));
      model = glm::translate (model, light.get_pos ());

      light.afficher (view, projection, model);

      SDL_GL_SwapWindow(m_window);
   }
}


void Main::do_events (const std::array <bool, 2500> colision_grid) {

   if (m_input.resize ()) {
      SDL_GetWindowSize (m_window, &m_weight, &m_height);
      change_window_size (m_weight, m_height);
   }

   if (m_input.terminer () || m_input.getTouche (SDL_SCANCODE_ESCAPE))
      exit (0);

      // moove mouse
   if (m_input.getXRel () != 0 || m_input.getYRel () != 0) {
      m_camera.orienter (m_input.getXRel (), m_input.getYRel ());
   }

      /* X-Y moove (wasd) */

   if (m_input.getTouche (SDL_SCANCODE_W))
      go_on (colision_grid);

   if (m_input.getTouche (SDL_SCANCODE_S))
      go_back (colision_grid);

   if (m_input.getTouche (SDL_SCANCODE_A))
      go_left (colision_grid);

   if (m_input.getTouche (SDL_SCANCODE_D))
      go_right (colision_grid);

      /* Z moove */

   if (!tomber ())
      if (m_input.getTouche (SDL_SCANCODE_SPACE))
         jump ();

   if (m_input.getTouche (SDL_SCANCODE_LSHIFT))
      accroupir ();
}

void Main::go_on (const std::array <bool, 2500> colision_grid) {

   glm::vec3 dist = m_camera.go_on (); // la cam va en avant

   if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) { // si collision

      m_camera.go_back (); // elle revient en arrière

         /* on la fait glisser contre le mur (tous les murs sont paralèles aux axes) */

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y + dist.y, m_camera.getPos ().z)); // on ajoute des Y
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y - dist.y, m_camera.getPos ().z)); // on retourne en arière

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x + dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on ajoute des X
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x - dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on retourne en arière
   }
}

void Main::go_back (const std::array <bool, 2500> colision_grid) {

   glm::vec3 dist = m_camera.go_back (); // la cam va en arière

   if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) { // si collision

      m_camera.go_on (); // elle revient devant

         /* on la fait glisser contre le mur (tous les murs sont paralèles aux axes) */

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y - dist.y, m_camera.getPos ().z)); // on ajoute des Y
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y + dist.y, m_camera.getPos ().z)); // on retourne en arière

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x - dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on ajoute des X
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x + dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on retourne en arière
   }
}

void Main::go_left (const std::array <bool, 2500> colision_grid) {

   glm::vec3 dist = m_camera.go_left (); // la cam va en avant

   if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) { // si collision

      m_camera.go_right (); // elle revient en arrière

         /* on la fait glisser contre le mur (tous les murs sont paralèles aux axes) */

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y + dist.y, m_camera.getPos ().z)); // on ajoute des Y
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y - dist.y, m_camera.getPos ().z)); // on retourne en arière

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x + dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on ajoute des X
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x - dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on retourne en arière
   }
}

void Main::go_right (const std::array <bool, 2500> colision_grid) {

   glm::vec3 dist = m_camera.go_right (); // la cam va en avant

   if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) { // si collision

      m_camera.go_left (); // elle revient en arrière

         /* on la fait glisser contre le mur (tous les murs sont paralèles aux axes) */

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y - dist.y, m_camera.getPos ().z)); // on ajoute des Y
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y + dist.y, m_camera.getPos ().z)); // on retourne en arière

      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x - dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on ajoute des X
      if (colision_grid [50 * (25 + (size_t)m_camera.getPos ().y) + (25 + (size_t)m_camera.getPos ().x)]) // si collision
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x + dist.x, m_camera.getPos ().y, m_camera.getPos ().z)); // on retourne en arière
   }
}


void Main::jump () {
   V_z += 0.50f;
   m_ticks_last_jump = SDL_GetTicks ();
}


void Main::accroupir () {

   if (!m_camera.get_is_down () && (m_camera.get_ticks_down () == 0 || m_camera.get_ticks_down () + 300 < SDL_GetTicks ())) {
      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y, m_camera.getPos ().z - 1.0f)); // s'accroupir
      m_camera.set_down (true);
      m_camera.set_ticks_down (SDL_GetTicks ());
   }
   else if ((m_camera.get_ticks_down () == 0 || m_camera.get_ticks_down () + 300 < SDL_GetTicks ())) {
      m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y, m_camera.getPos ().z + 1.0f)); // se desaccroupir
      m_camera.set_down (false);
      m_camera.set_ticks_down (SDL_GetTicks ());
   }
}

bool Main::tomber () {

   V_z -= 0.03f;
   m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y, m_camera.getPos ().z + V_z)); // on tombe, ou ou monte selon si on est sur le début ou la fin du saut

   if (m_camera.get_is_down ()) { // si accroupi
      if (m_camera.getPos ().z < 1.0f) { // si peux tomber

         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y, 1.0f)); // on tombe, ou ou monte selon si on est sur le début ou la fin du saut
         V_z = 0.0f;

         return false;
      }
      else return true;
   }
   else { // si debout
      if (m_camera.getPos ().z < 2.0f) { // si peux tomber

         V_z = 0.0f;
         m_camera.setPosition (glm::vec3 (m_camera.getPos ().x, m_camera.getPos ().y, 2.0f)); // on tombe, ou ou monte selon si on est sur le début ou la fin du saut

         return false;
      }
      else return true;
   }

   return false;
}


