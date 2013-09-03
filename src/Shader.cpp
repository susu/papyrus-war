#include <cw/opengl/Shader.hpp>

#include <sstream>
#include <vector>

#include <cw/core/Logger.hpp>
#include <cw/core/InputFile.hpp>
#include <cw/opengl/GlException.hpp>

namespace cw
{
  namespace opengl
  {

Shader::Shader(core::InputFile & file, GLenum shaderType)
  : m_file(file)
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
  m_file.open();
  if ( !m_file.isOpen() )
  {
    THROW( GlException, m_file.getName() + ": cannot be opened!");
  }

  m_filecontent = m_file.readAll();
}

void Shader::compile()
{
  LOG_DEBUG(getLogMessageHeader(), "compiling: '", m_file.getName(), "'");
  char const * shaderSrcPtr = m_filecontent.c_str();
  glShaderSource( m_shaderId, 1, &shaderSrcPtr, NULL );
  glCompileShader( m_shaderId );
}

const char* shaderTypeToStr( GLint shaderType )
{
  switch(shaderType)
  {
    case GL_VERTEX_SHADER:   return "VERTEX_SHADER";
    case GL_FRAGMENT_SHADER: return "FRAGMENT_SHADER";
    case GL_GEOMETRY_SHADER: return "GEOMETRY_SHADER";
    case GL_COMPUTE_SHADER:  return "GL_COMPUTE_SHADER";
    case GL_TESS_CONTROL_SHADER: return "GL_TESS_CONTROL_SHADER";
    case GL_TESS_EVALUATION_SHADER: return "GL_TESS_EVALUATION_SHADER";
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
