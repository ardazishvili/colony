#ifndef SURFACE_H
#define SURFACE_H

#include "Camera.h"
#include "PlainMesh.h"
#include "Shader.h"

class Surface
{
public:
  Surface(Camera& camera,
          Shader& shader,
          float bottomLeftX,
          float bottomLeftY,
          float topRightX,
          float topRightY,
          int divisions,
          std::string texturePath = "/home/roman/repos/colony/assets/grey.png");
  void render();
  void setOffsetZ(float offset);
  void setOffsetXY(float x, float y);
  void setTexture(const std::string& filename);
  void setScaleX(float factor);
  void setScaleXY(float xFactor, float yFactor);

private:
  Camera& _camera;
  Shader& _shader;
  PlainMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
  float _pitchAngle{ 0.0f };
  float _yawAngle{ 0.0f };
  float _xScaleFactor{ 1.0f };
  float _yScaleFactor{ 1.0f };
  glm::vec2 _bottomLeft;
  glm::vec2 _topRight;
};

#endif
