#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <random>
#include "Filter.hh"
#include "Transform.hh"
#include "Shader.hh"
#include "Render.hh"
#include "Generate.hh"

#define SEED_1 time(NULL)
#define NSQUARES 150
#define SQ_S_MIN (3.0 * 5.0)
#define SQ_S_MAX (15.0 * 5.0)
#define SQ_MEAN (1.15)
#define WAIT_CNT (512)
//5 centiemes de seconde
#define DRAWTIME (20)

#define SQ_S_AVE ((SQ_S_MIN + SQ_S_MAX) / 2.0)

void clipit(const Render &render, const std::string &filename)
{
  unsigned char *raw_img;
  int height;
  int width;
  raw_img = render.getScreenShot(width, height);
  render.saveBufferInFile(raw_img, width, height, filename);
}

std::string getImageName(const std::string &prefix, const std::string &suffix)
{
  static int ncnt = 0;
  std::string num;

  if (ncnt < 100)
  {
    if (ncnt < 10)
    {
      num = "00" + std::to_string(ncnt++);
    }
    else
    {
      num = "0" + std::to_string(ncnt++);
    }
  }
  else
  {
    num = std::to_string(ncnt++);
  }
  return prefix + num + suffix;
}

int main(int ac, char **av)
{
  std::vector<Square> sqs;
  std::stringstream name;
  unsigned int seed(SEED_1);
  std::stringstream params((ac > 1 ? av[1] : ""));
  std::string filename((ac > 2 ? av[2] : "draw_"));
  GLuint textureID = 0;

  if (params.str() != "")
    params >> seed;
  Generate::setSeed(seed);
  name << "Generator Dungeon seed : '" << seed << "'";
  std::cout << name.str() << std::endl;
  Render render(Box(1024 / 2.0, 1024 / 2.0, 1024, 1024), name.str(), ac, av);
  Canvas &canvas = render.getCanvas();
  canvas.setDefaultColor(Color(80, 120, 185, 255));

  const float edgeSize = (sqrt(NSQUARES) * sqrt(SQ_S_MIN * SQ_S_MAX));

  std::vector<Point> points_distribution = Generate::pointsInSquare(NSQUARES, Point(0, 0), edgeSize, edgeSize);
  for (const Point &obj : points_distribution)
    canvas.draw(obj);
  render.renderScene(textureID);
  clipit(render, getImageName(filename, ".bmp"));
  canvas.clear();
  canvas.setDefaultColor(Color(80, 120, 185, 255));

  //All squares
  sqs = Generate::squares(points_distribution, SQ_S_MIN, SQ_S_MAX);
  int i = 1;
  std::cout << "Scattering..." << std::endl;
  Transform::scatter(sqs, [&]() {
    if (--i == 0)
    {
      for (Square &room : sqs)
        canvas.draw(room);
      render.renderScene(textureID);
      clipit(render, getImageName(filename, ".bmp"));
      i = WAIT_CNT;
    }
  });

  usleep(100000);
  std::cout << "Main rooms selection..." << std::endl;
  //Only main rooms
  std::vector<Square> main_rooms = Filter::getMoreOrEqualSize(sqs, SQ_S_AVE * SQ_MEAN,
                                                              SQ_S_AVE * SQ_MEAN);

  canvas.setDefaultColor(Color(2, 30, 46, 255));
  for (Square &room : sqs)
  {
    canvas.remove(room);
    room.index = -1;
    canvas.draw(room);
  }
  canvas.setDefaultColor(Color(70, 70, 70, 255));
  for (Square &room : main_rooms)
  {
    room.index = -1;
    canvas.draw(room);
  }
  render.renderScene(textureID);
  for (int i = 0; i < 100 / DRAWTIME; i++)
    clipit(render, getImageName(filename, ".bmp"));

  usleep(100000);
  std::cout << "Getting center of squares..." << std::endl;
  //Only center rooms
  std::vector<Point> center_rooms = Filter::getCenterSquares(main_rooms);
  canvas.setDefaultColor(Color(120, 185, 80, 255));
  for (Point &obj : center_rooms)
    canvas.draw(obj);
  render.renderScene(textureID);
  for (int i = 0; i < 100 / DRAWTIME; i++)
    clipit(render, getImageName(filename, ".bmp"));

  usleep(100000);
  std::cout << "Applying delaunay triangulation..." << std::endl;
  //Delaunay
  std::vector<Triangle> tab = Generate::delaunay(center_rooms);
  canvas.setDefaultColor(Color(185, 20, 120, 255));
  for (Triangle &obj : tab)
    canvas.draw(obj);
  render.renderScene(textureID);
  for (int i = 0; i < 100 / DRAWTIME; i++)
    clipit(render, getImageName(filename, ".bmp"));

  usleep(100000);
  std::cout << "Applying minimul spanning tree..." << std::endl;
  //Minimum spanning tree
  std::vector<Edge> mst = Filter::getMininumSpanningTree(Filter::getAllEdges(tab), center_rooms);
  for (Triangle &obj : tab)
    canvas.remove(obj);
  canvas.setDefaultColor(Color(185, 20, 120, 255));
  for (Edge &obj : mst)
    canvas.draw(obj);
  render.renderScene(textureID);
  for (int i = 0; i < 100 / DRAWTIME; i++)
    clipit(render, getImageName(filename, ".bmp"));

  usleep(100000);
  std::cout << "Getting final path..." << std::endl;
  //final Path
  std::vector<Edge> minimum = Filter::getPath(mst, main_rooms);
  for (Edge &obj : mst)
    canvas.remove(obj);
  canvas.setDefaultColor(Color(185, 20, 120, 255));
  for (Edge &obj : minimum)
    canvas.draw(obj);
  render.renderScene(textureID);
  for (int i = 0; i < 100 / DRAWTIME; i++)
    clipit(render, getImageName(filename, ".bmp"));

  usleep(100000);
  std::cout << "Building corridors..." << std::endl;
  //Corridors
  std::vector<Square> final_rooms = Filter::cleanRoom(minimum, sqs);
  std::vector<Square> final_corridors = Filter::addCorridor(minimum, final_rooms, SQ_S_MIN);
  canvas.setDefaultColor(Color(185, 120, 80, 255));
  for (Square &room : sqs)
  {
    canvas.remove(room);
    room.index = -1;
  }

  canvas.setDefaultColor(Color(185, 185, 185, 255));
  for (Square &room : final_rooms)
  {
    room.index = -1;
    canvas.draw(room);
  }

  canvas.setDefaultColor(Color(120, 120, 120, 255));
  for (Square &room : final_corridors)
  {
    //room.index = -1;
    canvas.draw(room);
  }

  //final
  render.renderScene(textureID);
  for (int i = 0; i < 100 / DRAWTIME; i++)
    clipit(render, getImageName(filename, ".bmp"));
  //Shader shader("shaders/edgeDetection.shader", textureID);
  //render.setShader(shader);
  //render.renderImage();
  //clipit(render, getImageName(filename, ".bmp"));
  render.start();
  return (0);
}
