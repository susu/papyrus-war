#include <ctime>

#include <cw/core/Logger.hpp>

namespace cw
{
  namespace core
  {
Logger::Logger( const std::string & loggername )
  : m_outputStream( &std::cout )
{}

Logger::~Logger()
{}

std::string getFormattedDate()
{
  // TODO std::chrono
  time_t rawtime;
  struct tm * timeinfo;
  static char buffer[255];
  time( &rawtime );
  timeinfo = localtime( &rawtime );

  strftime( buffer, 255, "%F %X", timeinfo );
  return buffer;
}

const char* logLevelToStr(LogLevel level)
{
  switch( level )
  {
    case LogLevel::ERROR: return "ERROR";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::INFO: return "INFO";
    case LogLevel::DEBUG: return "DEBUG";
    case LogLevel::FINE: return "FINE";
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

StreamGuard::StreamGuard( Logger & logger, LogDetails details )
  : m_logger(logger)
  , m_details(details)
{}

StreamGuard::~StreamGuard()
{
  m_logger.endLog();
}

  }
}
