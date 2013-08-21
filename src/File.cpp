#include <cw/core/File.hpp>

namespace cw
{
  namespace core
  {

File::File(const std::string & fileName)
  : m_fileName(fileName)
  , m_opened(false)
{}

File::~File()
{}

std::string File::getName() const
{
  return m_fileName;
}

bool File::isOpen() const
{
  return m_opened;
}

bool File::open()
{
  if (!isOpen())
  {
    m_opened = doOpen();
    return m_opened;
  }
  return false;
}

void File::close()
{
  if (isOpen())
  {
    m_opened = false;
    doClose();
  }
}

  }
}
