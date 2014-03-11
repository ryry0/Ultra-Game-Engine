#ifndef GLSHADERPROG_H_
#define GLSHADERPROG_H_

#include <GL/glew.h>
#include <string>
/*
 * Description:
 *  This class represents a fully compiled and linked shader program object.
 *  First you feed it the source directly, or from a file.
 *  (CreateProgram/CreateProgFromFile respectively)
 *
 * Function:
 *  CreateProgFromFile: Accepts two file paths, extracts the source, then calls
 *    CreateProgram on the source data.
 *  CreateProgram:  Compiles and links the vertex and fragment shader.
 *  BindProgram:    Binds the program to the OpenGL state machine.
 *    (Activates *this current shader program.)
 *  UnbindProgram:    Unbinds the program from the OpenGL state machine.
 *    (Deactivates *this shader program.)
 */

class GLShaderProgram
{
  public:
    GLShaderProgram ();
    ~GLShaderProgram();

    GLShaderProgram         (const std::string &vertex_file_name,
                             const std::string &fragment_file_name);

    bool CreateProgFromFile (const std::string &vertex_file_name,
                             const std::string &fragment_file_name);

    bool CreateProgram      (const std::string &vertex_source,
                             const std::string &fragment_source);

    void BindProgram        () { glUseProgram(program_); }
    void UnbindProgram      () { glUseProgram(0); }

    GLuint GetFragmentShader() { return fragment_shader_; }
    GLuint GetVertexShader  () { return vertex_shader_; }
    GLuint GetProgram       () { return program_; }

    void operator()         () { BindProgram(); }

  private:
    bool LoadFromFile (const std::string &file_name, std::string &shader_source);
    GLuint vertex_shader_, fragment_shader_, program_;
};
#endif
