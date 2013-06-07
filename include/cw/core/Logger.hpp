#ifndef CW_CORE_LOGGER_HPP_INC
#define CW_CORE_LOGGER_HPP_INC

#include <iostream>
#include <fstream>

#ifdef CW_DEBUG

#define LOG_DEBUG LOG_MSG(cw::core::DEBUG)
#define LOG_FINE  LOG_MSG(cw::core::FINE)

#else // CW_DEBUG

#define LOG_DEBUG(...)
#define LOG_FINE(...)

#endif

#define LOG_MSG(loglevel) \
  cw::core::Logger::instance().getGuardedStream( \
      cw::core::LogDetails{\
        (loglevel), __FILE__, __LINE__, __PRETTY_FUNCTION__} )


// errors,warnings,infos always logged
#define LOG_ERROR LOG_MSG(cw::core::ERROR)
#define LOG_WARNING LOG_MSG(cw::core::WARNING)
#define LOG_INFO  LOG_MSG(cw::core::INFO)

#define LOG_EXCEPTION( ex ) \
   LOG_ERROR("Exception: '", (ex).what(), "'")


namespace cw
{
  namespace core
  {
    class Logger;
    enum LogLevel
    {
      // The following severity levels always compiled into build.
      ERROR,
      WARNING,
      INFO,

      // The following severity levels are not compiled into release build.
      DEBUG,
      FINE
    };
    struct LogDetails
    {
      LogLevel loglevel;
      const char* file;
      int line;
      const char* pretty;
    };

    class StreamGuard
    {
      public:
        StreamGuard(Logger & logger, LogDetails details);
        ~StreamGuard();

        template<typename...Args>
        void operator()(Args...args)
        {
          m_logger(m_details,args...);
        }
      private:
        Logger & m_logger;
        LogDetails m_details;
    };
    class Logger
    {
      public:
        ~Logger();
        static Logger& instance()
        {
          static Logger logger("logger");
          return logger;
        }

        StreamGuard getGuardedStream(LogDetails details)
        {
          return StreamGuard(*this, details);
        }

        template<typename...Args>
        void operator()(LogDetails details, Args...args)
        {
          startLog(details.loglevel, details.file, details.line, details.pretty);
          print(args...);
        }

        void endLog();
      private:
        Logger( const std::string & loggerName );

        void startLog( LogLevel loglevel, const char * file, int line,
                       const char * pretty);
        std::ostream& getOutputStream()
        { return *m_outputStream; }

        template<typename First,typename...Args>
        void print(First first, Args...args)
        {
          getOutputStream() << first;
          print(args...);
        }

        void print()
        {}

        std::ostream * m_outputStream;
    };
  }
}

#endif
