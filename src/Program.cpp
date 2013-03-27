#include <cw/opengl/Program.hpp>

#include <vector>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/Shader.hpp>

namespace cw
{
  namespace opengl
  {

Program::Program()
  : m_programId( glCreateProgram() )
{
}

Program::~Program()
{}

void Program::attachShaderFromFile(const std::string & filepath, GLuint shaderType)
{
  Shader shader( filepath, shaderType );
  shader.read();
  shader.compile();
  shader.check();

  glAttachShader( m_programId, shader.getShaderId() );
}

void Program::link()
{
  glLinkProgram(m_programId);
  check();
}

void Program::check() const
{
  GLint result = GL_FALSE;
  int loglen = 0;
  glGetProgramiv(m_programId, GL_LINK_STATUS, &result );
  glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &loglen);
  std::vector<char> progErrMsg( std::max(loglen, int(1)) );
  glGetProgramInfoLog(m_programId, loglen, NULL, &progErrMsg[0]);
  if (!result)
  {
    throw GlException( std::string("Error with program: ") + &progErrMsg[0] );
  }
}

  }
}
