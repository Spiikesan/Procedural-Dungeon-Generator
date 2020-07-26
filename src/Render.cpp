#include "Render.hh"

static Render *currentInstance = nullptr;

Render::Render(int argc, char *argv[])
    : _rect(0, 0, 640, 480), _name("render default")
{
  init(argc, argv);
}

Render::Render(const Box &rect, const std::string &name,
               int argc, char *argv[])
    : _rect(rect), _name(name)
{
  init(argc, argv);
}

Render::~Render()
{
  glDeleteFramebuffers(1, &fbo);
  glDeleteRenderbuffers(1, &render_buf);
}

void displayFunc()
{
  if (currentInstance)
    currentInstance->renderScene();
}

void reshapeFunc(GLsizei width, GLsizei height)
{
  if (currentInstance)
    currentInstance->resize(width, height);
}

void Render::init(int ac, char **av)
{
  currentInstance = this;
  glutInit(&ac, av);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(_rect.left(), _rect.top());
  glutInitWindowSize(_rect.width, _rect.height);
  id = glutCreateWindow(_name.c_str());
  glutDisplayFunc(displayFunc);
  glutReshapeFunc(reshapeFunc);
  glewInit();
}

void Render::start()
{
  glutMainLoop();
}

void Render::setShader(const Shader &_shader)
{
  shader = _shader;
}

void Render::renderImage()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_TEXTURE_2D);
  shader.begin();
  glBegin(GL_QUADS);
  glTexCoord2f(0, 1);
  glVertex2f(-1, 1); //top left
  glTexCoord2f(1, 1);
  glVertex2f(1, 1); //top right
  glTexCoord2f(1, 0);
  glVertex2f(1, -1); //bottom right
  glTexCoord2f(0, 0);
  glVertex2f(-1, -1); //bottom left
  glEnd();
  shader.end();
  glDisable(GL_TEXTURE_2D);
  glFinish();
  glutSwapBuffers();
}

void Render::renderScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-_rect.width / 2.0, _rect.width / 2.0,
          -_rect.height / 2.0, _rect.height / 2.0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  _canvas.renderer();
  glFinish();
  glutSwapBuffers();
}

void Render::renderScene(GLuint &texture)
{
  if (texture == 0)
  {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _rect.width, _rect.height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-_rect.width / 2.0, _rect.width / 2.0,
          -_rect.height / 2.0, _rect.height / 2.0, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  _canvas.renderer();
  glBindTexture(GL_TEXTURE_2D, texture);
  glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, _rect.width, _rect.height);
  glBindTexture(GL_TEXTURE_2D, 0);
  //glFlush();
  glutSwapBuffers();
}

void Render::resize(GLsizei width, GLsizei height)
{
  glViewport(0, 0, width, height);
}

Canvas &Render::getCanvas()
{
  return (_canvas);
}

const Box &Render::getRect() const
{
  return (_rect);
}

unsigned char *Render::getScreenShot(int &width, int &height) const
{
  GLint m_viewport[4];
  glGetIntegerv(GL_VIEWPORT, m_viewport);
  width = m_viewport[2];
  height = m_viewport[3];

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_viewport[0],
                   m_viewport[1], m_viewport[2], m_viewport[3], 0);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  unsigned char *raw_img = new unsigned char[width * height * 3];
  glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, raw_img);
  return (raw_img);
}

void Render::saveBufferInFile(unsigned char *img, int w, int h, const std::string filename) const
{
  std::ofstream imageFile(filename.c_str(), std::ios_base::binary);

  /*
  if (!imageFile) return ;
  imageFile.put(0).put(0);
  imageFile.put(2);        // RGB non compresse

  imageFile.put(0).put(0);
  imageFile.put(0).put(0);
  imageFile.put(0);

  imageFile.put(0).put(0); // origine X
  imageFile.put(0).put(0); // origine Y

  imageFile.put((width & 0x00FF)).put((width & 0xFF00) / 256);
  imageFile.put((height & 0x00FF)).put((height & 0xFF00) / 256);
  imageFile.put(24);      // 24 bit bitmap 
  imageFile.put(0);
*/

  int filesize = 54 + 3 * w * h;

  unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
  unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
  unsigned char bmppad[3] = {0, 0, 0};

  bmpfileheader[2] = (unsigned char)(filesize);
  bmpfileheader[3] = (unsigned char)(filesize >> 8);
  bmpfileheader[4] = (unsigned char)(filesize >> 16);
  bmpfileheader[5] = (unsigned char)(filesize >> 24);

  bmpinfoheader[4] = (unsigned char)(w);
  bmpinfoheader[5] = (unsigned char)(w >> 8);
  bmpinfoheader[6] = (unsigned char)(w >> 16);
  bmpinfoheader[7] = (unsigned char)(w >> 24);
  bmpinfoheader[8] = (unsigned char)(h);
  bmpinfoheader[9] = (unsigned char)(h >> 8);
  bmpinfoheader[10] = (unsigned char)(h >> 16);
  bmpinfoheader[11] = (unsigned char)(h >> 24);

  imageFile.write((char *)bmpfileheader, 14);
  imageFile.write((char *)bmpinfoheader, 40);

  for (int i = 0; i < h; i++)
  {
    imageFile.write((char *)(img + (w * (i)*3)), 3 * w);
    imageFile.write((char *)(bmppad), (4 - (w * 3) % 4) % 4);
  }
  //imageFile.write((char *)img, w * h * 3);
  imageFile.close();
}
