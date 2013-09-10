#ifndef GLSTUB_PROGRAM_REPO_HPP_INC
#define GLSTUB_PROGRAM_REPO_HPP_INC

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <map>
#include <set>
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

        void addAttribute(const std::string & name)
        {
          m_attributeNames.insert(name);
        }

        bool hasAttribute(const std::string & name)
        {
          auto it = m_attributeNames.find(name);
          return it != m_attributeNames.end();
        }

        void uniformMatrix( GLuint matrixId, int matrixSize, const float * matrixPtr )
        {
          LOG_DEBUG();
          for ( int i = 0; i < matrixSize; ++i )
          {
            for ( int j = 0; j < matrixSize; ++j )
            {
              m_unifMat[i][j] = matrixPtr[ j + i * matrixSize ];
            }
          }
        }

        const glm::mat4 & getUnifMat() const
        {
          return m_unifMat;
        }
      private:
        GLuint m_id;
        std::set<std::string> m_attributeNames;
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
