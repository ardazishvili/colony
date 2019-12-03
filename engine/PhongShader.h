#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "Shader.h"

class PhongShader : public Shader{
public:
  PhongShader(const GLchar* vertexPath, const GLchar* fragmentPath);

  void configure(glm::vec3 lightPosition,
		 glm::vec3 cameraPosition,
		 glm::mat4 view,
		 glm::mat4 projection);
private:

};

#endif
