#ifndef QUAD_H_
#define QUAD_H_
#include <cstring>
#define GLEW_STATIC
#include <GL/glew.h>
#include <engine/glshaderprog.h>
#include <engine/logger.h>

namespace primitive
{

/*
 * Description:
 *  This class provides a wrapper for a simple quad.
 *  It initializes a VBO, VAO, and EBO associated with this object.
 *  You need to pass the shader and its attribute names for position, color,
 *  and texture coordinate. If -1 is passed, it will not try to bind
 *  the attribute. This allows me to be flexible with the shader,
 *  and to use different shaders with different quads.
 */
class Quad
{
  public:
    ~Quad();
    void Init  (GLint position_attribute = -1,
                GLint color_attribute    = -1,
                GLint texture_attribute  = -1);
    void Render();

  private:
    static GLfloat vertices_[28];
    static GLuint elements_[6];
    GLuint element_buffer_obj_;
    GLuint vertex_buffer_obj_;
    GLuint vertex_array_obj_;
};
}
#endif
