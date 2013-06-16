#include <cw/opengl/Shader.hpp>

#include <fstream>
#include <sstream>
#include <vector>

#include <cw/core/Logger.hpp>
#include <cw/opengl/GlException.hpp>

namespace cw
{
  namespace opengl
  {

Shader::Shader( const std::string & filename, GLenum shaderType )
  : m_filename(filename)
  , m_shaderId( glCreateShader(shaderType) )
{
  glGetShaderiv(m_shaderId, GL_SHADER_TYPE, &m_shaderType);
}

Shader::~Shader()
{
  glDeleteShader( m_shaderId );
}

GLuint Shader::getShaderId() const
{
  return m_shaderId;
}

void Shader::read()
{
  m_filecontent = "";
  std::ifstream ifs( m_filename.c_str(), std::ios::in );
  if ( !ifs.is_open() )
  {
    THROW( GlException,m_filename + ": cannot be opened!");
  }
  std::string line;
  while( getline(ifs, line) )
  {
    m_filecontent += "\n" + line;
  }
  ifs.close();
}

void Shader::compile()
{
  LOG_DEBUG(getLogMessageHeader(), "compiling: '", m_filename, "'");
  char const * shaderSrcPtr = m_filecontent.c_str();
  glShaderSource( m_shaderId, 1, &shaderSrcPtr, NULL );
  glCompileShader( m_shaderId );
}

std::string shaderTypeToStr( GLint shaderType )
{
  switch(shaderType)
  {
    case GL_VERTEX_SHADER:   return "VERTEX_SHADER";
    case GL_FRAGMENT_SHADER: return "FRAGMENT_SHADER";
    case GL_GEOMETRY_SHADER: return "GEOMETRY_SHADER";
    default: return "INVALID SHADER TYPE!";
  }
}

std::string Shader::getLogMessageHeader() const
{
  std::stringstream ss;
  ss << "Shader (id=" << m_shaderId <<
    ", type=" << shaderTypeToStr(m_shaderType) <<
    ") ";
  return ss.str();
}

void Shader::check()
{
  GLint result = GL_FALSE;
  int logLength = 0;
  glGetShaderiv( m_shaderId, GL_COMPILE_STATUS, &result );
  glGetShaderiv( m_shaderId, GL_INFO_LOG_LENGTH, &logLength );
  std::vector< char > shaderErrMsg(logLength);
  glGetShaderInfoLog( m_shaderId, logLength, NULL, &shaderErrMsg[0] );
  if (!result)
  {
    THROW( GlException, getLogMessageHeader() + " compile error: " + &shaderErrMsg[0] );
  }
}

void Shader::attachProgram( GLuint programId ) const
{
  glAttachShader(programId, m_shaderId);
}
  }
}
