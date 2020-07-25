#include "Shader.hh"
#include "Render.hh"

unsigned long Shader::getFileLength(std::ifstream& file)
{
    if(!file.good()) return 0;

    file.tellg();
    file.seekg(0,std::ios::end);
    unsigned long len = file.tellg();
    file.seekg(std::ios::beg);

    return len;
}

char* Shader::loadSource(const char *filename)
{
  std::ifstream file;
  char *shaderSource;
  file.open(filename, std::ios::in);
  if(!file) return NULL;

  unsigned int len = getFileLength(file);

  if (len==0) return NULL;

  shaderSource = new char[len+1];
  if (shaderSource == 0) return NULL;
  shaderSource[len] = 0;

  unsigned int i=0;
  while (file.good())
    {
      shaderSource[i] = file.get();
      if (!file.eof())
	i++;
    }

  shaderSource[i] = 0;

  file.close();
  return shaderSource;
}

Shader::Shader(const Shader &other)
: filename(other.filename), id(other.id), program(other.program), textureID(other.textureID), source(NULL)
{

}

Shader::Shader(const std::string &_filename, GLuint texture)
  : filename(_filename), id(glCreateShader(GL_FRAGMENT_SHADER)), program(glCreateProgram()), textureID(texture)
{
  source = loadSource(filename.c_str());
  glShaderSource(id, 1, (const GLchar**)&source, NULL);
  glCompileShaderARB(id);
  GLint compile_status = GL_TRUE;
  glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
  if(compile_status != GL_TRUE)
    {
      GLsizei logsize = 0;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logsize);
      char *log = new char[logsize + 1];
      glGetShaderInfoLog(id, logsize, &logsize, log);
      log[logsize + 1] = '\0';
      std::cout << "compile errors : " << log << std::endl;
      delete [] log;
    }
  glAttachShader(program, id);
  glLinkProgram(program);
}

Shader::~Shader()
{
  if (source != 0)
    delete[] source;
  source = 0;
  glDeleteShader(id);
  glDeleteProgram(program);
}

const Shader &Shader::operator=(const Shader &other)
{
      if (this != &other)
	{
	  filename = other.filename;
      id = other.id;
      program = other.program;
      textureID = other.textureID;
      source = NULL;
    }
  return (*this);
}

void Shader::begin()
{
  glBindTexture(GL_TEXTURE_2D, textureID);
  glUseProgram(program);
}

void Shader::end()
{
  glUseProgram(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}
