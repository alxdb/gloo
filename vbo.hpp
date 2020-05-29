#ifndef GL_UTILS_VBO_HPP
#define GL_UTILS_VBO_HPP

#include "gl_utils.hpp"

#include <vector>
#include <typeinfo>

namespace gl_utils {
  class VBO final : public GLObj {
    GLenum m_target;
  public:
    const std::type_info& buffer_type;
    const size_t float_id = typeid(float).hash_code();

    const GLenum& target = m_target;

    template <class T>
      VBO(GLenum target, const T* data, const size_t n_el, GLenum usage)
      : m_target(target), buffer_type(typeid(T)) {
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
        static_assert(typeid(T) == buffer_type, "incorrect buffer type");
        glBindBuffer(m_target, id);
        glBindBufferSubData(m_target, offset, n_el * sizeof(T), data);
      }

    template <class T>
      void update_data(const std::vector<T>& data, const int offset = 0) {
        update_data(data.data(), data.size(), offset);
      }

    GLenum get_gl_type() const {
      GLenum type;
      switch (buffer_type.hash_code()) {
        case float_id:
          type = GL_FLOAT;
          break;
        default:
          throw std::runtime_error("no suitable GL type for buffer");
      }
    }

    ~VBO() { glDeleteBuffers(1, &id); }
  };
}

#endif
