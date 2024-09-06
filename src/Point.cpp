#include "Point.hpp"

namespace bd {
Point::Point()
    : x(std::numeric_limits<int>::max()), y(std::numeric_limits<int>::max()) {}

Point::Point(int _x, int _y) : x(_x), y(_y) {}

} // namespace bd
