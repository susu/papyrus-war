#ifndef CW_OPENGL_SHADER_HPP_INC
#define CW_OPENGL_SHADER_HPP_INC

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
    class Shader
    {
      public:
        Shader(core::InputFile & file, GLenum shaderType);

        ~Shader();

        void read();
        void compile();
        void check();
        void attachProgram( GLuint programId ) const;

        GLuint getShaderId() const;

      private:
        Shader(Shader&);
        void operator=(Shader);

        std::string getLogMessageHeader() const;

        core::InputFile & m_file;
        std::string  m_filecontent;
        GLuint       m_shaderId;
        GLint        m_shaderType;
    };
  }
}

#endif
