#ifndef GLOO_VAO_HPP
#define GLOO_VAO_HPP

#include <vector>

#include "gloo.hpp"
#include "vbo.hpp"

namespace gloo {

struct VertexAttrib {
  GLuint index;
  GLenum type;
  GLint size;
  GLsizei stride;
  const GLvoid* ptr;
  GLboolean normalized;

  VertexAttrib(GLuint index,
               GLenum type = GL_FLOAT,
               GLint size = 4,
               GLsizei stride = 0,
               const GLvoid* ptr = 0,
               GLboolean normalized = GL_FALSE)
      : index(index), type(type), size(size), stride(stride), ptr(ptr), normalized(normalized){};
};

class VAO final : public GLObj {
public:
  VAO(const std::vector<std::pair<VBO, VertexAttrib>>& vertex_attributes) {
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(id);
    for (const std::pair<VBO, VertexAttrib>& vbo_attrib : vertex_attributes) {
      const VBO& vbo = vbo_attrib.first;
      const VertexAttrib& attrib = vbo_attrib.second;
      glEnableVertexAttribArray(attrib.index);
      glBindBuffer(vbo.target, vbo.id);
      glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.ptr);
    }
  };
  VAO(VAO&& other) : GLObj(static_cast<GLObj&&>(other)){};

  ~VAO() { glDeleteVertexArrays(1, &id); }
};

} // namespace gloo

#endif
