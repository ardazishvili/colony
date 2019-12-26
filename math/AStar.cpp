#include <iomanip>

#include "../globals.h"
#include "AStar.h"

AStar::AStar(const std::vector<VertexColor>& v,
             const std::vector<bool>& o,
             SegmentDimensions sd) :
  _v(v),
  _o(o), _sd(sd)
{
  std::cout << "v.size= " << v.size() << std::endl;
  /* ANode node[sd.divisionsX + 1][sd.divisionsY + 1]; */
  /* for (unsigned int i = 0; i < sd.divisionsX + 1; ++i) { */
  /*   for (unsigned int j = 0; j < sd.divisionsY + 1; ++j) { */
  /*     node[i][j].x = v.at(i * sd.latticeWidth + j).p.x; */
  /*     node[i][j].y = v.at(i * sd.latticeWidth + j).p.y; */
  /*     if (o.at(i * sd.latticeWidth + j)) { */
  /*       node[i][j].isObstacle = true; */
  /*     } */
  /*   } */
  /* } */

  /* for (unsigned int i = 0; i < sd.divisionsX + 1; ++i) { */
  /*   for (unsigned int j = 0; j < sd.divisionsY + 1; ++j) { */
  /*     std::cout << setw(15) << setprecision(3) << "(" << node[i][j].x << ","
   */
  /*               << node[i][j].y << ")" << node[i][j].isObstacle << " "; */
  /*   } */
  /*   std::cout << std::endl; */
  /* } */
}

APath AStar::getPath(glm::vec2 s, glm::vec2 e)
{
  s.x += _sd.xOffset;
  s.y += _sd.yOffset;
  e.x += _sd.xOffset;
  e.y += _sd.yOffset;
  auto result = APath();
  std::cout << "_sd.divisionsX= " << _sd.divisionsX << std::endl;
  std::cout << "_sd.divisionsY= " << _sd.divisionsY << std::endl;
  std::cout << "_sd.latticeWidth= " << _sd.latticeWidth << std::endl;

  unsigned int sxi = s.x / _sd.xStep;
  unsigned int syi = s.y / _sd.yStep;
  std::cout << "sxi= " << sxi << std::endl;
  std::cout << "syi= " << syi << std::endl;
  unsigned int exi = e.x / _sd.xStep;
  unsigned int eyi = e.y / _sd.yStep;
  std::cout << "exi= " << exi << std::endl;
  std::cout << "eyi= " << eyi << std::endl;

  return result;
}

float AStar::h(glm::vec2 c, glm::vec2 goal)
{
  return glm::distance(c, goal);
}
