#include <cw/opengl/ProgramContext.hpp>

#include <glm/gtc/type_ptr.hpp>

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
  GLint uniformId = glGetUniformLocation(getProgramId(), name.c_str());
  if (uniformId == -1)
    THROW(GlException, (MakeString() << name << " is not a valid location in program: " << getProgramId()));
  glUniformMatrix4fv(uniformId, 1, GL_FALSE, glm::value_ptr(viewMat));
}

  }
}
