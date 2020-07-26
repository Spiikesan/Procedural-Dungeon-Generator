#include "Square.hh"

Square::Square()
    : GObject(), box()
{
}

Square::Square(float x, float y, float width, float height)
    : GObject(), box(x, y, width, height)
{
}

Square::Square(const Square &other)
    : GObject(other), box(other.box)
{
}

Square::~Square()
{
}

const Square &Square::operator=(const Square &other)
{
  if (this != &other)
  {
    GObject::operator=(other);
    box = other.box;
  }
  return (*this);
}

void Square::move(const Point &dir, float speed)
{
  box.x += dir.x * speed;
  box.y += dir.y * speed;
}

Point Square::getCenter() const
{
  return (Point(box.x, box.y));
}
