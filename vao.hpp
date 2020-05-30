#ifndef GLOO_VAO_HPP
#define GLOO_VAO_HPP

#include <vector>

#include "gloo.hpp"
#include "vbo.hpp"

namespace gloo {

struct VertexAttrib {
  const VBO& vbo;
  GLuint index;
  GLenum type;
  GLint size;
  GLsizei stride;
  const GLvoid* ptr;
  GLboolean normalized;

  VertexAttrib(const VBO& vbo,
               GLuint index,
               GLenum type = GL_FLOAT,
               GLint size = 4,
               GLsizei stride = 0,
               const GLvoid* ptr = 0,
               GLboolean normalized = GL_FALSE)
      : vbo(vbo), index(index), type(type), size(size), stride(stride), ptr(ptr), normalized(normalized){};
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
      glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.ptr);
    }
  };

  ~VAO() { glDeleteVertexArrays(1, &id); }
};

} // namespace gloo

#endif
