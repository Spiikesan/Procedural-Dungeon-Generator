#ifndef _BOX_HH_
# define _BOX_HH_

#include "Edge.hh"

struct Box
{
  float x;
  float y;
  float width;
  float height;

  Box();
  Box(const Box &other);
  Box(float _x, float _y, float _width, float _height);
  ~Box();
  Box &operator=(const Box &other);
  bool collision(const Box &other) const;
  bool collision(const Edge &other) const;
  void	moveContact(const Box &other, const Point &dir);
  float left() const;
  float top() const;
  float right() const;
  float bottom() const;
};

#endif /* ! _BOX_HH_ */
