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

      void tick(double) override
      {}

      void onFocused() override
      {}

      void onDeFocused() override
      {}

      void onOuterClick(cw::core::Pos click, Ref<cw::core::Model>::R clickedModel) override
      {}

  };
}

#endif
