#include "Path.h"
#include "../globals.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float Path::Z_OFFSET = 0.1;

Path::Path(Shader& shader, AStar* router) : LinesObject(shader), _router(router)
{
  _v.clear();
  _i.clear();
}

bool Path::init(glm::vec3 s, glm::vec3 e)
{
  auto route = _router->getPath(glm::vec2(s.x, s.y), glm::vec2(e.x, e.y));
  if (!route) {
    return false;
  }
  _route = *route;
  /* std::reverse(_route.begin(), _route.end()); */
  for (unsigned int i = 0; i < _route.size() - 1; ++i) {
    /* std::cout << "p.x= " << _route.at(i).x << std::endl; */
    /* std::cout << "p.y= " << _route.at(i).y << std::endl; */
    glm::vec3 start{ _route.at(i).x, _route.at(i).y, s.z + Z_OFFSET };
    _v.push_back(start);
    _i.push_back(i);
    _i.push_back(i + 1);
  }
  glm::vec3 start{ _route.at(_route.size() - 1).x,
                   _route.at(_route.size() - 1).y,
                   s.z + Z_OFFSET };
  _v.push_back(start);

  LinesObject::initBuffers();
  return true;
}

APath Path::route() const
{
  return _route;
}

void Path::render()
{
  _shader.use();
  _shader.configure();
  auto model = glm::mat4(1.0f);
  _shader.setTransformation("model", glm::value_ptr(model));
  _shader.setBool("animated", false);

  LinesObject::render();
}

/* void Path::setStart(glm::vec3 s) */
/* { */
/*   s.z += Z_OFFSET; */
/*   _v.at(0) = s; */
/*   reloadData(); */
/* } */

std::shared_ptr<Path> makePath(Shader& shader,
                               AStar* router,
                               glm::vec3 s,
                               glm::vec3 e)
{
  auto path = std::make_shared<Path>(shader, router);
  if (path->init(s, e)) {
    return path;
  }
  return nullptr;
}
