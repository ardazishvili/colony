#ifndef VIEW_H
#define VIEW_H

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class View
{
public:
  static float VIEW_SCALE;

protected:
  bool _hasAnimation{ false };
};

#endif
