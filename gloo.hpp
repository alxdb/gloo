#ifndef GLOO_HPP
#define GLOO_HPP

#ifndef GLOO_NOGLEW
#include <GL/glew.h>
#endif

namespace gloo {
  class GLObj {
  protected:
    GLuint id;
    GLObj() {};

  public:
    GLuint get_id() const { return id; }

    GLObj(const GLObj&) = delete;
    GLObj& operator=(const GLObj&) = delete;
    virtual ~GLObj() {};
  };
}

#include "vbo.hpp"
#include "vao.hpp"
#include "shaders.hpp"

#endif
