#ifndef TRANSFORM_HH_
# define TRANSFORM_HH_

#include "Square.hh"
#include <vector>
#include <functional>

class Transform
{
private:
  Transform() = delete;
  Transform(const Transform &other) = delete;
  ~Transform() = delete;
  const Transform &operator=(const Transform &other) = delete;
  static bool avoidCollision(Square &a, Square &b);
public:
  static void scatter(std::vector<Square> &squares, std::function<void(void)> func);
};

#endif // TRANSFORM_HH_
