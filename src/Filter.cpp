#ifndef FILTER_CPP

#include "Filter.hh"

Node::Node() : pts(), value(0) { }

Node::Node(const Point &_pts, const Edge &_edge, float _value) : pts(_pts), edge(_edge), value(_value) { }

Node::Node (const Node &other) : pts(other.pts), edge(other.edge),value(other.value) { }

const Node &Node::operator=(const Node &other)
{
    if (this != &other)
    {
	  pts = other.pts;
	  edge = other.edge;
      	  value = other.value;
    }
  return (*this);
}

bool	Node::operator<(const Node &other)
{
  return (value < other.value);
}

bool	Node::operator==(const Node &other)
{
  return (pts == other.pts);
}

const Point &Filter::getMin(const std::vector<Point> &tab)
{
  const Point *min = &tab[0];

  for(const Point &pts : tab)
    {
      if (pts < *min)
	min = &pts;
    }
  return (*min);
}

const Point &Filter::getMax(const std::vector<Point> &tab)
{
  const Point *max = &tab[0];
  for(const Point &pts : tab)
    {
      if (pts > *max)
	max = &pts;
    }
  return (*max);
}

std::vector<Square> Filter::getMoreOrEqualSize(const std::vector<Square> &tab,
					       float width, float height)
{
  std::vector<Square> tmp;
  for (const Square &sq : tab)
    {
      if (sq.box.width >= width && sq.box.height >= height)
	tmp.push_back(sq);
    }
  return (tmp);
}

std::vector<Point> Filter::getCenterSquares(const std::vector<Square> &squares)
{
  std::vector<Point> tmp;

  for(const Square &sq : squares)
      tmp.push_back(sq.getCenter());
  return (tmp);
}

std::vector<Edge> Filter::getAllEdges(const std::vector<Triangle> &triangles)
{
  std::vector<Edge> tmp;

  for(const Triangle &tr : triangles)
    {
      tmp.push_back(tr.e1);
      tmp.push_back(tr.e2);
      tmp.push_back(tr.e3);
    }
  return (tmp);
}

std::vector<Edge> Filter::getAllEdgesFromVertices(const std::vector<Edge> &edges,
						  const Point &pts)
{
  std::vector<Edge> tmp;

  for (const Edge &edge : edges)
    {
      if (edge.p1 == pts || edge.p2 == pts)
	tmp.push_back(edge);
    }
  return (tmp);
}

std::vector<Edge> Filter::getEdgesNotIn(const std::vector<Edge> &edges, const std::vector<Edge> &others)
{
 std::vector<Edge> tmp;
 if (others.size() == 0)
    {
      tmp.assign(edges.begin(), edges.end());
      return (tmp);
    }
 for (const Edge &edge : edges)
    {
      auto found = std::find(others.begin(), others.end(), edge);
      if (found == others.end())
	tmp.push_back(edge);
    }
  return (tmp);
}

std::vector<Edge> Filter::getEdgesNotIn(const std::vector<Edge> &edges, const std::vector<Point> &pts)
{
  std::vector<Edge> tmp;

  if (pts.size() == 0)
    {
      tmp.assign(edges.begin(), edges.end());
      return (tmp);
    }
  for (const Edge &edge : edges)
    {
	auto found = std::find_if(pts.begin(), pts.end(), [&edge](const Point &p) {
				  return (p == edge.p1 || edge.p2 == p);
				  });
      if (found == pts.end())
	tmp.push_back(edge);
    }
  return (tmp);
}

const Edge &Filter::getMin(const std::vector<Edge> &edges)
{
  const Edge *min = &edges[0];
  for (const Edge &edge : edges)
    {
      if (*min > edge)
	min = &edge;
    }
  return (*min);
}

std::vector<Edge> Filter::getMininumSpanningTree(const std::vector<Edge> &edges,
						 const std::vector<Point> &vertices)
{
  std::list<Node> T;
  std::list<Node> nodes;
  std::vector<Edge> tmp;

  for (const Edge &e : edges)
    if (e.p1 == vertices[0] || e.p2 == vertices[0])
      nodes.push_back(Node((vertices[0] == e.p1 ? e.p2 : e.p1), e, e.length2()));
  nodes.sort();
  nodes.unique();
  while (!nodes.empty())
    {
      Node n = nodes.front();
      nodes.pop_front();
      if (std::find(T.begin(), T.end(), n) == T.end())
	{
	  T.push_back(n);
	  tmp.push_back(n.edge);
	  for (const Edge &e : edges)
	    if (e.p1 == n.pts || e.p2 == n.pts)
	      nodes.push_back(Node((n.pts == e.p1 ? e.p2 : e.p1), e, e.length2()));
	  nodes.sort();
	  nodes.unique();
	}
    }
  return (tmp);
}

std::vector<Edge> Filter::getPath(const std::vector<Edge> &edges, const std::vector<Square> &rooms)
{
  std::vector<Edge> tmp;

  (void) rooms; // manque le check de collision avec une autre room;
  for (const Edge &edge : edges)
    {
      Point d = edge.p2 - edge.p1;
      if (d.x != 0.0 && d.y != 0.0)
	{
	  tmp.push_back(Edge(edge.p1, Point(edge.p2.x, edge.p1.y)));
	  tmp.push_back(Edge(Point(edge.p2.x, edge.p1.y), edge.p2));
	}
      else
	tmp.push_back(edge);
    }
  return (tmp);
}

std::vector<Square> Filter::cleanRoom(const std::vector<Edge> &edges, const std::vector<Square> &rooms)
{
  std::vector<Square> tmp;

  for(const Square &sq : rooms)
    {
      for (const Edge &ed : edges)
	{
	  if (sq.box.collision(ed))
	    {
	      tmp.push_back(sq);
	      break;
	    }
	}
    }
  return (tmp);
}

std::vector<Square> Filter::addCorridor(const std::vector<Edge> &edges, const std::vector<Square> &rooms, float width)
{
  std::vector<Square> tmp(rooms);

  for(const Edge &ed : edges)
    {
      Point center = ed.getCenter();
      if (ed.p1.x == ed.p2.x)
	tmp.push_back(Square(center.x, center.y, width, Point::dist(ed.p1, ed.p2) + width));
      else
	tmp.push_back(Square(center.x, center.y, Point::dist(ed.p1, ed.p2) + width , width));
    }
  return (tmp);
}

#else

template <class T>
void	Filter::depup(std::vector<T> &tab)
{
  bool doublon = true;
  bool found = false;

  while (doublon) {
    doublon = false;
    found = false;
    for (int i = tab.size(); i--; ) {
      if (found)
	break;
      for (int j = i; j--; ) {
	if (tab[i] == tab[j]) {
	  tab.erase(tab.begin() + i);
	  tab.erase(tab.begin() + j);
	  doublon = true;
	  found = true;
	  break;
	}
      }
    }
  }
}

#endif // FILTER_CPP
