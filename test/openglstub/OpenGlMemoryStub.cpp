#include "OpenGlMemoryStub.hpp"

std::unique_ptr<OpenGlMemoryStub> OpenGlMemoryStub::s_instance;

OpenGlMemoryStub& OpenGlMemoryStub::instance()
{
  if (s_instance == nullptr)
  {
    s_instance.reset(new OpenGlMemoryStub);
  }
  return *s_instance;
}

OpenGlMemoryStub::OpenGlMemoryStub()
  : m_boundVBO(-1)
  , m_lastIndex(1)
{}

OpenGlMemoryStub::VBO& OpenGlMemoryStub::getBoundVBO()
{
  ENFORCE(m_boundVBO != -1, "No VBO is bound at the moment!");
  auto it = m_VBOs.find(m_boundVBO);
  ENFORCE(it != m_VBOs.end(), "VBO not exists: " + std::to_string(m_boundVBO));
  return it->second;
}

const OpenGlMemoryStub::VBO& OpenGlMemoryStub::getVBO(GLint index) const
{
  auto it = m_VBOs.find(index);
  ENFORCE(it != m_VBOs.end(), "VBO not exists: " + std::to_string(index));
  return it->second;
}

GLuint OpenGlMemoryStub::generateVBO()
{
  auto nextIndex = getNextIndex();
  m_VBOs[nextIndex] = VBO();
  return nextIndex;
}

GLint OpenGlMemoryStub::getNextIndex()
{
  return ++m_lastIndex;
}

void OpenGlMemoryStub::boundVBO(GLint index)
{
  ENFORCE(m_VBOs.find(index) != m_VBOs.end(), "VBO not exists: " + std::to_string(index));
  m_boundVBO = index;
}
