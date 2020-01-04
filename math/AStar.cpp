#include <iomanip>

#include "../globals.h"
#include "AStar.h"

const unsigned int AStar::MAX_ITER = 2000;

AStar::AStar(const std::vector<VertexColor>& v,
             const std::vector<bool>& o,
             SegmentDimensions sd) :
  _v(v),
  _o(o), _sd(sd)
{
}

std::optional<APath> AStar::getPath(glm::vec2 s, glm::vec2 e)
{
  /* s.x += _sd.xOffset; */
  /* s.y += _sd.yOffset; */
  /* e.x += _sd.xOffset; */
  /* e.y += _sd.yOffset; */
  /* std::cout << "s.x= " << s.x << std::endl; */
  /* std::cout << "s.y= " << s.y << std::endl; */
  /* std::cout << "e.x= " << e.x << std::endl; */
  /* std::cout << "e.y= " << e.y << std::endl; */
  auto result = APath();
  _cache.clear();

  /* unsigned int sxi = s.x / _sd.xStep; */
  /* unsigned int syi = s.y / _sd.yStep; */
  int sxi = s.x / _sd.xStep;
  int syi = s.y / _sd.yStep;
  /* std::cout << "sxi= " << sxi << std::endl; */
  /* std::cout << "syi= " << syi << std::endl; */
  auto start = std::make_shared<ANode>(s, APoint{ sxi, syi });
  _cache.emplace(start);
  /* unsigned int exi = e.x / _sd.xStep; */
  /* unsigned int eyi = e.y / _sd.yStep; */
  int exi = e.x / _sd.xStep;
  int eyi = e.y / _sd.yStep;
  auto end = std::make_shared<ANode>(e, APoint{ exi, eyi });
  start->g = 0;
  start->f = start->g + h(start->p, end->p);

  auto comp = [](const std::shared_ptr<ANode>& lhs,
                 const std::shared_ptr<ANode>& rhs) {
    return lhs->f < rhs->f;
  };
  auto frontier = std::set<std::shared_ptr<ANode>, decltype(comp)>(comp);
  frontier.emplace(start);
  std::set<std::shared_ptr<ANode>> closed;

  unsigned int it = 0;
  while (!frontier.empty()) {
    ++it;
    // TODO add more elegant solution
    if (it > MAX_ITER) {
      break;
    }
    auto currentIt = frontier.begin();
    auto current = *currentIt;

    if (current->integerP == end->integerP) {
      return reconstructPath(current.get());
    }

    closed.insert(current);
    frontier.erase(currentIt);
    std::cout << "current->integerP.x= " << current->integerP.x << std::endl;
    std::cout << "current->integerP.y= " << current->integerP.y << std::endl;
    auto neighbors = getNeighbors(current.get());
    for (auto& n : neighbors) {
      auto tmp = current->g + _sd.xStep;
      auto fIt = frontier.find(n);
      if (fIt != frontier.end() && tmp < (*fIt)->g) {
        frontier.erase(fIt);
      }
      auto cIt = closed.find(n);
      if (cIt != closed.end() && tmp < (*cIt)->g) {
        closed.erase(cIt);
      }
      if (fIt == frontier.end() && cIt == closed.end()) {
        n->g = tmp;
        n->f = tmp + h(n->p, end->p);
        n->parent = current.get();
        frontier.insert(n);
      }
    }
  }

  return std::nullopt;
}

float AStar::h(glm::vec2 c, glm::vec2 goal)
{
  return glm::distance(c, goal);
}

APath AStar::reconstructPath(ANode* current)
{
  auto path = APath();
  while (current->parent != nullptr) {
    auto p = glm::vec2(current->p.x, current->p.y);
    path.push_back(p);
    current = current->parent;
  }

  return path;
}

bool operator==(const APoint& lhs, const APoint& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::vector<std::shared_ptr<ANode>> AStar::getNeighbors(
  const ANode* const current)
{
  /* auto cx = current->integerP.x; */
  /* auto cy = current->integerP.y; */
  auto cx = current->integerP.x;
  auto cy = current->integerP.y;
  struct Offset
  {
    int x;
    int y;
  };
  std::vector<Offset> offsets = { { -1, 0 },  { 1, 0 },  { 0, -1 }, { 0, 1 },
                                  { -1, -1 }, { -1, 1 }, { 1, -1 }, { 1, 1 } };
  std::vector<std::shared_ptr<ANode>> res;
  for (auto& offset : offsets) {
    /* unsigned int i = cx + offset.x; */
    /* unsigned int j = cy + offset.y; */
    int i = cx + offset.x;
    int j = cy + offset.y;
    // i,j is from (-sd.latticeWidth / 2, sd.latticeWidth /2) range
    std::cout << "cx= " << cx << std::endl;
    std::cout << "cy= " << cy << std::endl;
    std::cout << "_o.size()= " << _o.size() << std::endl;
    std::cout << "_sd.latticeWidth= " << _sd.latticeWidth << std::endl;
    std::cout << "i= " << i << std::endl;
    std::cout << "j= " << j << std::endl << std::endl;
    if (!_o.at((i + _sd.latticeWidth / 2) * _sd.latticeWidth +
               (j + _sd.latticeWidth / 2))) {
      auto it = std::find_if(
        _cache.begin(), _cache.end(), [i, j](std::shared_ptr<ANode> node) {
          return (node->integerP == APoint(i, j));
        });
      if (it == _cache.end()) {
        float x = _v.at((i + _sd.latticeWidth / 2) * _sd.latticeWidth +
                        (j + _sd.latticeWidth / 2))
                    .p.x;
        float y = _v.at((i + _sd.latticeWidth / 2) * _sd.latticeWidth +
                        (j + _sd.latticeWidth / 2))
                    .p.y;
        auto n = std::make_shared<ANode>(glm::vec2(x, y), APoint(i, j));
        _cache.emplace(n);
        res.push_back(n);
      } else {
        res.push_back(*it);
      }
    }
  }
  return res;
}
