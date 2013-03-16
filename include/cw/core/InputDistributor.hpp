#ifndef CW_CORE_INPUT_DISTRIBUTOR_HPP_INC
#define CW_CORE_INPUT_DISTRIBUTOR_HPP_INC

#include <set>

#include <cw/core/Types.hpp>
#include <cw/core/UnifiedInputHandler.hpp>

namespace cw
{
  namespace core
  {
    class InputDistributor : public UnifiedInputHandler
    {
      public:
        InputDistributor();
        virtual ~InputDistributor();
        void registerUnit( UnitRef unit );

        virtual void clickedAt(int x, int y) override;
        virtual void zoom(ZoomDir dir) override;
        virtual void startScroll(ScrollDir dir) override;
        virtual void stopScroll() override;
      private:
        std::set<UnitRef> m_units;
    };
  }
}

#endif
