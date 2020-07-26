#ifndef CANVAS_HH_
#define CANVAS_HH_

#include <vector>
#include <algorithm>
#include "Point.hh"
#include "Color.hh"
#include "Edge.hh"
#include "Square.hh"
#include "Triangle.hh"
#include "Circle.hh"

struct Buffer
{
  int index;
  Point point;
  Color color;
  Buffer();
  Buffer(int _index, const Point &_point, const Color &_color);
  Buffer(const Buffer &other);
  const Buffer &operator=(const Buffer &other);
};

class Canvas
{
private:
  Color default_color;

  static size_t index_points;
  std::vector<Buffer> points;

  static size_t index_edges;
  std::vector<Buffer> edges;

  static size_t index_squares;
  std::vector<Buffer> squares;

  static size_t index_triangles;
  std::vector<Buffer> triangles;

  static size_t index_circles;
  std::vector<Buffer> circles;

  const Canvas &operator=(const Canvas &other) = delete;

public:
  explicit Canvas();
  ~Canvas();
  void draw(Point &point, const Color &color);
  void draw(Edge &edge, const Color &color);
  void draw(Square &square, const Color &color);
  void draw(Triangle &triangle, const Color &color);
  void draw(Circle &circle, const Color &color);

  void draw(Point &point);
  void draw(Edge &edge);
  void draw(Square &square);
  void draw(Triangle &triangle);
  void draw(Circle &circle);

  void draw(const Point &point, const Color &color);
  void draw(const Edge &edge, const Color &color);
  void draw(const Square &square, const Color &color);
  void draw(const Triangle &triangle, const Color &color);
  void draw(const Circle &circle, const Color &color);

  void draw(const Point &point);
  void draw(const Edge &edge);
  void draw(const Square &square);
  void draw(const Triangle &triangle);
  void draw(const Circle &circle);

  void remove(Point &point);
  void remove(Edge &edge);
  void remove(Square &square);
  void remove(Triangle &triangle);
  void remove(Circle &circle);

  void setDefaultColor(const Color &color);
  const Color &getDefaultColor() const;

  void renderer();
  void clear();
};

#endif // CANVAS_H_
