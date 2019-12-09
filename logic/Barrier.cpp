#include "Barrier.h"

Barrier::Barrier(Shader& textureShader,
                 Shader& colorShader,
                 glm::vec3 position) :
  _view(textureShader, colorShader, position)
{}

void Barrier::render()
{
  _view.draw();
}

void Barrier::assignVertices(Terrain* terrain)
{
  /* _vertices = terrain->getVertices(_view.position(), _radius); */
  /* std::cout << "_vertices.size()= " << _vertices.size() << std::endl; */
  /* for (auto& index : _vertices) { */
  /*   terrain->updateColor(index); */
  /* } */
}
