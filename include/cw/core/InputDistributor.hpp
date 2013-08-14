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
        typedef std::function< bool(ClickEvent) > ClickedOnCondition;

        typedef std::function< void(ScrollEvent) > ScrollCallback;

        InputDistributor();
        virtual ~InputDistributor();

        CallbackId registerClickedOn( ClickedOnCallback, ClickedOnCondition cond = ClickedOnCondition() );
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

        // TODO Pair is compact, but not readable enough. Create separate struct for it!
        std::map< CallbackId, std::pair<ClickedOnCallback,ClickedOnCondition> > m_clickedOnCallbacks;
        std::map< CallbackId, ScrollCallback > m_scrollCallbacks;
    };
  }
}

#endif
