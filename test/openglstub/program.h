
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

    GLint getShaderiv(GLuint index, GLenum infoType)
    {
      auto it = m_shaders.find(index);
      assert( it != m_shaders.end() );
      if (GL_COMPILE_STATUS == infoType)
      {
        it->second.checked = true;
        return it->second.compiled;
      }
      return it->second.type;
    }

    void compileShader(GLuint index)
    {
      auto it = m_shaders.find(index);
      assert( it != m_shaders.end() );
      it->second.compiled = true;
    }

    std::vector<ShaderState> shaders() const
    {
      std::vector<ShaderState> ret;
      ret.reserve( m_shaders.size() );
      for ( auto const & i : m_shaders )
      {
        ret.push_back( i.second );
      }
      return ret;
    }

    void clear()
    {
      m_shaders.clear();
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
    LOG(DEBUG);
    return 0;
  }

  GLuint stub_CreateShader(GLenum type)
  {
    LOG(DEBUG);
    return shaderRepo.createShader(type);
  }

  void stub_GetShaderiv(GLuint index,GLenum infoType,GLint* out)
  {
    LOG(DEBUG);
    *out = shaderRepo.getShaderiv(index, infoType);
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
    shaderRepo.compileShader(id);
  }

  void stub_GetShaderInfoLog(GLuint id, GLsizei bufSize, GLsizei*, GLchar* infoLog)
  {}

  GLenum glewInit()
  {
    __glewCreateProgram = &stub_CreateProgram;
    __glewCreateShader = &stub_CreateShader;
    __glewGetShaderiv = &stub_GetShaderiv;
    __glewDeleteShader = &stub_DeleteShader;
    __glewShaderSource = &stub_ShaderSource;
    __glewCompileShader = &stub_CompileShader;
    __glewGetShaderInfoLog = &stub_GetShaderInfoLog;
    return 0;
  }
}

