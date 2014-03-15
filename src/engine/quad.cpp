#define GLEW_STATIC
#include <GL/glew.h>
#include <engine/quad.h>

namespace primitive
{
GLfloat Quad::vertices_[28] = {
  //pos,          color,            texcoords.
  -1.0f,1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, //Top left
  1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, //top-right
  1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, //bottom right
  -1.0f,-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f //bottom left
};

GLuint Quad::elements_[6] = {
  0, 1, 2,
  2, 3, 0
};

Quad::~Quad()
{
  glDeleteBuffers(1, &vertex_buffer_obj_);
  glDeleteBuffers(1, &element_buffer_obj_);
  glDeleteVertexArrays(1, &vertex_array_obj_);
}

/*
 * Initializes the vertex object buffers associated with quad, and maps
 * the pointer to the correct locations in the shader. The latter is done in
 * this function because it must be within the same stack frame as the VAO.
 */
void Quad::Init(GLint position_attribute,
                GLint color_attribute,
                GLint texture_attribute)
{
  //generate and load buffer objects:
  glGenVertexArrays(1, &vertex_array_obj_);
  glBindVertexArray(vertex_array_obj_);

  glGenBuffers(1, &element_buffer_obj_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_obj_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements_), elements_,
      GL_STATIC_DRAW);

  glGenBuffers(1, &vertex_buffer_obj_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_obj_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_, GL_STATIC_DRAW);

  if (position_attribute != -1) //bind only if it exists
  {
    glVertexAttribPointer(position_attribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          7 * sizeof(GLfloat),
                          0);
  }

  if (color_attribute != -1) //bind only if it exists
  {
    glVertexAttribPointer(color_attribute,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          7 * sizeof(GLfloat),
                          (void*)(2 * sizeof(GLfloat)));
  }

  if (texture_attribute != -1) //bind only if it exists
  {
    glVertexAttribPointer(texture_attribute,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          7 * sizeof(GLfloat),
                          (void*)(5 * sizeof(GLfloat)));
  }
  glBindVertexArray(0); //unbind the vertex array object.
}

/*
 * Just bind the VAO and render
 */
void Quad::Render()
{
  glBindVertexArray(vertex_array_obj_);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glBindVertexArray(0);
}
} //namespace primitive
