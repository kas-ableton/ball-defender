#pragma once

#include "Point.hpp"
#include "Subject.hpp"

namespace bd {

class PointSubject : public Point, public Subject {
public:
  PointSubject(int _x, int _y);
  PointSubject(Point&& point);

private:
};

} // namespace bd
