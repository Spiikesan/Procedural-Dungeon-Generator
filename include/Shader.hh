#ifndef SHADER_HH_
# define SHADER_HH_

#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

class Render;

class Shader
{
private:
  std::string filename;
  GLuint id;
  GLuint program;
  GLuint textureID;
  char *source;
  char* loadSource(const char *filename);
  unsigned long getFileLength(std::ifstream& file);
public:
  Shader() = default;
  Shader(const Shader &other);
  Shader(const std::string &_filename, GLuint texture);
  ~Shader();
  const Shader &operator=(const Shader &other);
  void begin();
  void end();
};

#endif // SHADER_HH_
