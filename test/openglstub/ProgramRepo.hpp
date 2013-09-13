#ifndef GLSTUB_PROGRAM_REPO_HPP_INC
#define GLSTUB_PROGRAM_REPO_HPP_INC

#include "GL/glew.h"
#include <glm/glm.hpp>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include <cw/Enforce.hpp>
#include <cw/core/Logger.hpp>
#include <cw/core/MakeString.hpp>

class ProgramRepo
{
  public:
    class Program
    {
      public:
        Program( GLuint id )
          : m_id(id)
        {}

        Program(Program&) =delete;
        Program& operator=(Program&) =delete;

        GLuint getId() const
        { return m_id; }

        void addUniform(const std::string & name)
        {
          m_uniformNames.push_back(name);
        }

        bool hasUniform(const std::string & name)
        {
          auto it = std::find(begin(m_uniformNames), end(m_uniformNames), name);
          return it != m_uniformNames.end();
        }

        GLint getUniformIndex(const std::string & name) const
        {
          int count = 0;
          for (const auto & i : m_uniformNames)
          {
            if (i == name)
            {
              return count;
            }
            ++count;
          }
          return -1;
        }

        void uniformMatrix( GLuint matrixId, int matrixSize, const float * matrixPtr )
        {
          LOG_DEBUG("Storing uniformMatrix (4x4) with uniform-id=", matrixId,
                    " program-id=", getId());
          glm::mat4 mat;
          for ( int i = 0; i < matrixSize; ++i )
          {
            for ( int j = 0; j < matrixSize; ++j )
            {
              mat[i][j] = matrixPtr[ j + i * matrixSize ];
            }
          }

          m_4x4_matrices.insert({matrixId,mat});
        }

        const glm::mat4 & getUniformMatrix4fv(GLuint matrixId) const
        {
          LOG_FINE("uniform-id=", matrixId, " program-id=", getId());
          auto it = m_4x4_matrices.find(matrixId);
          ENFORCE(it != m_4x4_matrices.end(), "Non-existent uniform matrix id (4x4): " << matrixId);
          LOG_FINE("found");
          return m_4x4_matrices.find(matrixId)->second;
        }

        void dump() const
        {
          LOG_DEBUG("DUMP programId=", getId());
          for (auto const & i : m_4x4_matrices)
          {
            LOG_DEBUG("matrixId: ", i.first);
          }
        }
      private:
        GLuint m_id;
        std::vector<std::string> m_uniformNames;
        std::unordered_map<GLuint, glm::mat4> m_4x4_matrices;
    };

    ProgramRepo()
      : nextId(0)
    {}

    GLuint createProgram()
    {
      // m_programs.insert( std::make_pair(nextId, Program(nextId) ) );
      m_programs[nextId] = std::make_unique<Program>(nextId);
      ++nextId;
      return nextId-1;
    }

    Program& getProgram( GLuint programid )
    {
      auto prog = m_programs.find( programid );
      assert( prog != m_programs.end() );
      return *prog->second;
    }
  private:
    std::map< GLuint, std::unique_ptr<Program> > m_programs;
    int nextId;
};

#endif
