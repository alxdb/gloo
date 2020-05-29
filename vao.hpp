#ifndef GLOO_VAO_HPP
#define GLOO_VAO_HPP

#include <vector>

#include "gloo.hpp"
#include "vbo.hpp"

namespace gloo {
  struct VertexAttrib {
    const VBO& vbo;
    GLuint index;
    GLint size = 4;
    GLsizei stride = 0;
    const GLvoid* pointer = 0;
    // should use optional, but I want stick to C++11. Hopefully, OpenGL doesn't use 0 as a meaningfull value here
    GLenum type = 0;
    GLboolean normalized = false;
  };

  class VAO final : public GLObj {
  public:
    VAO(const std::vector<VertexAttrib>& vertex_attributes) {
      glGenVertexArrays(1, &id);
      glBindVertexArray(id);
      for (VertexAttrib attrib : vertex_attributes) {
        const VBO& vbo = attrib.vbo;
        glEnableVertexAttribArray(attrib.index);
        glBindBuffer(vbo.target, vbo.get_id());
        GLenum type = attrib.type ? attrib.type : vbo.get_gl_type();
        glVertexAttribPointer(attrib.index, attrib.size, type, attrib.normalized, attrib.stride, attrib.pointer);
      }
    };
    ~VAO() { glDeleteVertexArrays(1, &id); }
  };
}

#endif
