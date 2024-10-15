#include "Rect.hpp"

#include <optional>

namespace bd {

std::ostream& operator<<(std::ostream& os, const Rect& rect) {
  return os << rect.top() << ", " << rect.left() << ", " << rect.bottom()
            << ", " << rect.right() << "\n";
}

Rect::Rect(const Point& _topLeft, int height, int width)
    : topLeft(_topLeft),
      bottomRight(_topLeft.x() + width, _topLeft.y() + height) {}

Rect::Rect(const Point& _topLeft, int side) : Rect(_topLeft, side, side) {}

int Rect::top() const { return topLeft.y(); }
int Rect::bottom() const { return bottomRight.y(); }
int Rect::left() const { return topLeft.x(); }
int Rect::right() const { return bottomRight.x(); }

int Rect::height() const { return bottom() - top(); }
int Rect::width() const { return right() - left(); }

bool Rect::intersects(const Rect& other) {
  return left() <= other.right() && right() >= other.left() &&
         // y-axis 0 is the top
         top() <= other.bottom() && bottom() >= other.top();
}

bool Rect::contains(const Point& point) {
  return left() <= point.x() && point.x() <= right() && top() >= point.y() &&
         bottom() <= point.y();
}

std::optional<Rect> Rect::overlap(const Rect& other) {
  if (!intersects(other)) {
    return std::nullopt;
  }
  auto horizDist = std::min(right() - other.left(), other.right() - left());
  auto vertDist = std::min(bottom() - other.top(), other.bottom() - top());

  const auto point = Point{0, 0};
  return std::make_optional(Rect{point, vertDist, horizDist});
}

void Rect::shiftX(int value) {
  topLeft.setX(topLeft.x() + value);
  bottomRight.setX(bottomRight.x() + value);
}

void Rect::shiftY(int value) {
  topLeft.setY(topLeft.y() + value);
  bottomRight.setY(bottomRight.y() + value);
}

} // namespace bd
