#ifndef GLOO_VAO_HPP
#define GLOO_VAO_HPP

#include <map>
#include <vector>

#include "gloo.hpp"
#include "buffer.hpp"

namespace gloo {

struct VertexAttrib {
  GLuint index{};
  GLenum type = GL_FLOAT;
  GLint size = 4;
  GLsizei stride = 0;
  const GLvoid* ptr = nullptr;
  GLboolean normalized = GL_FALSE;
};

class VAO final : public GLObj {
public:
  VAO() { glGenVertexArrays(1, &m_id); };

  void add_vertex_buffer(const Buffer& vbo, std::vector<VertexAttrib> attributes) {
    glBindVertexArray(id);
    glBindBuffer(vbo.target, vbo.id);
    for (const VertexAttrib& attrib : attributes) {
      glEnableVertexAttribArray(attrib.index);
      glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized, attrib.stride, attrib.ptr);
    }
  };

  VAO(VAO&& other) : GLObj(static_cast<GLObj&&>(other)){};
  ~VAO() { glDeleteVertexArrays(1, &id); }
};

} // namespace gloo

#endif
