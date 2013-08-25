#include <cw/core/IFStreamFile.hpp>

#include <cw/Enforce.hpp>
#include <cw/core/Logger.hpp>

namespace cw
{
  namespace core
  {

IFStreamFile::IFStreamFile(const std::string & name)
  : InputFile(name)
{}

IFStreamFile::~IFStreamFile()
{
  // however std::ifstream closes in its destructor,
  // we close the file here to keep consistency
  close();
}

bool IFStreamFile::doOpen()
{
  LOG_DEBUG("Opening file: ", getName());
  m_ifs.open(getName());
  if (m_ifs.fail())
    LOG_ERROR("Cannot open file: ", getName(), " failbit=", m_ifs.fail());
  return m_ifs.is_open();
}

void IFStreamFile::doClose()
{
  m_ifs.close();
}

std::string IFStreamFile::readAll()
{
  ENFORCE(m_ifs.is_open(), "File must be opened before reading it!");
  LOG_DEBUG("Read all data from file: ", getName());

  std::string line;
  std::string data;
  while(getline(m_ifs, line))
  {
    LOG_FINE("line read: '", line, "'");
    data.append(line + "\n");
  }
  return data;
}

char IFStreamFile::readChar()
{
  ENFORCE(m_ifs.is_open(), "File must be opened before reading it!");
  return char(m_ifs.get());
}

bool IFStreamFile::isEndOfFile() const
{
  return m_ifs.eof();
}

  }
}
