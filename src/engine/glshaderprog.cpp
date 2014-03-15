#define GLEW_STATIC
#include <iostream>
#include <engine/glshaderprog.h>
#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <engine/logger.h>

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
  glDetachShader(program_id_, vertex_shader_id_);
  glDetachShader(program_id_, fragment_shader_id_);
  glDeleteProgram(program_id_);
  glDeleteShader(vertex_shader_id_);
  glDeleteShader(fragment_shader_id_);
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
  {
    LOG(LOG_ERROR) << "Could not open vertex shader: " << vertex_file_name;
    return false;
  }

  if (LoadFromFile(fragment_file_name, fragment_source) == false)
  {
    LOG(LOG_ERROR) << "Could not open fragment shader: " << fragment_file_name;
    return false;
  }

  return CreateProgram(vertex_source, fragment_source);
}

/*
 * Takes two strings containing the vertex source and fragment source.
 * Compiles, attaches, links and creates a complete shader program.
 * If any of these are unsuccessful, it is logged.
 */
bool GLShaderProgram::CreateProgram(const std::string &vertex_source,
                                    const std::string &fragment_source)
{
  GLint status;
  vertex_shader_id_   = glCreateShader(GL_VERTEX_SHADER);
  fragment_shader_id_ = glCreateShader(GL_FRAGMENT_SHADER);
  program_id_         = glCreateProgram();

  char buffer[512];

  //get const char * versions of the source
  const char * vertex_source_cptr = vertex_source.c_str();
  const char * fragment_source_cptr = fragment_source.c_str();

  //associate the source with the shaders
  glShaderSource(vertex_shader_id_, 1, &vertex_source_cptr, NULL);
  glShaderSource(fragment_shader_id_, 1, &fragment_source_cptr, NULL);

  //compile the source
  glCompileShader(vertex_shader_id_);
  glCompileShader(fragment_shader_id_);

  //check if compiled successfully
  glGetShaderiv(vertex_shader_id_, GL_COMPILE_STATUS, &status);
  if(status != GL_TRUE)
  {
    glGetShaderInfoLog(vertex_shader_id_, 512, NULL, buffer);
    LOG(LOG_ERROR) << "Vertex shader compilation error:\n" << buffer;
    return false;
  }

  glGetShaderiv(fragment_shader_id_, GL_COMPILE_STATUS, &status);
  if(status != GL_TRUE)
  {
    glGetShaderInfoLog(fragment_shader_id_, 512, NULL, buffer);
    LOG(LOG_ERROR) << "Fragment shader compilation error:\n" << buffer;
    return false;
  }

  glAttachShader(program_id_, vertex_shader_id_);
  glAttachShader(program_id_, fragment_shader_id_);

  glLinkProgram(program_id_);
  glGetProgramiv(program_id_, GL_LINK_STATUS, &status);
  if (status != GL_TRUE)
  {
    LOG(LOG_ERROR) << "Could not link shader program.";
    return false;
  }

  return true;
}

/*
 * Grabs the source from file_name, and then places it into shader_source.
 */
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

/*
 * Returns the attribute location, makes sure it can be found first,
 * and logs it.
 */
GLint GLShaderProgram::GetAttribute(const std::string attribute)
{
  //make sure that it exists, otherwise log.
  if(attribute_location_list_.find(attribute) == attribute_location_list_.end())
  { LOG(LOG_ERROR) << "Could not find string attribute: " << attribute; }

  return attribute_location_list_[attribute];
}

/*
 * Returns the uniform location, makes sure it can be found first,
 * and logs it.
 */
GLint GLShaderProgram::GetUniform(const std::string uniform)
{
  //make sure that it exists, otherwise log.
  if(uniform_location_list_.find(uniform) == uniform_location_list_.end())
  { LOG(LOG_ERROR) << "Could not find string uniform: " << uniform; }

  return uniform_location_list_[uniform];
}

/*
 * Adds the attribute to the program, and returns a handle to its location.
 */
GLint GLShaderProgram::AddAttribute(const std::string attribute)
{
  attribute_location_list_[attribute] = glGetAttribLocation(program_id_,
                                                            attribute.c_str());
  if (attribute_location_list_[attribute] == -1)
  { LOG(LOG_ERROR) << "Could not locate " << attribute << " in shader"; }

  return attribute_location_list_[attribute];
}

/*
 * Adds the uniform to the program, and returns a handle to its location.
 */
GLint GLShaderProgram::AddUniform(const std::string uniform)
{
  uniform_location_list_[uniform] = glGetUniformLocation(program_id_,
                                                         uniform.c_str());
  if (uniform_location_list_[uniform] == -1)
  { LOG(LOG_ERROR) << "Could not locate " << uniform << " in shader"; }

  return uniform_location_list_[uniform];
}
