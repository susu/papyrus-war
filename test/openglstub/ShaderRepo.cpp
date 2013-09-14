#include "ShaderRepo.hpp"

std::unique_ptr<ShaderRepo> ShaderRepo::s_instance;

ShaderRepo& ShaderRepo::instance()
{
  if (s_instance == nullptr)
  {
    LOG_DEBUG("First access of ShaderRepo");
    s_instance.reset(new ShaderRepo);
  }
  return *s_instance;
}

GLuint ShaderRepo::createShader(GLenum type)
{
  ShaderState state;
  state.type = type;
  auto newIndex = getNewIndex();
  m_shaders.insert( std::make_pair( newIndex, state ) );
  return newIndex;
}

GLint ShaderRepo::getShaderiv(GLuint index, GLenum infoType)
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

void ShaderRepo::compileShader(GLuint index)
{
  auto it = m_shaders.find(index);
  assert( it != m_shaders.end() );
  it->second.compiled = true;
}

std::vector<ShaderRepo::ShaderState> ShaderRepo::shaders() const
{
  std::vector<ShaderState> ret;
  ret.reserve( m_shaders.size() );
  for ( auto const & i : m_shaders )
  {
    ret.push_back( i.second );
  }
  return ret;
}

void ShaderRepo::clear()
{
  m_shaders.clear();
}
