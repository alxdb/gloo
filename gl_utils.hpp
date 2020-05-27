#ifndef GL_UTILS_HPP
#define GL_UTILS_HPP

#ifndef GL_UTILS_DONT_INCLUDE_GL_HEADER
#include <GL/glew.h>
#endif

namespace gl_utils {
  class GLObj {
  protected:
    GLuint id;
    GLObj() {};

  public:
    GLObj(const GLObj&) = delete;
    GLObj& operator=(const GLObj&) = delete;
    GLuint get_id() const { return id; }
    virtual ~GLObj() {};
  };
}

#include "vbo.hpp"
#include "vao.hpp"
#include "shaders.hpp"

#endif
