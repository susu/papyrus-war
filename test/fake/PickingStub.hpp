#ifndef FAKE_PICKING_STUB_HPP_INC
#define FAKE_PICKING_STUB_HPP_INC

#include <cw/core/PickingInterface.hpp>

namespace fake
{
  class PickingStub : public cw::core::PickingInterface
  {
    public:
      PickingStub()
      {}

      virtual ~PickingStub()
      {}
  };
}

#endif
