#ifndef CW_CORE_PICKING_INTERFACE_HPP_INC
#define CW_CORE_PICKING_INTERFACE_HPP_INC

#include <cw/core/Pos.hpp>
#include <cw/core/Pos3d.hpp>

namespace cw
{
  namespace core
  {
    class PickingInterface
    {
      public:
        virtual ~PickingInterface() {}
        virtual Pos3d unProject( Pos ) = 0;
    };
  }
}

#endif
