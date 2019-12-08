#include "Terrain.h"

Terrain::Terrain(Shader& shader,
                 float bottomLeftX,
                 float bottomLeftY,
                 float topRightX,
                 float topRightY,
                 int divisions) :
  _shader(shader)
{
  _mesh.initTerrain(
    0, 0, topRightX - bottomLeftX, topRightY - bottomLeftY, divisions);
  _offset.x = bottomLeftX;
  _offset.y = bottomLeftY;
}

void Terrain::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, _offset);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);
  _mesh.render();
}

glm::vec3 Terrain::getXYZ(glm::vec2 xy) const
{
  return glm::vec3(xy.x, xy.y, _mesh.getZ(xy.x - _offset.x, xy.y - _offset.y));
}
