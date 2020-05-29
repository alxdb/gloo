#ifndef GL_UTILS_HPP
#define GL_UTILS_HPP

#ifndef GL_UTILS_NOGLEW
#include <GL/glew.h>
#endif

namespace gl_utils {
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
