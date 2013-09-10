#include <cw/opengl/ProgramContext.hpp>

#include <cw/core/Logger.hpp>
#include <cw/core/MakeString.hpp>
#include <cw/opengl/GlException.hpp>

namespace cw
{
  namespace opengl
  {

ProgramContext::ProgramContext(GLuint programId)
  : m_programId(programId)
{}

void ProgramContext::setUniform(const std::string & name, const glm::mat4 & viewMat)
{
  using cw::core::MakeString;
  LOG_DEBUG("Set uniform: ", name);
  GLint location = glGetAttribLocation(getProgramId(), name.c_str());
  if (location == -1)
    THROW(GlException, (MakeString() << name << " is not a valid location in program: " << getProgramId()));
}

  }
}
