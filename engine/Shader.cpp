#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a) / sizeof(a[0]))

Shader::Shader(Light* light,
               Camera& camera,
               glm::mat4& view,
               glm::mat4& projection,
               const GLchar* vertexPath,
               const GLchar* fragmentPath) :
  _light(light),
  _camera(camera), _view(view), _projection(projection)
{
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vertexShaderFile;
  std::ifstream fragmentShaderFile;
  vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    vertexShaderFile.open(vertexPath);
    std::stringstream vertexShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();
    vertexShaderFile.close();
    vertexCode = vertexShaderStream.str();

    fragmentShaderFile.open(fragmentPath);
    std::stringstream fragmentShaderStream;
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    fragmentShaderFile.close();
    fragmentCode = fragmentShaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cout << " shader file is not loaded " << std::endl;
  }

  const char* vertexShaderCode = vertexCode.c_str();
  const char* fragmentShaderCode = fragmentCode.c_str();

  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
  glCompileShader(vertex);
  int success = -1;
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  char infoLog[512];
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cout << "SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cout << "SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  _id = glCreateProgram();
  glAttachShader(_id, vertex);
  glAttachShader(_id, fragment);
  glLinkProgram(_id);
  glGetProgramiv(_id, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(_id, 512, NULL, infoLog);
    std::cout << "SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  init();
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::use()
{
  glUseProgram(_id);
}

void Shader::setBool(const std::string& name, bool value) const
{
  glUniform1i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string& name, int value) const
{
  glUniform1i(glGetUniformLocation(_id, name.c_str()), static_cast<int>(value));
}

void Shader::setFloat(const std::string& name, float value) const
{
  glUniform1f(glGetUniformLocation(_id, name.c_str()),
              static_cast<float>(value));
}

void Shader::setColor(const std::string& name, float value) const
{
  glUniform4f(glGetUniformLocation(_id, name.c_str()), 0.0, value, 0.0f, 1.0f);
}

void Shader::setTransformation(const std::string& name,
                               const GLfloat* matrix) const
{
  glUniformMatrix4fv(
    glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, matrix);
}

void Shader::setVec3(const std::string& name,
                     float f1,
                     float f2,
                     float f3) const
{
  glUniform3f(glGetUniformLocation(_id, name.c_str()), f1, f2, f3);
}

void Shader::setVec3(const std::string& name, glm::vec3& value) const
{
  glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
  glUniformMatrix4fv(
    glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::init()
{
  for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(m_boneLocation); i++) {
    char Name[128];
    memset(Name, 0, sizeof(Name));
    snprintf(Name, sizeof(Name), "gBones[%d]", i);
    m_boneLocation[i] = getUniformLocation(Name);
  }
}

void Shader::setBoneTransform(unsigned int index, const glm::mat4& matrix)
{
  assert(index < MAX_BONES);
  glUniformMatrix4fv(m_boneLocation[index], 1, GL_TRUE, glm::value_ptr(matrix));
}

GLint Shader::getUniformLocation(const char* name)
{
  GLuint location = glGetUniformLocation(_id, name);

  if (location == GL_INVALID_VALUE || location == GL_INVALID_OPERATION) {
    fprintf(stderr, "Unable to get the location of uniform '%s'\n", name);
  }

  return location;
}

Camera& Shader::camera()
{
  return _camera;
}
