#include "Vector.hpp"

#include "Point.hpp"

#include <cmath>

namespace bd {
Vector::Vector(Point&& startPos, Point&& endPos)
{
  int xMove = startPos.x() - endPos.x();
  int yMove = startPos.y() - endPos.y();

  // length of the vector
  auto r = std::sqrt(xMove * xMove + yMove * yMove);

  // get normalized values of x and y
  yDelta = yMove / r;
  xDelta = xMove / r;
}
}
