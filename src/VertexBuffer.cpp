#include <cw/opengl/VertexBuffer.hpp>

namespace cw
{
  namespace opengl
  {

VertexBuffer::VertexBuffer(ByteType size)
  : m_fullVboSize(size)
{
  glGenBuffers(1, &m_bufferIndex);
  glBindBuffer(GL_ARRAY_BUFFER, m_bufferIndex);
  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{}

GLint VertexBuffer::getIndex() const
{
  return m_bufferIndex;
}

ByteType VertexBuffer::getFullSize() const
{
  return m_fullVboSize;
}

void VertexBuffer::requestMemory(ByteType)
{}

  }
}
