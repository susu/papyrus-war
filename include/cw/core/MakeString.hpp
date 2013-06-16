#ifndef CW_CORE_MAKE_STRING_HPP_INC
#define CW_CORE_MAKE_STRING_HPP_INC

#include <sstream>

namespace cw
{
  namespace core
  {
    class MakeString
    {
      public:
        MakeString()
        {}

        template<typename T>
        MakeString& operator<<(const T& value)
        {
          m_out << value;
          return *this;
        }

        operator std::string() const
        {
          return m_out.str();
        }
      private:
        std::ostringstream m_out;
    };
  }
}
#endif
