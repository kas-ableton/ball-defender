#include "PointSubject.hpp"

namespace bd {

PointSubject::PointSubject(int _x, int _y) : Point(_x, _y) {}
PointSubject::PointSubject(Point&& point) : Point(point) {}

} // namespace bd
