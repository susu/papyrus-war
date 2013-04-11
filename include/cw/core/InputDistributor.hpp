#ifndef CW_CORE_INPUT_DISTRIBUTOR_HPP_INC
#define CW_CORE_INPUT_DISTRIBUTOR_HPP_INC

#include <map>

#include <cw/core/Types.hpp>
#include <cw/core/Pos.hpp>
#include <cw/core/UnifiedInputHandler.hpp>

namespace cw
{
  namespace core
  {
    class PickingInterface;
    struct ClickEvent
    {
      Pos pos;
    };
    class InputDistributor : public UnifiedInputHandler
    {
      public:
        typedef unsigned long long CallbackId;
        typedef std::function< void(ClickEvent) > ClickedOnCallback;
        InputDistributor( const PickingInterface & );
        virtual ~InputDistributor();

        CallbackId registerClickedOn( ClickedOnCallback );
        void unregisterClickedOn( CallbackId );

        virtual void clickedAt(int x, int y) override; //< pixel-level
        virtual void zoom(ZoomDir dir) override;
        virtual void startScroll(ScrollDir dir) override;
        virtual void stopScroll() override;
      private:
        CallbackId getNextKey() const;
        std::map< CallbackId, ClickedOnCallback > m_clickedOnCallbacks;
        const PickingInterface & m_picking;
    };
  }
}

#endif
