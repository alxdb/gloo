#ifndef GLOO_SHADERS_HPP
#define GLOO_SHADERS_HPP

#include "gloo.hpp"

#include <fstream>
#include <sstream>
#include <string>

namespace gloo {

class Shader final : public GLObj {
public:
  Shader(const char* source, GLenum shader_type) {
    id = glCreateShader(shader_type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

#ifndef GLOO_SKIP_SHADER_CHECK
    GLint isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

      std::string infoLog;
      infoLog.resize(maxLength);
      glGetShaderInfoLog(id, maxLength, &maxLength, (char*)infoLog.data());

      glDeleteShader(id);
      std::stringstream error_msg;
      error_msg << "shader compilation failed, info log follows:\n";
      error_msg << infoLog;
      throw std::runtime_error(error_msg.str());
    }
#endif
  }
  Shader(const std::string& source_string, GLenum shader_type) : Shader(source_string.c_str(), shader_type){};
  Shader(std::ifstream& source_filestream, GLenum shader_type)
      : Shader(std::string(std::istreambuf_iterator<char>(source_filestream), std::istreambuf_iterator<char>()),
               shader_type){};
  Shader(std::ifstream&& source_filestream, GLenum shader_type)
      : Shader(std::string(std::istreambuf_iterator<char>(source_filestream), std::istreambuf_iterator<char>()),
               shader_type){};
  ~Shader() noexcept { glDeleteShader(id); }
};

class Program final : public GLObj {
public:
  Program(const Shader& vertex_shader, const Shader& fragment_shader) {
    id = glCreateProgram();

    glAttachShader(id, vertex_shader.get_id());
    glAttachShader(id, fragment_shader.get_id());
    glLinkProgram(id);

#ifndef GLOO_SKIP_SHADER_CHECK
    GLint isLinked = 0;
    glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
      GLint maxLength = 0;
      glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

      std::string infoLog;
      infoLog.resize(maxLength);
      glGetProgramInfoLog(id, maxLength, &maxLength, (char*)infoLog.data());

      glDeleteProgram(id);
      std::stringstream error_msg;
      error_msg << "program linkage failed, info log follows:\n";
      error_msg << infoLog;
      throw std::runtime_error(error_msg.str());
    }
#endif
  };
  Program(std::ifstream& vertex_filestream, std::ifstream& fragment_filestream)
      : Program(Shader(vertex_filestream, GL_VERTEX_SHADER), Shader(fragment_filestream, GL_FRAGMENT_SHADER)){};
  Program(std::ifstream&& vertex_filestream, std::ifstream&& fragment_filestream)
      : Program(Shader(vertex_filestream, GL_VERTEX_SHADER), Shader(fragment_filestream, GL_FRAGMENT_SHADER)){};
  Program(Program&& other) : GLObj(std::move(other)){};
  ~Program() noexcept { glDeleteProgram(id); }
};

} // namespace gloo

#endif
