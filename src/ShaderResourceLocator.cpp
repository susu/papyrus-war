#include <cw/opengl/ShaderResourceLocator.hpp>

#include <cw/opengl/GlException.hpp>

namespace cw
{
  namespace opengl
  {
ShaderResourceLocator::ShaderResourceLocator( GLuint programId )
  : m_programId(programId)
{}

ShaderResourceLocator::~ShaderResourceLocator()
{}

GLuint ShaderResourceLocator::getUniform( const char * name ) const
{
  return checkedLocation( glGetUniformLocation( m_programId, name ), name );
}

GLuint ShaderResourceLocator::getAttrib( const char * name ) const
{
  return checkedLocation( glGetAttribLocation(m_programId,name), name );
}

void ShaderResourceLocator::setUniform( const char * name, float value )
{
  glUniform1fv( getUniform(name), 1, &value );
}

void ShaderResourceLocator::setUniform( const char * name, const glm::vec3 & value )
{
  glUniform3fv( getUniform(name), 1, &value[0] );
}

int ShaderResourceLocator::checkedLocation( int location, const std::string & locName ) const
{
  if (location == -1)
    THROW(GlException, locName + " is not a valid location!" );
  return location;
}

  }
}
