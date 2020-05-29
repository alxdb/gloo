#ifndef GLOO_VBO_HPP
#define GLOO_VBO_HPP

#include "gloo.hpp"

#include <vector>
#include <typeinfo>

namespace gloo {
  class VBO final : public GLObj {
    GLenum m_target;
  public:
    const GLenum& target = m_target;

    template <class T>
      VBO(GLenum target, const T* data, const size_t n_el, GLenum usage)
      : m_target(target) {
        glGenBuffers(1, &id);
        glBindBuffer(m_target, id);
        glBufferData(m_target, n_el * sizeof(T), data, usage);
      };

    template <class T>
      VBO(GLenum target, const std::vector<T>& vec, GLenum usage)
      : VBO(target, vec.data(), vec.size(), usage) {};

    template <class T>
      VBO(GLenum target, size_t n_el, GLenum usage)
      : VBO(target, (const T*) nullptr, n_el * sizeof(T), usage) {};

    template <class T>
      void update_data(const T* data, const size_t n_el, const int offset) {
        glBindBuffer(m_target, id);
        glBindBufferSubData(m_target, offset, n_el * sizeof(T), data);
      }

    template <class T>
      void update_data(const std::vector<T>& data, const int offset = 0) {
        update_data(data.data(), data.size(), offset);
      }

    ~VBO() { glDeleteBuffers(1, &id); }
  };
}



#endif
