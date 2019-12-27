#include <iomanip>
#include <map>
#include <set>

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

  unsigned int sxi = s.x / _sd.xStep;
  unsigned int syi = s.y / _sd.yStep;
  ANode start = { s, { sxi, syi } };
  unsigned int exi = e.x / _sd.xStep;
  unsigned int eyi = e.y / _sd.yStep;
  ANode end = { e, { exi, eyi } };

  std::set<ANode*> frontier;
  frontier.emplace(&start);
  std::map<ANode*, float> gScore;
  gScore.emplace(&start, 0);
  std::map<ANode*, float> fScore;
  fScore.emplace(&start, h(start.p, end.p));
  std::cout << "fScore.size()= " << fScore.size() << std::endl;
  std::cout << "fScore[&start]= " << fScore[&start] << std::endl;

  while (!frontier.empty()) {
    auto currentIt = std::min_element(
      frontier.begin(), frontier.end(), [&fScore](ANode* lhs, ANode* rhs) {
        return fScore[lhs] < fScore[rhs];
      });
    auto current = *currentIt;

    if (current->integerP == end.integerP) {
      return reconstructPath(current);
    }

    frontier.erase(currentIt);
    auto neighbors = getNeighbors(current);
    for (auto& n : neighbors) {
      std::cout << "n.integerP.x= " << n.integerP.x << std::endl;
      std::cout << "n.integerP.y= " << n.integerP.y << std::endl;
    }
  }

  return reconstructPath(&start);
}

float AStar::h(glm::vec2 c, glm::vec2 goal)
{
  return glm::distance(c, goal);
}

APath AStar::reconstructPath(ANode* node)
{
  return APath();
}

bool operator==(const APoint& lhs, const APoint& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::vector<ANode> AStar::getNeighbors(ANode* current)
{
  struct Offset
  {
    int x;
    int y;
  };
  std::vector<Offset> offsets = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
  std::vector<ANode> res;
  for (auto& offset : offsets) {

    unsigned int i = current->integerP.x + offset.x;
    unsigned int j = current->integerP.y + offset.y;
    if (!_o.at(i * _sd.latticeWidth + j)) {
      float x = _v.at(i * _sd.latticeWidth + j).p.x;
      float y = _v.at(i * _sd.latticeWidth + j).p.y;
      ANode node = { glm::vec2(x, y), { i, j } };
      res.push_back(node);
    }
  }
  return res;
}
