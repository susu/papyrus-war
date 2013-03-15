#include <ctime>

#include <cw/core/Logger.hpp>

namespace cw
{
  namespace core
  {
Logger::Logger( const std::string & loggername )
{}

Logger::~Logger()
{}

std::string getFormattedDate()
{
  time_t rawtime;
  struct tm * timeinfo;
  static char buffer[255];
  time( &rawtime );
  timeinfo = localtime( &rawtime );

  strftime( buffer, 255, "%F %X", timeinfo );
  return buffer;
}

std::string logLevelToStr(Logger::LogLevel level)
{
  switch( level )
  {
    case Logger::ERROR: return "ERROR";
    case Logger::DEBUG: return "DEBUG";
  }
  return "UNDEF";
}

void Logger::startLog( LogLevel loglevel, const char * file, int line,
                       const char * pretty)
{
  getOutputStream() << getFormattedDate() << ' ' <<
                       logLevelToStr(loglevel) << " (" <<
                       file << ':' << line << ") [" <<
                       pretty << "] ";
}

void Logger::endLog()
{
  getOutputStream() << std::endl;
}

StreamGuard::StreamGuard( Logger & logger )
  : m_logger(logger)
  , m_out( logger.getOutputStream() )
{}

StreamGuard::~StreamGuard()
{
  m_logger.endLog();
}

  }
}
