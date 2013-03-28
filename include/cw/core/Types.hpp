#ifndef CW_CORE_TYPES_HPP_INC
#define CW_CORE_TYPES_HPP_INC

#include <memory>

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

#endif
