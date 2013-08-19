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
        : m_over(false)
      {}

      // @{ stubbed methods
      void tick(double) override
      {}

      bool isOver(cw::core::Pos pos) const override
      {
        return m_over;
      }

      void onOuterClick(cw::core::Pos click, Ref<cw::core::Model>::R clickedModel) override
      {}

      Polygon getBoundingBox() override
      { return {}; }
      // @}

      // @{ helper methods
      bool & over()
      { return m_over; }
      // @}


    private:
      void onFocused() override
      {}

      void onDeFocused() override
      {}

      bool m_over;
  };
}

#endif
