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

int ShaderResourceLocator::checkedLocation( int location, const std::string & locName ) const
{
  if (location == -1)
    throw GlException( locName + " is not a valid location!" );
  return location;
}

  }
}
