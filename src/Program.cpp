#include <cw/opengl/Program.hpp>

#include <algorithm>
#include <vector>

#include <cw/core/Logger.hpp>
#include <cw/core/InputFile.hpp>

#include <cw/opengl/GlException.hpp>
#include <cw/opengl/Shader.hpp>

namespace cw
{
  namespace opengl
  {

Program::Program()
  : m_programId( glCreateProgram() )
{
  LOG_DEBUG("Program created: id=", m_programId);
}

Program::~Program()
{}

void Program::attachShaderFromFile(std::unique_ptr<core::InputFile> file, GLuint shaderType)
{
  Shader shader(*file, shaderType);
  shader.read();
  shader.compile();
  shader.check();

  glAttachShader( m_programId, shader.getShaderId() );
}

void Program::link()
{
  glLinkProgram(m_programId);
  check();
  LOG_DEBUG("Program linked successfully: id=", m_programId);
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
    THROW( GlException, std::string("Error with program: ") + &progErrMsg[0] );
  }
}

  }
}
