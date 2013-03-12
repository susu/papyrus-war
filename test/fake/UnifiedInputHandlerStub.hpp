#ifndef FAKE_UNIFIED_INPUT_HANDLER_STUB_HPP_INC
#define FAKE_UNIFIED_INPUT_HANDLER_STUB_HPP_INC

#include <cw/core/UnifiedInputHandler.hpp>

namespace fake
{
  class UnifiedInputHandlerStub : public cw::core::UnifiedInputHandler
  {
    public:
      UnifiedInputHandlerStub()
      {}
      virtual void clickedAt(int x, int y)
      {}

      virtual void zoom(ZoomDir direction)
      {}

      virtual void startScroll(ScrollDir direction)
      {}

      virtual void stopScroll()
      {}
  };
}

#endif
