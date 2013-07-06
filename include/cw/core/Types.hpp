#ifndef CW_CORE_TYPES_HPP_INC
#define CW_CORE_TYPES_HPP_INC

#include <memory>
#include <type_traits>

#include <cpp11hacks.hpp>

template<class T>
struct Ref
{
  typedef std::shared_ptr<T> R;
  private:
    Ref();
};

namespace cw
{
  namespace core
  {
    class PaperBoat;
    typedef Ref<PaperBoat>::R PaperBoatRef;
  }
}

template<typename EnumClass>
auto to_underlying(EnumClass e) -> typename std::underlying_type<EnumClass>::type
{
  return static_cast<typename std::underlying_type<EnumClass>::type>(e);
}

#endif
