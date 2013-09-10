#ifndef CW_OPENGL_PROGRAMCONTEXT_HPP_INC
#define CW_OPENGL_PROGRAMCONTEXT_HPP_INC

#include "GL/glew.h"
#include <string>
#include <glm/glm.hpp>

namespace cw
{
  namespace opengl
  {
    class ProgramContext
    {
      public:
        ProgramContext(GLuint programId);

        void setUniform(const std::string & name, const glm::mat4 & mat);
      private:
        GLint getProgramId() const
        { return m_programId; }

        GLint m_programId;
    };
  }
}

#endif
