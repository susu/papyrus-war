#ifndef CW_OPENGL_PROGRAM_HPP_INC
#define CW_OPENGL_PROGRAM_HPP_INC

#include <GL/glew.h>
#include <string>

namespace cw
{
  namespace core
  {
    class InputFile;
  }
  namespace opengl
  {
    class Program
    {
      public:
        Program();
        ~Program();

        void attachShaderFromFile(core::InputFile && file, GLuint shaderType);
        void link();
        void check() const;

        GLuint getId() const
        { return m_programId; }

      private:
        GLuint m_programId;
    };
  }
}

#endif
