#include "Canvas.hh"
#include <GL/gl.h>

size_t Canvas::index_squares = 0;
size_t Canvas::index_triangles = 0;
size_t Canvas::index_points = 0;
size_t Canvas::index_edges = 0;
size_t Canvas::index_circles = 0;


Buffer::Buffer()
: index(0), point(), color()
{

}

Buffer::Buffer(const Buffer &other)
: index(other.index), point(other.point), color(other.color)
{

}

const Buffer &Buffer::operator=(const Buffer &other)
{
  if (this != &other)
    {
      index = other.index;
      point = other.point;
      color = other.color;
    }
  return (*this);
}

Buffer::Buffer(int _index, const Point &_point, const Color &_color)
 : index(_index), point(_point), color(_color)
{
}


Canvas::Canvas()
: default_color(255, 255, 255, 255)
{

}

Canvas::~Canvas()
{

}

void Canvas::draw(Point &point, const Color &color)
{
  if (point.index < 0)
    {
      points.push_back(Buffer(index_points, point, color));
      point.index = index_points++;
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(points.begin(), points.end(),
							 [&point] (const Buffer &buffer) -> bool {
							 return (point.index == buffer.index);
							 });
      if (found == points.end())
	return ;
      found->point = point;
      found->color = color;
    }
}

void Canvas::draw(Edge &edge, const Color &color)
{
  if (edge.index < 0)
    {
      edges.push_back(Buffer(index_edges, edge.p1, color));
      edges.push_back(Buffer(index_edges, edge.p2, color));
      edge.index = index_edges++;
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(edges.begin(), edges.end(),
							 [&edge] (const Buffer &buffer) -> bool {
							 return (edge.index == buffer.index);
							 });
      if (found == edges.end())
	return ;
      found->point = edge.p1;
      found->color = color;
      (found + 1)->point = edge.p2;
      (found + 1)->color = color;
    }
}

void Canvas::draw(Square &square, const Color &color)
{
  if (square.index < 0)
    {
      squares.push_back(Buffer(index_squares, Point(square.box.left(), square.box.top()),
			       color));
      squares.push_back(Buffer(index_squares, Point(square.box.right(), square.box.top()),
                               color));
      squares.push_back(Buffer(index_squares, Point(square.box.right(), square.box.bottom()),
			       color));
      squares.push_back(Buffer(index_squares, Point(square.box.left(), square.box.bottom()),
			       color));
      square.index = index_squares++;
    }
  else
    {
     std::vector<Buffer>::iterator found = std::find_if(squares.begin(), squares.end(),
							[&square] (const Buffer &buffer) -> bool {
							return (square.index == buffer.index);
                                                   });
     if (found == squares.end())
	return ;
     found->point.x = square.box.left();
     found->point.y = square.box.top();
     found->color = color;
     (found + 1)->point.x = square.box.right();
     (found + 1)->point.y = square.box.top();
     (found + 1)->color = color;
     (found + 2)->point.x = square.box.right();
     (found + 2)->point.y = square.box.bottom();
     (found + 2)->color = color;
     (found + 3)->point.x = square.box.left();
     (found + 3)->point.y = square.box.bottom();
     (found + 3)->color = color;
    }
}

void Canvas::draw(Triangle &triangle, const Color &color)
{
  if (triangle.index < 0)
    {
      triangles.push_back(Buffer(index_triangles, triangle.p1, color));
      triangles.push_back(Buffer(index_triangles, triangle.p2, color));
      triangles.push_back(Buffer(index_triangles, triangle.p3, color));
      triangle.index = index_triangles++;
    }
  else
    {
     std::vector<Buffer>::iterator found = std::find_if(triangles.begin(), triangles.end(),
							[&triangle] (const Buffer &buffer) -> bool {
							return (triangle.index == buffer.index);
                                                   });
     if (found == triangles.end())
	return ;
     found->point.x = triangle.p1.x;
     found->point.y = triangle.p1.y;
     found->color = color;
     (found + 1)->point.x = triangle.p2.x;
     (found + 1)->point.y = triangle.p2.y;
     (found + 1)->color = color;
     (found + 2)->point.x = triangle.p3.x;
     (found + 2)->point.y = triangle.p3.y;
     (found + 2)->color = color;
    }
}

