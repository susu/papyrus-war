#ifndef GLSTUB_SHADER_REPO_HPP_INC
#define GLSTUB_SHADER_REPO_HPP_INC

#include <cassert>
#include <map>
#include <vector>

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

#endif
