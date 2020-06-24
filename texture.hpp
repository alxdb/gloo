#ifndef GLOO_TEXTURE_HPP
#define GLOO_TEXTURE_HPP

#include "gloo.hpp"

namespace gloo {

class Texture final : public GLObj {
  Texture() { glGenTextures(1, &m_id); }
  Texture(Texture&& other) : GLObj(std::move(other)) {}
  ~Texture() { glDeleteTextures(1, &m_id); }
};

} // namespace gloo

#endif
