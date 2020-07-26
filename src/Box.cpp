#include "Box.hh"
#include "Util.hh"

Box::Box()
    : x(0), y(0), width(0), height(0)
{
}

Box::Box(const Box &other)
    : x(other.x), y(other.y), width(other.width), height(other.height)
{
}

Box::Box(float _x, float _y, float _width, float _height)
    : x(_x), y(_y), width(_width), height(_height)
{
}

Box::~Box()
{
}

Box &Box::operator=(const Box &other)
{
  if (this != &other)
  {
    x = other.x;
    y = other.y;
    width = other.width;
    height = other.height;
  }
  return (*this);
}

bool Box::collision(const Box &other) const
{
  return (this != &other &&
          left() < other.right() &&
          other.left() < right() &&
          top() < other.bottom() &&
          other.top() < bottom());
}

bool Box::collision(const Edge &other) const
{
  float _left = left();
  float _right = right();
  float _top = top();
  float _bottom = bottom();

  if ((other.p1.x <= _left && other.p2.x <= _left) ||
      (other.p1.y <= _top && other.p2.y <= _top) ||
      (other.p1.x >= _right && other.p2.x >= _right) ||
      (other.p1.y >= _bottom && other.p2.y >= _bottom))
    return (false);
  if ((other.p1.x > _left && other.p1.x < _right && other.p1.y > _top && other.p1.y < _bottom) ||
      (other.p2.x > _left && other.p2.x < _right && other.p2.y > _top && other.p2.y < _bottom))
    return (true);
  float m = (other.p2.y - other.p1.y) / (other.p2.x - other.p1.x);
  float y = m * (_left - other.p1.x) + other.p1.y;
  if (y > _top && y < _bottom)
    return (true);

  y = m * (_bottom - other.p1.x) + other.p1.y;
  if (y > _top && y < _bottom)
    return (true);

  float x = (_top - other.p1.y) / m + other.p1.x;
  if (x > _left && x < _right)
    return (true);

  x = (_top - other.p1.y) / m + other.p1.x;
  if (x > _left && x < _right)
    return (true);

  return (false);
}

void Box::moveContact(const Box &other, const Point &dir)
{
  if (left() < other.right() ||
      other.left() < right())
  {
    x += dir.x;
  }
  if (top() < other.bottom() ||
      other.top() < bottom())
  {
    y += dir.y;
  }
}

float Box::left() const
{
  return (x - width / 2.0);
}

float Box::top() const
{
  return (y - height / 2.0);
}

float Box::right() const
{
  return (x + width / 2.0);
}

float Box::bottom() const
{
  return (y + height / 2.0);
}
