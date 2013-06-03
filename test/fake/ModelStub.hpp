#ifndef FAKE_MODEL_STUB_HPP_INC
#define FAKE_MODEL_STUB_HPP_INC

#include <cw/core/Model.hpp>
#include <cw/core/Pos.hpp>

namespace fake
{
  class ModelStub : public cw::core::Model
  {
    public:
      ModelStub()
      {}

      virtual void tick(double) override
      {}
  };
}

#endif
