#include <iomanip>
#include <set>

#include "../globals.h"
#include "AStar.h"

AStar::AStar(const std::vector<VertexColor>& v,
             const std::vector<bool>& o,
             SegmentDimensions sd) :
  _v(v),
  _o(o), _sd(sd)
{
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
  auto start = std::make_shared<ANode>(s, APoint{ sxi, syi });
  unsigned int exi = e.x / _sd.xStep;
  unsigned int eyi = e.y / _sd.yStep;
  auto end = std::make_shared<ANode>(e, APoint{ exi, eyi });
  start->g = 0;
  start->f = start->g + h(start->p, end->p);

  std::set<std::shared_ptr<ANode>> frontier;
  frontier.emplace(start);
  std::set<std::shared_ptr<ANode>> closed;
  std::cout << "sta position: (" << start->integerP.x << ", "
            << start->integerP.y << ")" << std::endl;
  std::cout << "end position: (" << end->integerP.x << ", " << end->integerP.y
            << ")" << std::endl;

  auto iterations = 0;
  while (!frontier.empty()) {
    auto currentIt = std::min_element(
      frontier.begin(),
      frontier.end(),
      [](std::shared_ptr<ANode> lhs, std::shared_ptr<ANode> rhs) {
        return lhs->f < rhs->f;
      });
    auto current = *currentIt;

    if (current->integerP == end->integerP) {
      return reconstructPath(current.get());
    }

    closed.insert(current);
    frontier.erase(currentIt);
    auto neighbors = getNeighbors(current.get());
    for (auto& n : neighbors) {
      auto tmp = current->g + 0.01;
      auto fIt = std::find_if(
        frontier.begin(), frontier.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      if (fIt != frontier.end() && tmp < (*fIt)->g) {
        frontier.erase(fIt);
      }
      auto cIt = std::find_if(
        closed.begin(), closed.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      if (cIt != closed.end() && tmp < (*cIt)->g) {
        closed.erase(cIt);
      }
      fIt = std::find_if(
        frontier.begin(), frontier.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      cIt = std::find_if(
        closed.begin(), closed.end(), [&n](std::shared_ptr<ANode> node) {
          return (node->integerP == n.integerP);
        });
      if (fIt == frontier.end() && cIt == closed.end()) {
        auto a = std::make_shared<ANode>(n);
        a->g = tmp;
        a->f = tmp + h(a->p, end->p);
        a->parent = current.get();
        frontier.insert(a);
      }
    }
  }

  std::cout << "FAILURE of ASTAR" << std::endl;
  return APath();
}

float AStar::h(glm::vec2 c, glm::vec2 goal)
{
  return glm::distance(c, goal);
}

APath AStar::reconstructPath(ANode* current)
{
  auto path = APath();
  while (current->parent != nullptr) {
    auto p = glm::vec2(current->p.x - _sd.xOffset, current->p.y - _sd.yOffset);
    path.push_back(p);
    current = current->parent;
  }

  return path;
}

bool operator==(const APoint& lhs, const APoint& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::vector<ANode> AStar::getNeighbors(const ANode* const current)
{
  auto cx = current->integerP.x;
  auto cy = current->integerP.y;
  struct Offset
  {
    int x;
    int y;
  };
  std::vector<Offset> offsets = { { -1, 0 },  { 1, 0 },  { 0, -1 }, { 0, 1 },
                                  { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 } };
  std::vector<ANode> res;
  for (auto& offset : offsets) {

    unsigned int i = cx + offset.x;
    unsigned int j = cy + offset.y;
    if (!_o.at(i * _sd.latticeWidth + j)) {
      float x = _v.at(i * _sd.latticeWidth + j).p.x;
      float y = _v.at(i * _sd.latticeWidth + j).p.y;
      auto n = ANode(glm::vec2(x, y), APoint(i, j));
      res.push_back(n);
    }
  }
  return res;
}
