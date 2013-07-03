#ifndef CW_OPENGL_SHADER_HPP_INC
#define CW_OPENGL_SHADER_HPP_INC

#include <GL/glew.h>

#include <string>

namespace cw
{
  namespace opengl
  {
    class Shader
    {
      public:
        Shader( const std::string & filename, GLenum shaderType );

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

        const std::string m_filename;
        std::string       m_filecontent;
        GLuint            m_shaderId;
        GLint             m_shaderType;
    };
  }
}

#endif
