#ifndef CW_CORE_EXCEPTION_HPP_INC
#define CW_CORE_EXCEPTION_HPP_INC

#include <iostream>
#include <exception>
#include <cw/core/MakeString.hpp>

#define THROW(type,msg) \
  throw type(__FILE__,__LINE__,(msg))

namespace cw
{
  namespace core
  {
    class BaseException
    {
      public:
        BaseException(const char * file, int line, const std::string & msg)
          : m_file(file)
          , m_line(line)
          , m_msg(msg)
        {}

        std::string getMessage() const noexcept
        {
          return MakeString() << "thrown at " <<
                 m_file << ":" << m_line << " message: '" <<
                 m_msg << "'";
        }
      private:
        const char * m_file;
        int m_line;
        std::string m_msg;
    };
  }
}

#endif
