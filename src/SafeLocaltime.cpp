#include <cw/core/SafeLocaltime.hpp>

namespace cw
{
  namespace core
  {
std::tm safeLocaltime(std::time_t * currentTime)
{
  std::tm result;
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
  localtime_s(&result, currentTime);
#else
  localtime_r(currentTime, &result);
#endif
  return result;
}
  }
}
