#ifndef CW_ENFORCE_HPP_INC
#define CW_ENFORCE_HPP_INC

#include <stdexcept>

#define ENFORCE(cond,msg)\
  cw::enforce<std::logic_error>(cond,msg);

namespace cw
{
  template<class E, class Arg>
  inline void enforce(bool condition, Arg arg)
  {
    if (!condition)
    {
      throw E(arg);
    }
  }
}

#endif
