#include "Transform.hh"

bool	Transform::avoidCollision(Square &a, Square &b)
{
  bool	collide(false);

  while (a.box.collision(b.box)) {
    a.box.moveContact(b.box, Point(a.box.x - b.box.x, a.box.y - b.box.y).normalize());
    b.box.moveContact(a.box, Point(b.box.x - a.box.x, b.box.y - a.box.y).normalize());
    collide = true;
  }
  return (collide);
}

void Transform::scatter(std::vector<Square> &squares, std::function<void(void)> func)
{
  bool collide(true);
  while (collide)
    {
      collide = false;
      for (Square &a : squares) {
	for (Square &b : squares)
	  if (avoidCollision(a, b))
	    collide = true;
	 func();
      }
    }
}
