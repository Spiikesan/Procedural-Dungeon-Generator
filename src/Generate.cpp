#include "Generate.hh"
#include "Util.hh"

FastRandom Generate::rnd(0);

void Generate::setSeed(unsigned int seed)
{
  rnd = FastRandom(seed);
}

std::vector<Square> Generate::squares(const std::vector<Point> &pts, float min, float max)
{
  std::vector<Square> sq;
  size_t i;

  for (i = 0; i < pts.size(); ++i)
  {
    sq.push_back(Square(pts[i].x, pts[i].y,
                        Util::round(rnd.rndDouble(min, max)),
                        Util::round(rnd.rndDouble(min, max))));
  }
  return (sq);
}

std::vector<Point> Generate::pointsInCircle(size_t n, Point center, float width, float height)
{
  std::vector<Point> po;
  const bool circle = (width == height);
  float angle;
  float rady;
  float radx;
  float coeff;

  while (n--)
  {
    coeff = std::sqrt(rnd.rndDouble(0.0, 1.0));
    angle = rnd.rndDouble(0, M_PI * 2.0);
    radx = width * coeff;
    rady = (circle ? radx : height * coeff);
    po.push_back(Point(center.x + radx * std::cos(angle),
                       center.y + rady * std::sin(angle)));
  }
  return (po);
}

std::vector<Point> Generate::pointsInSquare(size_t n, Point center, float width, float height)
{
  std::vector<Point> po;
  const float w2 = width / 2.0;
  const float h2 = height / 2.0;

  setSeed(1);

  while (n--)
  {
    const float radx = rnd.rndDouble(-w2, w2);
    const float rady = rnd.rndDouble(-h2, h2);

    po.push_back(Point(center.x + radx,
                       center.y + rady));
  }
  return (po);
}

Triangle Generate::superTriangle(std::vector<Point> const &v)
{
  Point pmin(std::numeric_limits<float>::max(),
             std::numeric_limits<float>::max());
  Point pmax(std::numeric_limits<float>::min(),
             std::numeric_limits<float>::min());
  Point d;
  Point dmid;
  float dmax;

  for (const Point &p : v)
  {
    if (p.x < pmin.x)
      pmin.x = p.x;
    if (p.x > pmax.x)
      pmax.x = p.x;
    if (p.y < pmin.y)
      pmin.y = p.y;
    if (p.y > pmax.y)
      pmax.y = p.y;
  }

  d = (pmax - pmin);
  dmax = (d.x > d.y ? d.x : d.y);
  dmid = (pmax + pmin) / 2.0;

  return (Triangle(Point(dmid.x - 20.0 * dmax, dmid.y - dmax),
                   Point(dmid.x, dmid.y + 20.0 * dmax),
                   Point(dmid.x + 20.0 * dmax, dmid.y - dmax)));
}

std::vector<Triangle> Generate::delaunay(const std::vector<Point> &v)
{
  std::vector<Triangle> closed;
  std::vector<Triangle> open;
  std::vector<Edge> edges;
  std::vector<Point> vertices(v);

  if (vertices.size() < 3)
    return (open);
  if (vertices.size() == 3)
  {
    open.push_back(Triangle(vertices[0], vertices[1], vertices[2]));
    return open;
  }
  sort(vertices.begin(), vertices.end(), [](const Point &a, const Point &b) {
    return (a.x > b.x);
  });
  Triangle st = Generate::superTriangle(vertices);
  vertices.push_back(st.p1);
  vertices.push_back(st.p2);
  vertices.push_back(st.p3);
  open.push_back(st);
  for (unsigned int i = vertices.size() - 3; i--;)
  {
    edges.clear();
    for (unsigned int j = open.size(); j--;)
    {
      if (open[j].isAtRightCircumCircle(vertices[i]))
      {
        closed.push_back(open[j]);
        open.erase(open.begin() + j);
      }
      else if (open[j].inCircumCircle(vertices[i]))
      {
        edges.push_back(open[j].e1);
        edges.push_back(open[j].e2);
        edges.push_back(open[j].e3);
        open.erase(open.begin() + j);
      }
    }
    Filter::depup<Edge>(edges);
    for (unsigned int j = edges.size(); j--;)
      open.push_back(Triangle(edges[j].p1, edges[j].p2, vertices[i]));
  }
  for (int i = open.size(); i--;)
    closed.push_back(open[i]);
  open.clear();
  for (int i = closed.size(); i--;)
    if (closed[i].p1 != st.p1 && closed[i].p1 != st.p2 && closed[i].p1 != st.p3 &&
        closed[i].p2 != st.p1 && closed[i].p2 != st.p2 && closed[i].p2 != st.p3 &&
        closed[i].p3 != st.p1 && closed[i].p3 != st.p2 && closed[i].p3 != st.p3)
      open.push_back(closed[i]);
  return (open);
}
