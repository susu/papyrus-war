
#include "GL/glew.h"
#include "GL/glxew.h"

#include <iostream>


class ShadersRepo
{
    struct ShaderState
    {
      GLenum type;
      bool compiled;
      bool checked;
      ShaderState() : type(0), compiled(false), checked(false) {}
    };
  public:
    GLuint createShader(GLenum type)
    {
      ShaderState state;
      state.type = type;
      auto newIndex = getNewIndex();
      m_shaders.insert( std::make_pair( newIndex, state ) );
      return newIndex;
    }
  private:
    GLuint getNewIndex() const
    {
      if (m_shaders.empty()) return 0;
      return m_shaders.rbegin()->first + 1;
    }
    std::map< GLuint, ShaderState > m_shaders;
};

namespace
{
  ShadersRepo shaderRepo;
}

extern "C"
{
  GLuint stub_CreateProgram()
  {
    std::cout << "SEAM WORK!" << std::endl;
    return 0;
  }

  GLuint stub_CreateShader(GLenum type)
  {
    LOG(DEBUG);
    return shaderRepo.createShader(type);
  }

  void stub_GetShaderiv(GLuint,GLenum,GLint* out)
  {
    LOG(DEBUG);
    *out = GL_VERTEX_SHADER;
  }

  void stub_DeleteShader(GLuint)
  {
    LOG(DEBUG);
  }

  void stub_ShaderSource(GLuint id,int,const char **,const int*)
  {
    LOG(DEBUG);
  }

  void stub_CompileShader(GLuint id)
  {
    LOG(DEBUG);
  }

  GLenum glewInit()
  {
    __glewCreateProgram = &stub_CreateProgram;
    __glewCreateShader = &stub_CreateShader;
    __glewGetShaderiv = &stub_GetShaderiv;
    __glewDeleteShader = &stub_DeleteShader;
    __glewShaderSource = &stub_ShaderSource;
    __glewCompileShader = &stub_CompileShader;
    return 0;
  }
}

