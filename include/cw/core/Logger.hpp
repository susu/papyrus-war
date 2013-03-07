#ifndef CW_CORE_LOGGER_HPP_INC
#define CW_CORE_LOGGER_HPP_INC

#include <iostream>
#include <fstream>

#ifdef CW_DEBUG

#define LOG_MSG(loglevel) \
  logger.getGuardedStream( (loglevel), __FILE__, __LINE__, __PRETTY_FUNCTION__ )

#else // CW_DEBUG

#define LOG_MSG(a) logger.getNullStream()

#endif

#define LOG(level) LOG_MSG(cw::core::Logger::level)

#define LOG_EXCEPTION( ex ) \
   LOG(ERROR) << "Exception: '" << ex.what() << "'"


namespace cw
{
  namespace core
  {
    class Logger;
    class StreamGuard
    {
      public:
        StreamGuard( Logger & logger );
        ~StreamGuard();

        template<typename T>
        StreamGuard& operator<<( const T & val )
        {
          m_out << val;
          return *this;
        }
      private:
        Logger & m_logger;
        std::ostream & m_out;
    };
    class Logger
    {
      public:
        enum LogLevel
        {
          ERROR,
          DEBUG
        };
        Logger( const std::string & loggerName );
        ~Logger();

        StreamGuard getGuardedStream( LogLevel loglevel, const char * file, int line,
                                      const char * pretty)
        {
          startLog(loglevel, file, line, pretty);
          return StreamGuard(*this);
        }

        std::ostream& getOutputStream()
        {
          return std::cout;
        }

        std::ostream& getNullStream()
        {
          return m_null;
        }

        void endLog();
      private:
        void startLog( LogLevel loglevel, const char * file, int line,
                       const char * pretty);
        std::ofstream m_null;
    };
  }
}

#endif
