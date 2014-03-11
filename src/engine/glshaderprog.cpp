#include <engine/glshaderprog.h>
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>

//default ctor
GLShaderProgram::GLShaderProgram()
{
}

/*
 * When this constructor is called, it creates both shaders from given files.
 */
GLShaderProgram::GLShaderProgram(const std::string &vertex_file_name,
                                 const std::string &fragment_file_name)
{
  CreateProgFromFile(vertex_file_name, fragment_file_name);
}

/*
 * Destructor destroys both shaders and the program
 */
GLShaderProgram::~GLShaderProgram()
{
  glDeleteProgram(program_);
  glDeleteShader(vertex_shader_);
  glDeleteShader(fragment_shader_);
}

/*
 * Creates, compiles, and links a vertex and fragment shader, given
 * each of their source files.
 */
bool GLShaderProgram::CreateProgFromFile(const std::string &vertex_file_name,
                                         const std::string &fragment_file_name)
{
  std::string vertex_source, fragment_source;

  if (LoadFromFile(vertex_file_name, vertex_source) == false)
    return false;
  if (LoadFromFile(fragment_file_name, fragment_source) == false)
    return false;

  return CreateProgram(vertex_source, fragment_source);
}

bool GLShaderProgram::CreateProgram(const std::string &vertex_source,
                                    const std::string &fragment_source)
{
  GLint compile_status;
  vertex_shader_   = glCreateShader(GL_VERTEX_SHADER);
  fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
  program_         = glCreateProgram();

  //get const char * versions of the source
  const char * vertex_source_cptr = vertex_source.c_str();
  const char * fragment_source_cptr = fragment_source.c_str();

  //associate the source with the shaders
  glShaderSource(vertex_shader_, 1, &vertex_source_cptr, NULL);
  glShaderSource(fragment_shader_, 1, &fragment_source_cptr, NULL);

  //compile the source
  glCompileShader(vertex_shader_);
  glCompileShader(fragment_shader_);

  //check if compiled successfully
  glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &compile_status);
  if(compile_status != GL_TRUE)
    return false;

  glGetShaderiv(vertex_shader_, GL_COMPILE_STATUS, &compile_status);
  if(compile_status != GL_TRUE)
    return false;


  glAttachShader(program_, vertex_shader_);
  glAttachShader(program_, fragment_shader_);

  glLinkProgram(program_);

  return true;
}

bool GLShaderProgram::LoadFromFile( const std::string &file_name,
                                    std::string& shader_source)
{
  std::ifstream     input_file;
  std::stringstream file_stream;

  input_file.open(file_name.c_str());
  if (!input_file.good())
    return false;

  // Grab the whole file.
  file_stream << input_file.rdbuf();

  input_file.close(); //close the file.

  //Turn the whole file into a string.
  shader_source = file_stream.str();
  return true;
}
