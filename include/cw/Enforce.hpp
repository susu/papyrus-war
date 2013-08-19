#ifndef CW_ENFORCE_HPP_INC
#define CW_ENFORCE_HPP_INC

#include <cw/core/BaseException.hpp>

#define ENFORCE(cond,msg)\
  cw::enforce<cw::core::BaseException>((cond),__FILE__,__LINE__,\
      cw::core::MakeString()<<"ENFORCE FAILED! "<<(msg));

namespace cw
{
  template<class E, class... Arg>
  inline void enforce(bool condition, Arg&&... arg)
  {
    if (!condition)
    {
      throw E(std::forward<Arg>(arg)...);
    }
  }
}

#endif
