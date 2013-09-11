#ifndef CW_CORE_EXCEPTION_HPP_INC
#define CW_CORE_EXCEPTION_HPP_INC

#include <iostream>
#include <exception>
#include <cw/core/MakeString.hpp>

#include <cpp11hacks.hpp>

#define THROW(type,msg) \
  throw type(__FILE__,__LINE__,(msg))

namespace cw
{
  namespace core
  {
    class BaseException : public std::exception
    {
      public:
        BaseException(const char * file, int line, const std::string & msg)
          : m_whatMessage(constructWhatMessage(file, line, msg))
        {}

        const std::string & getMessage() const noexcept
        {
          return m_whatMessage;
        }

        const char* what() const noexcept override
        {
          return m_whatMessage.c_str();
        }
      private:
        static std::string constructWhatMessage(const char * file,
                                                int line,
                                                const std::string & msg) noexcept
        {
          return MakeString() << "thrown at " <<
                 file << ":" << line << " message: '" <<
                 msg << "'";
        }
        std::string m_whatMessage;
    };
  }
}

#endif
