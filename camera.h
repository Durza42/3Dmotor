#ifndef DEF_CAMERA
 #define DEF_CAMERA

 #include <glm/glm.hpp>
 #include <glm/gtx/transform.hpp>
 #include <glm/gtc/type_ptr.hpp>

 #include "Input.h"


class Camera {

  public:

   Camera();
   Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical, float sensibilite, float vitesse);
   ~Camera();
   void orienter(int xRel, int yRel);
   void lookAt(glm::mat4 &modelview);
   void setPointcible(glm::vec3 pointCible);
   void setPosition(glm::vec3 position);
   float getSensibilite() const;
   float getVitesse() const;
   void setSensibilite(float sensibilite);
   void setVitesse(float vitesse);
   glm::vec3 getPos () const;
   glm::vec3 go_on ();
   glm::vec3 go_back ();
   glm::vec3 go_right ();
   glm::vec3 go_left ();
   bool get_is_jumping () const;
   bool get_is_down () const;
   long unsigned int get_ticks_down () const;
   void set_down (bool value);
   void set_ticks_down (const long unsigned int value);

  private:

   float m_phi;
   float m_theta;

   glm::vec3 m_orientation;
   glm::vec3 m_axeVertical;
   glm::vec3 m_deplacementLateral;
   glm::vec3 m_position;
   glm::vec3 m_pointCible;

   float m_sensibilite;
   float m_vitesse;

   bool m_is_jumping; // true if is jumping
   bool m_is_down; // si accroupit
   long unsigned int m_ticks_down; // contient le moment de l'accroupissement
};


#endif
