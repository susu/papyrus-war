#ifndef CW_CORE_INPUT_DISTRIBUTOR_HPP_INC
#define CW_CORE_INPUT_DISTRIBUTOR_HPP_INC

#include <set>

#include <cw/core/Types.hpp>
#include <cw/core/UnifiedInputHandler.hpp>

namespace cw
{
  namespace core
  {
    class Model;
    class InputDistributor : public UnifiedInputHandler
    {
      public:
        InputDistributor();
        virtual ~InputDistributor();
        void registerModel( Ref<Model> model );

        virtual void clickedAt(int x, int y) override;
        virtual void zoom(ZoomDir dir) override;
        virtual void startScroll(ScrollDir dir) override;
        virtual void stopScroll() override;
      private:
        std::set<Ref<Model>> m_models;
    };
  }
}

#endif
