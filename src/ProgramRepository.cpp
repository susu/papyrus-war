#include <cw/opengl/ProgramRepository.hpp>

#include <algorithm>
#include <typeinfo>
#include <cw/Enforce.hpp>
#include <cw/opengl/Shader.hpp>

namespace cw
{
  namespace opengl
  {

// ----------- ShaderChain -----------
ShaderChain::ShaderChain(const std::string & chainId)
  : m_chainId(chainId)
{}

void ShaderChain::addShader(GLuint shaderType, std::unique_ptr<core::InputFile> file)
{
  LOG_DEBUG("Adding shader. Type:", opengl::shaderTypeToStr(shaderType),
            " file:", file->getName());
  m_inputFiles.insert( std::make_pair(shaderType, std::move(file)) );
}

void ShaderChain::addShadersToProgram(Program & prog)
{
  for(auto & i : m_inputFiles)
  {
    prog.attachShaderFromFile(std::move(i.second), i.first);
  }
  m_inputFiles.clear();
}

// ----------- ProgramRepository -----------
ProgramRepository::ProgramRepository()
  : m_currentProgram(nullptr)
{}

void ProgramRepository::addShaderChain(ShaderChain && chain)
{
  m_programs.push_back({chain.getId(), Program() });
  chain.addShadersToProgram( m_programs.back().program );
}

bool ProgramRepository::hasProgram(const std::string & chainId) const
{
  return m_programs.end() != findProgram(chainId);
}

void ProgramRepository::selectProgram(const std::string & chainId)
{
  auto it = findProgram(chainId);
  ENFORCE(it != m_programs.end(), "No such program: " + chainId);
  glUseProgram(it->program.getId());
  m_currentProgram = it.base();
}

std::string ProgramRepository::getSelectedProgramId() const
{
  if (m_currentProgram == nullptr)
    return "";
  return m_currentProgram->id;
}

template<typename Iterator>
Iterator findProgramInRange(Iterator first, Iterator last, const std::string & id)
{
  Iterator it = std::find_if(first, last,
  [&id](const typename Iterator::value_type & i)
  {
    return i.id == id;
  });
  return it;
}

ProgramRepository::Programs::const_iterator ProgramRepository::findProgram(const std::string & id) const
{
  return findProgramInRange(m_programs.begin(), m_programs.end(), id);
}

ProgramRepository::Programs::iterator ProgramRepository::findProgram(const std::string & id)
{
  return findProgramInRange(m_programs.begin(), m_programs.end(), id);
}
  }
}
