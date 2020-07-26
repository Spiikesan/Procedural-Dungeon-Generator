#ifndef SQUARE_HH_
#define SQUARE_HH_

#include "GObject.hh"
#include "Box.hh"
#include "Point.hh"

struct Square : GObject
{
  Box box;
  Square();
  Square(float x, float y, float width, float height);
  Square(const Square &other);
  ~Square();
  const Square &operator=(const Square &other);
  void move(const Point &dir, float speed);
  Point getCenter() const;
};

#endif // SQUARE_HH_
