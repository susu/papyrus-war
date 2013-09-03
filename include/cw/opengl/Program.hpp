#ifndef CW_OPENGL_PROGRAM_HPP_INC
#define CW_OPENGL_PROGRAM_HPP_INC

#include <GL/glew.h>
#include <string>
#include <memory>

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

        Program(Program&&) = default;
        Program& operator=(Program&&) = default;

        void attachShaderFromFile(std::unique_ptr<core::InputFile> file, GLuint shaderType);
        void link();
        void check() const;

        GLuint getId() const
        { return m_programId; }

      private:
        Program(Program&);
        Program& operator=(Program&);

        GLuint m_programId;
    };
  }
}

#endif
