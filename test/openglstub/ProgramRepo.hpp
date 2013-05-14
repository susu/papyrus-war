#ifndef GLSTUB_PROGRAM_REPO_HPP_INC
#define GLSTUB_PROGRAM_REPO_HPP_INC

#include <glm/glm.hpp>

#include <cw/core/Logger.hpp>

class ProgramRepo
{
  public:
    class Program
    {
      public:
        Program( GLuint id )
          : m_id(id)
        {}

        void uniformMatrix( GLuint matrixId, const float * matrixPtr )
        {
          LOG_DEBUG();
          const int MATRIX_SIZE = 4;
          for ( int i = 0; i < MATRIX_SIZE; ++i )
          {
            for ( int j = 0; j < MATRIX_SIZE; ++j )
            {
              m_unifMat[i][j] = matrixPtr[ j + i * MATRIX_SIZE ];
            }
          }
        }

        const glm::mat4 & getUnifMat() const
        {
          return m_unifMat;
        }
      private:
        GLuint m_id;
        glm::mat4 m_unifMat;
    };

    ProgramRepo()
      : nextId(0)
    {}

    GLuint createProgram()
    {
      m_programs.insert( { nextId, Program(nextId) } );
      ++nextId;
      return nextId-1;
    }

    Program& getProgram( GLuint programid )
    {
      auto prog = m_programs.find( programid );
      assert( prog != m_programs.end() );
      return prog->second;
    }
  private:
    std::map< GLuint, Program > m_programs;
    int nextId;
};

#endif