void Canvas::draw(Circle &circle, const Color &color)
{
  if (circle.index < 0)
    {
      for (int i = 0; i < 360; ++i)
	{
	  float angleToRad = i * 2.0 * M_PI / 360;
	  circles.push_back(Buffer(index_circles, Point(circle.center.x + cos(angleToRad) * circle.radius,
							circle.center.y + sin(angleToRad) * circle.radius), color));
	}
      circle.index = index_circles++;
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(circles.begin(), circles.end(),
							 [&circle] (const Buffer &buffer) -> bool {
							   return (circle.index == buffer.index);
							 });
      if (found == circles.end())
	return ;

      for (int i = 0; i < 360; ++i)
	{
	  float angleToRad = i * 2.0 * M_PI / 360;
	  (found + i)->point = Point(circle.center.x + cos(angleToRad) * circle.radius,
					    circle.center.y + cos(angleToRad) * circle.radius);
	  (found + i)->color = color;
	}
    }
}

void Canvas::draw(Point &point)
{
  if (point.index < 0)
    {
      draw(point, default_color);
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(points.begin(), points.end(),
							 [&point] (const Buffer &buffer) -> bool {
							 return (point.index == buffer.index);
							 });
      if (found == points.end())
      	return ;
      draw(point, found->color);
    }
}

void Canvas::draw(Edge &edge)
{
  if (edge.index < 0)
    {
      draw(edge, default_color);
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(edges.begin(), edges.end(),
							 [&edge] (const Buffer &buffer) -> bool {
							 return (edge.index == buffer.index);
							 });
      if (found == edges.end())
	return ;
      draw(edge, found->color);
    }
}

void Canvas::draw(Square &square)
{
  if (square.index < 0)
    {
      draw(square, default_color);
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(squares.begin(), squares.end(),
							 [&square] (const Buffer &buffer) -> bool {
							 return (square.index == buffer.index);
							 });
      if (found == squares.end())
	return ;
      draw(square, found->color);
    }
}

void Canvas::draw(Triangle &triangle)
{
  if (triangle.index < 0)
    {
      draw(triangle, default_color);
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(triangles.begin(), triangles.end(),
							 [&triangle] (const Buffer &buffer) -> bool {
							 return (triangle.index == buffer.index);
							 });
      if (found == squares.end())
	return ;
      draw(triangle, found->color);
    }
}

void Canvas::draw(Circle &circle)
{
  if (circle.index < 0)
    {
      draw(circle, default_color);
    }
  else
    {
      std::vector<Buffer>::iterator found = std::find_if(circles.begin(), circles.end(),
							 [&circle] (const Buffer &buffer) -> bool {
							   return (circle.index == buffer.index);
							 });
      if (found == circles.end())
	return ;
      draw(circle, found->color);
    }
}

void Canvas::draw(const Point &point, const Color &color)
{
  points.push_back(Buffer(-1, point, color));
}

void Canvas::draw(const Edge &edge, const Color &color)
{
  squares.push_back(Buffer(-1, edge.p1, color));
  squares.push_back(Buffer(-1, edge.p2, color));
}

void Canvas::draw(const Square &square, const Color &color)
{
  squares.push_back(Buffer(-1, Point(square.box.left(), square.box.top()),
			   color));
  squares.push_back(Buffer(-1, Point(square.box.right(), square.box.top()),
			   color));
  squares.push_back(Buffer(-1, Point(square.box.right(), square.box.bottom()),
			   color));
  squares.push_back(Buffer(-1, Point(square.box.left(), square.box.bottom()),
			   color));
}

void Canvas::draw(const Triangle &triangle, const Color &color)
{
  squares.push_back(Buffer(-1, triangle.p1, color));
  squares.push_back(Buffer(-1, triangle.p2, color));
  squares.push_back(Buffer(-1, triangle.p3, color));
}

void Canvas::draw(const Circle &circle, const Color &color)
{
  for (int i = 0; i < 360; ++i)
    {
      float angleToRad = i * 2.0 * M_PI / 360;
      circles.push_back(Buffer(-1, Point(circle.center.x + cos(angleToRad) * circle.radius,
					 circle.center.y + sin(angleToRad) * circle.radius), color));
    }
}

void Canvas::draw(const Point &point)
{
  draw(point, default_color);
}

void Canvas::draw(const Edge &edge)
{
  draw(edge, default_color);
}

