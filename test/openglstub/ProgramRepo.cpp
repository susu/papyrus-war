#include "ProgramRepo.hpp"

Program::Program( GLuint id )
  : m_id(id)
{}


void Program::addUniform(const std::string & name)
{
  m_uniformNames.push_back(name);
}

bool Program::hasUniform(const std::string & name)
{
  auto it = std::find(begin(m_uniformNames), end(m_uniformNames), name);
  return it != m_uniformNames.end();
}

GLint Program::getUniformIndex(const std::string & name) const
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

void Program::uniformMatrix(GLuint matrixId, int matrixSize, const float * matrixPtr)
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

const glm::mat4 & Program::getUniformMatrix4fv(GLuint matrixId) const
{
  LOG_FINE("uniform-id=", matrixId, " program-id=", getId());
  auto it = m_4x4_matrices.find(matrixId);
  ENFORCE(it != m_4x4_matrices.end(), "Non-existent uniform matrix id (4x4): " << matrixId);
  LOG_FINE("found");
  return m_4x4_matrices.find(matrixId)->second;
}

void Program::dump() const
{
  LOG_DEBUG("DUMP programId=", getId());
  for (auto const & i : m_4x4_matrices)
  {
    LOG_DEBUG("matrixId: ", i.first);
  }
}
