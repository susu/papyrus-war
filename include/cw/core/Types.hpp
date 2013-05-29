#ifndef CW_CORE_TYPES_HPP_INC
#define CW_CORE_TYPES_HPP_INC

#include <memory>
#include <type_traits>

template<class T>
using Ref = std::shared_ptr<T>;

namespace cw
{
  namespace core
  {
    class PaperBoat;
    typedef Ref<PaperBoat> PaperBoatRef;
  }
}

template<typename EnumClass>
auto to_underlying(EnumClass e) -> typename std::underlying_type<EnumClass>::type
{
  return static_cast<typename std::underlying_type<EnumClass>::type>(e);
}

#endif
