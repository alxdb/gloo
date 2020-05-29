#ifndef GLOO_HPP
#define GLOO_HPP

#ifndef GLOO_NOGLEW
#include <GL/glew.h>
#endif

namespace gloo {

class GLObj {
protected:
  GLuint id = 0;
  GLObj(){};

public:
  GLuint get_id() const { return id; }

  GLObj(const GLObj&) = delete;
  GLObj& operator=(const GLObj&) = delete;
  GLObj(GLObj&& other) : id(other.id) { other.id = 0; }
  virtual ~GLObj(){};
};

} // namespace gloo

#include "shaders.hpp"
#include "vao.hpp"
#include "vbo.hpp"

#endif
