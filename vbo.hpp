#ifndef GL_UTILS_VBO_HPP
#define GL_UTILS_VBO_HPP

#include "gl_utils.hpp"

#include <vector>

namespace gl_utils {
  class VBO final : public GLObj {
    GLenum m_target;
  public:
    template <class T>
    VBO(GLenum target, const T* data, const size_t n_el, GLenum usage) : m_target(target) {
      glGenBuffers(1, &id);
      glBindBuffer(m_target, id);
      glBufferData(m_target, n_el * sizeof(T), data, usage);
    };

    template <class T>
    VBO(GLenum target, const std::vector<T>& vec, GLenum usage)
      : VBO(target, vec.data(), vec.size(), usage) {};

    template <class T>
    void update_data(const std::vector<T>& vec, GLintptr offset = 0) {
      glBindBuffer(m_target, id);
      glBindBufferSubData(m_target, offset, vec.size() * sizeof(T), vec.data());
    }

    ~VBO() { glDeleteBuffers(1, &id); }
  };
}

#endif