void Canvas::draw(const Square &square)
{
  draw(square, default_color);
}

void Canvas::draw(const Triangle &triangle)
{
  draw(triangle, default_color);
}

void Canvas::draw(const Circle &circle)
{
  draw(circle, default_color);
}

void Canvas::remove(Point &point)
{
  if (point.index >= 0)
    {
      std::vector<Buffer>::iterator found = std::find_if(points.begin(), points.end(),
							 [&point] (const Buffer &buffer) -> bool {
							 return (point.index == buffer.index);
							 });
      if (found == points.end())
	return ;
      points.erase(found);
      point.index = -1;
    }
}

void Canvas::remove(Edge &edge)
{
  if (edge.index >= 0)
    {
      std::vector<Buffer>::iterator found = std::find_if(edges.begin(), edges.end(),
							 [&edge] (const Buffer &buffer) -> bool {
							 return (edge.index == buffer.index);
							 });
      if (found == edges.end())
	return ;
      edges.erase(found, found + 2);
      edge.index = -1;
    }
}

void Canvas::remove(Square &square)
{
  if (square.index >= 0)
    {
      std::vector<Buffer>::iterator found = std::find_if(squares.begin(), squares.end(),
							 [&square] (const Buffer &buffer) -> bool {
							 return (square.index == buffer.index);
							 });
      if (found == squares.end())
	return ;
      squares.erase(found, found + 4);
      square.index = -1;
    }
}

void Canvas::remove(Triangle &triangle)
{
  if (triangle.index >= 0)
    {
      std::vector<Buffer>::iterator found = std::find_if(triangles.begin(), triangles.end(),
							 [&triangle] (const Buffer &buffer) -> bool {
							 return (triangle.index == buffer.index);
							 });
      if (found == triangles.end())
	return ;
      triangles.erase(found, found + 3);
      triangle.index = -1;
    }
}

void Canvas::remove(Circle &circle)
{
  if (circle.index >= 0)
    {
      std::vector<Buffer>::iterator found = std::find_if(circles.begin(), circles.end(),
							 [&circle] (const Buffer &buffer) -> bool {
							   return (circle.index == buffer.index);
							 });
      if (found == circles.end())
	return ;
      circles.erase(found, found + 360);
      circle.index = -1;
    }
}

void Canvas::setDefaultColor(const Color &color)
{
    default_color = color;
}

const Color &Canvas::getDefaultColor() const
{
  return (default_color);
}

void Canvas::renderer()
{
  glColor3ub(255, 255, 255);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  if (squares.size())
    {
      glVertexPointer(2, GL_FLOAT, sizeof(Buffer), &squares[0].point.x);
      glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Buffer), &squares[0].color.r);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glDrawArrays(GL_QUADS, 0, squares.size());
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  if (triangles.size())
    {
      glVertexPointer(2, GL_FLOAT, sizeof(Buffer), &triangles[0].point.x);
      glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Buffer), &triangles[0].color.r);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glLineWidth(3);
      glDrawArrays(GL_TRIANGLES, 0, triangles.size());
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  if (edges.size())
    {
      glVertexPointer(2, GL_FLOAT, sizeof(Buffer), &edges[0].point.x);
      glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Buffer), &edges[0].color.r);
      glLineWidth(3);
      glDrawArrays(GL_LINES, 0, edges.size());
    }
  if (points.size())
    {
      glVertexPointer(2, GL_FLOAT, sizeof(Buffer), &points[0].point.x);
      glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Buffer), &points[0].color.r);
      glPointSize(3);
      glDrawArrays(GL_POINTS, 0, points.size());
    }
  if (circles.size())
    {
      glVertexPointer(2, GL_FLOAT, sizeof(Buffer), &circles[0].point.x);
      glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Buffer), &circles[0].color.r);
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      for (unsigned int i = 0; i < circles.size(); i += 360)
	{
	  glDrawArrays(GL_LINE_LOOP, i , i + 360);
	}
       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
  glDisableClientState( GL_VERTEX_ARRAY );
  glDisableClientState( GL_COLOR_ARRAY );
}

void Canvas::clear()
{
  default_color = Color(255, 255, 255, 255);
  points.clear();
  edges.clear();
  squares.clear();
  triangles.clear();
  circles.clear();
}