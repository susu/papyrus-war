#ifndef CW_CORE_INPUT_DISTRIBUTOR_HPP_INC
#define CW_CORE_INPUT_DISTRIBUTOR_HPP_INC

#include <map>
#include <functional>

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
    struct ScrollEvent
    {
      enum Action
      {
        START,
        STOP
      };
      ScrollDir scrollDir;
      Action action;
    };
    class InputDistributor : public UnifiedInputHandler
    {
      public:
        typedef unsigned long long CallbackId;
        typedef std::function< void(ClickEvent) > ClickedOnCallback;
        typedef std::function< void(ScrollEvent) > ScrollCallback;

        InputDistributor( const PickingInterface & );
        virtual ~InputDistributor();

        CallbackId registerClickedOn( ClickedOnCallback );
        void unregisterClickedOn( CallbackId );

        CallbackId registerScroll( ScrollCallback );
        void unregisterScroll( CallbackId );

        virtual void clickedAt(int x, int y) override; //< pixel-level
        virtual void zoom(ZoomDir dir) override;
        virtual void startScroll(ScrollDir dir) override;
        virtual void stopScroll(ScrollDir dir) override;


      private:
        InputDistributor(InputDistributor&);
        InputDistributor& operator=(InputDistributor);

        std::map< CallbackId, ClickedOnCallback > m_clickedOnCallbacks;
        std::map< CallbackId, ScrollCallback > m_scrollCallbacks;
        const PickingInterface & m_picking;
    };
  }
}

#endif
