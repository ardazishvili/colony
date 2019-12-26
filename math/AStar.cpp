#include <iomanip>

#include "../globals.h"
#include "AStar.h"

void AStar::init(const std::vector<VertexColor>& v,
                 const std::vector<bool>& o,
                 SegmentDimensions sd)
{
  std::cout << "sd.divisionsX= " << sd.divisionsX << std::endl;
  std::cout << "sd.divisionsY= " << sd.divisionsY << std::endl;
  std::cout << "sd.latticeWidth= " << sd.latticeWidth << std::endl;
  std::cout << "v.size= " << v.size() << std::endl;
  ANode node[sd.divisionsX + 1][sd.divisionsY + 1];
  for (unsigned int i = 0; i < sd.divisionsX + 1; ++i) {
    for (unsigned int j = 0; j < sd.divisionsY + 1; ++j) {
      node[i][j].x = v.at(i * sd.latticeWidth + j).p.x;
      node[i][j].y = v.at(i * sd.latticeWidth + j).p.y;
      if (o.at(i * sd.latticeWidth + j)) {
        node[i][j].isObstacle = true;
      }
    }
  }

  for (unsigned int i = 0; i < sd.divisionsX + 1; ++i) {
    for (unsigned int j = 0; j < sd.divisionsY + 1; ++j) {
      std::cout << setw(15) << setprecision(3) << "(" << node[i][j].x << ","
                << node[i][j].y << ")" << node[i][j].isObstacle << " ";
    }
    std::cout << std::endl;
  }
}
