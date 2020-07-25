#ifndef _RENDER_HH_
# define _RENDER_HH_

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Box.hh"
#include "Canvas.hh"
#include "Shader.hh"

class Render
{
private:
  Box _rect;
  std::string _name;
  Canvas _canvas;
  Shader shader;
  GLuint fbo;
  GLuint render_buf;
private:
  Render() = default;
  Render(const Render &other) = delete;
  Render &operator=(const Render &other) = delete;
  void init(int ac, char **av);
public:
  GLuint id;
  Render(int argc, char *argv[]);
  Render(const Box &rect, const std::string &name, int argc, char *argv[]);
  ~Render();
  Canvas &getCanvas();
  void renderScene();
  void renderScene(GLuint &texture);
  void start();
  void resize(GLsizei width, GLsizei height);
  void renderImage();
  void setShader(const Shader &shader);
  const Box &getRect() const;
  unsigned char *getScreenShot(int &width, int &height) const;
  void saveBufferInFile(unsigned char *raw, int width, int height, const std::string filename) const;
};

#endif /* ! _RENDER_HH_ */
