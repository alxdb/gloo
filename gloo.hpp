#ifndef GLOO_HPP
#define GLOO_HPP

namespace gloo {

class GLObj {
protected:
  GLuint m_id = 0;
  GLObj(){};

public:
  const GLuint& id = m_id;

  GLObj(const GLObj&) = delete;
  GLObj& operator=(const GLObj&) = delete;
  GLObj(GLObj&& other) : m_id(other.m_id) { other.m_id = 0; }
  virtual ~GLObj(){};
};

} // namespace gloo

#include "shaders.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include "buffer.hpp"

#endif
