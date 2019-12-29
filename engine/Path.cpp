#include "Path.h"
#include "../globals.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const float Path::Z_OFFSET = 0.1;

Path::Path(Shader& shader, AStar* router, glm::vec3 s, glm::vec3 e) :
  LinesObject(shader), _router(router)
{
  _v.clear();
  _i.clear();
  auto route = _router->getPath(glm::vec2(s.x, s.y), glm::vec2(e.x, e.y));
  for (unsigned int i = 0; i < route.size() - 1; ++i) {
    std::cout << "p.x= " << route.at(i).x << std::endl;
    std::cout << "p.y= " << route.at(i).y << std::endl;
    glm::vec3 start{ route.at(i).x, route.at(i).y, s.z + Z_OFFSET };
    _v.push_back(start);
    _i.push_back(i);
    _i.push_back(i + 1);
  }
  glm::vec3 start{ route.at(route.size() - 1).x,
                   route.at(route.size() - 1).y,
                   s.z + Z_OFFSET };
  _v.push_back(start);

  std::cout << "route.size()= " << route.size() << std::endl;
  std::cout << "_v.size()= " << _v.size() << std::endl;
  std::cout << "_i.size()= " << _i.size() << std::endl;

  LinesObject::initBuffers();
  /* clear(); */
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

/* void Path::setUp(glm::vec3 s, glm::vec3 e) */
/* { */
/* s.z += Z_OFFSET; */
/* _v.push_back(s); */
/* e.z += Z_OFFSET; */
/* _v.push_back(e); */
/* _v.clear(); */
/* _i.clear(); */
/* auto route = _router->getPath(glm::vec2(s.x, s.y), glm::vec2(e.x, e.y)); */
/* for (unsigned int i = 0; i < route.size() - 1; ++i) { */
/* std::cout << "p.x= " << p.x << std::endl; */
/* std::cout << "p.y= " << p.y << std::endl; */
/* glm::vec3 start{ route.at(i).x, route.at(i).y, s.z + Z_OFFSET }; */
/* glm::vec3 end{ route.at(i + 1).x, route.at(i + 1).y, s.z + Z_OFFSET }; */
/* _v.push_back(start); */
/* _v.push_back(end); */
/* _i.push_back(i); */
/* _i.push_back(i + 1); */
/* } */
/* glm::vec3 start{ route.at(route.size() - 1).x, */
/*                route.at(route.size() - 1).y, */
/*                s.z + Z_OFFSET }; */
/* _v.push_back(start); */

/* std::cout << "route.size()= " << route.size() << std::endl; */
/* std::cout << "_v.size()= " << _v.size() << std::endl; */
/* std::cout << "_i.size()= " << _i.size() << std::endl; */
/* LinesObject::initBuffers(); */
/* reloadData(); */
/* } */

/* void Path::setStart(glm::vec3 s) */
/* { */
/*   s.z += Z_OFFSET; */
/*   _v.at(0) = s; */
/*   reloadData(); */
/* } */

/* void Path::setEnd(glm::vec3 e) */
/* { */
/*   e.z += Z_OFFSET; */
/*   _v.at(_v.size() - 1) = e; */
/*   reloadData(); */
/* } */

/* void Path::reloadData() */
/* { */
/*   glBindBuffer(GL_ARRAY_BUFFER, _vbo); */
/*   glBufferSubData(GL_ARRAY_BUFFER, */
/*                   sizeof(glm::vec3) * 0, */
/*                   sizeof(glm::vec3) * _v.size(), */
/*                   &_v[0]); */
/* } */
/* void Path::clear() */
/* { */
/*   _v.clear(); */
/* } */

/* bool Path::isSettedUp() const */
/* { */
/*   return !_v.empty(); */
/* } */
