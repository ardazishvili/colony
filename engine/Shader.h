#ifndef SHADER_H

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
  static const unsigned int MAX_BONES = 100;
  Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

  void init();
  void use();
  void setBool(const std::string& name, bool value) const;
  void setInt(const std::string& name, int value) const;
  void setFloat(const std::string& name, float value) const;
  void setColor(const std::string& name, float value) const;
  void setVec3(const std::string& name, float f1, float f2, float f3) const;
  void setVec3(const std::string& name, glm::vec3& value) const;
  void setTransformation(const std::string& name, const GLfloat* matrix) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;
 
  GLint getUniformLocation(const char* name);
  void setBoneTransform(unsigned int index,
  	       			const glm::mat4& matrix);
private:
  unsigned int _id;
  GLuint m_boneLocation[MAX_BONES];
};

#define SHADER_H
#endif
