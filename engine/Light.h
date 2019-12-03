#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

class Light {
public:
  Light(glm::vec3 position,
	Shader& _shader,
       	Camera& camera,
	float screenWidth,
	float screenHeight);
  ~Light();
  void render();  
  glm::vec3 position();
                  
private:          
  void init();    

  glm::vec3 _position;
  unsigned int _vao;
  unsigned int _vbo;
  Shader& _shader;
  Camera& _camera;
  glm::mat4 _view;
  glm::mat4 _projection;
  glm::mat4 _model;
};

#endif
