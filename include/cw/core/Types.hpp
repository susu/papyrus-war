#ifndef CW_CORE_TYPES_HPP_INC
#define CW_CORE_TYPES_HPP_INC

#include <memory>

namespace cw
{
  namespace core
  {
    class Unit;
    typedef std::shared_ptr<Unit> UnitRef;

    class PaperBoat;
    typedef std::shared_ptr<PaperBoat> PaperBoatRef;
  }
}

#endif
