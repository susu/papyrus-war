#ifndef GLSTUB_SHADER_REPO_HPP_INC
#define GLSTUB_SHADER_REPO_HPP_INC

#include "GL/glew.h"

#include <cassert>
#include <map>
#include <vector>
#include <memory>
#include <cw/core/Logger.hpp>

class ShaderRepo
{
    struct ShaderState
    {
      GLenum type;
      bool compiled;
      bool checked;
      ShaderState() : type(0), compiled(false), checked(false) {}
    };
  public:
    static ShaderRepo& instance();
    GLuint createShader(GLenum type);
    GLint getShaderiv(GLuint index, GLenum infoType);
    void compileShader(GLuint index);
    std::vector<ShaderState> shaders() const;
    void clear();

  private:
    ShaderRepo()
    {}

    GLuint getNewIndex() const
    {
      if (m_shaders.empty()) return 0;
      return m_shaders.rbegin()->first + 1;
    }
    std::map< GLuint, ShaderState > m_shaders;

    static std::unique_ptr<ShaderRepo> s_instance;
};

#endif
