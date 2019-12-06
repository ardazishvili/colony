#ifndef TERRAIN_H
#define TERRAIN_H

#include "Shader.h"
#include "TerrainMesh.h"

class Terrain
{
public:
  Terrain(Shader& shader,
          float bottomLeftX,
          float bottomLeftY,
          float topRightX,
          float topRightY,
          int divisions);
  void render();
  void setOffsetZ(float offset);
  void setOffsetXY(float x, float y);
  void setPitchAngle(float angle);
  void setYawAngle(float angle);
  void setScaleX(float factor);
  void setScaleXY(float xFactor, float yFactor);
  glm::vec4 getArea() const; // bottom left x, y; top right x, y

private:
  Shader& _shader;
  TerrainMesh _mesh;
  glm::vec3 _offset{ glm::vec3(0.0f) };
  float _pitchAngle{ 0.0f };
  float _yawAngle{ 0.0f };
  float _xScaleFactor{ 1.0f };
  float _yScaleFactor{ 1.0f };
  glm::vec2 _bottomLeft;
  glm::vec2 _topRight;
};

#endif
