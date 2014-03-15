#ifndef GLSHADERPROG_H_
#define GLSHADERPROG_H_

#include <GL/glew.h>
#include <string>
#include <map>
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
 *  AddAttribute:   adds an attribute to the shader program, it returns the
 *    handle to the location of the attribute.
 *  AddUniform:   adds an uniform to the shader program, it returns the
 *    handle to the location of the uniform.
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

    void BindProgram        () { glUseProgram(program_id_); }
    void UnbindProgram      () { glUseProgram(0); }

    GLuint GetFragmentShader() const { return fragment_shader_id_; }
    GLuint GetVertexShader  () const { return vertex_shader_id_; }
    GLuint GetProgram       () const { return program_id_; }
    GLint GetAttribute      (const std::string attribute);
    GLint GetUniform        (const std::string uniform);

    GLint AddAttribute      (const std::string attribute);
    GLint AddUniform        (const std::string uniform);

    void operator()         () { BindProgram(); }

  private:
    bool LoadFromFile       (const std::string &file_name,
                             std::string &shader_source);

    GLuint vertex_shader_id_,
           fragment_shader_id_,
           program_id_;
    std::map<std::string, GLint> attribute_location_list_,
                                 uniform_location_list_;
};
#endif
