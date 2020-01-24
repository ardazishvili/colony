#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Camera.h"

class Light;
class Shader
{
public:
  static const unsigned int MAX_BONES = 100;
  Shader(Light* light,
         Camera& camera,
         glm::mat4& view,
         glm::mat4& projection,
         const GLchar* vertexPath,
         const GLchar* fragmentPath);
  virtual ~Shader() = default;
  Shader(const Shader&) = delete;
  Shader(Shader&&) = delete;
  Shader& operator=(const Shader&) = delete;
  Shader& operator=(Shader&&) = delete;

  void init();
  void use();
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
  void setColor(const std::string& name, float value) const;
  void setVec3(const std::string& name, float f1, float f2, float f3) const;
  void setVec3(const std::string& name, glm::vec3& value) const;
  void setVec4(const std::string& name, glm::vec4& value) const;
  void setVec2(const std::string& name, glm::vec2& value) const;
  void setTransformation(const std::string& name, const GLfloat* matrix) const;
  void setMat4(const std::string& name, const glm::mat4& mat) const;
  Camera& camera();

  GLint getUniformLocation(const char* name);
  void setBoneTransform(unsigned int index, const glm::mat4& matrix);
  virtual void configure() = 0;

protected:
  unsigned int _id;
  Light* _light;
  Camera& _camera;
  glm::mat4& _view;
  glm::mat4& _projection;

private:
  GLuint m_boneLocation[MAX_BONES];
};

#endif
