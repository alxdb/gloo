#ifndef GL_UTILS_VAO_HPP
#define GL_UTILS_VAO_HPP

#include <GL/glew.h>

#include <vector>

#include "gl_utils.hpp"
#include "vbo.hpp"

namespace gl_utils {
  struct VertexAttrib {
    const VBO& vbo;
    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const GLvoid* pointer;
  };

  class VAO final : public GLObj {
  public:
    VAO(const std::vector<VertexAttrib>& vertex_attributes) {
      glGenVertexArrays(1, &id);
      glBindVertexArray(id);
      for (VertexAttrib a : vertex_attributes) {
        glEnableVertexAttribArray(a.index);
        glBindBuffer(GL_ARRAY_BUFFER, a.vbo.get_id());
        glVertexAttribPointer(a.index, a.size, a.type, a.normalized, a.stride, a.pointer);
      }
    };
    ~VAO() { glDeleteVertexArrays(1, &id); }
  };
}

#endif
