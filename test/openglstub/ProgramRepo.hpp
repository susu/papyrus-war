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

class Program
{
  public:
    Program(GLuint id);

    Program(Program&) =delete;
    Program& operator=(Program&) =delete;

    GLuint getId() const
    { return m_id; }

    void addUniform(const std::string & name);
    bool hasUniform(const std::string & name);
    GLint getUniformIndex(const std::string & name) const;
    void uniformMatrix( GLuint matrixId, int matrixSize, const float * matrixPtr );
    const glm::mat4 & getUniformMatrix4fv(GLuint matrixId) const;
    void dump() const;
  private:
    GLuint m_id;
    std::vector<std::string> m_uniformNames;
    std::unordered_map<GLuint, glm::mat4> m_4x4_matrices;
};

class ProgramRepo
{
  public:
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
