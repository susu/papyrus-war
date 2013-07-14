#ifndef CW_CORE_SURFACE_HPP_INC
#define CW_CORE_SURFACE_HPP_INC

#include <cw/core/Model.hpp>

namespace cw
{
  namespace core
  {
    class Surface : public Model
    {
      public:
        Surface();
        virtual ~Surface();

        // Surface is a special model, it cannot have a focus
        void onFocused() override {}
        void onDeFocused() override {}
        void onOuterClick(Pos click, Ref<Model>::R clickedModel) override {}

        void tick(double diffTime) override;
    };

  }
}

#endif
