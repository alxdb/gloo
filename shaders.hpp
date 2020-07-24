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
    m_id = glCreateShader(shader_type);
    glShaderSource(m_id, 1, &source, nullptr);
    glCompileShader(m_id);

#ifdef GLOO_SHADER_CHECK
    GLint isCompiled = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

      std::string infoLog;
      infoLog.resize(maxLength);
      glGetShaderInfoLog(m_id, maxLength, &maxLength, (char*)infoLog.data());

      glDeleteShader(m_id);
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
  ~Shader() noexcept { glDeleteShader(m_id); }
};

class Program final : public GLObj {
public:
  Program(const Shader& vertex_shader, const Shader& fragment_shader) {
    m_id = glCreateProgram();

    glAttachShader(m_id, vertex_shader.id);
    glAttachShader(m_id, fragment_shader.id);
    glLinkProgram(m_id);

#ifdef GLOO_PROGRAM_CHECK
    GLint isLinked = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
      GLint maxLength = 0;
      glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

      std::string infoLog;
      infoLog.resize(maxLength);
      glGetProgramInfoLog(m_id, maxLength, &maxLength, (char*)infoLog.data());

      glDeleteProgram(m_id);
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
  Program(const std::string& filename_prefix)
      : Program(std::ifstream(filename_prefix + ".vert"), std::ifstream(filename_prefix + ".frag")){};
  Program(Program&& other) : GLObj(static_cast<GLObj&&>(other)){};
  ~Program() noexcept { glDeleteProgram(m_id); }
};

} // namespace gloo

#endif
