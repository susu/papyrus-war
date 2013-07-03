#ifndef CW_CORE_SAFE_LOCALTIME_HPP_INC
#define CW_CORE_SAFE_LOCALTIME_HPP_INC

namespace cw
{
  namespace core
  {
    /**
     *  Threadsafe version of localtime
     *  NOTE: on win:  localtime_s is used
     *        on other(POSIX): localtime_r is used
     */
    std::tm * safeLocaltime(std::time_t * currentTime);
  }
}



#endif
