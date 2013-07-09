#include <cw/core/Timer.hpp>

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

using namespace igloo;

Describe(the_Timer)
{
  const double START_TIME = 10.0;
  const double DELTA = 1 * 0.001 * 0.001 * 0.001;// 1_nanosec
  cw::core::Timer timer{START_TIME};

  It(can_be_instantiated_with_start_time)
  {
    AssertThat( timer.getElapsed(), EqualsWithDelta( 0.0, DELTA ) );
  }

  It(can_be_updated)
  {
    timer.updateCurrentTime( START_TIME + 10 * 0.001 /* 10_millisec */ );
    AssertThat( timer.getElapsed(), EqualsWithDelta( 10 * 0.001 /* 10_millisec */, DELTA ) );
  }

  It(should_call_back_if_timer_is_expired)
  {
    bool timerExpired = false;
    timer.setUpTimer( 1.0, [ &timerExpired ]( )
    {
      timerExpired = true;
    });
    AssertThat( timerExpired, Equals(false) );
    timer.updateCurrentTime( START_TIME + 0.900 );
    AssertThat( timerExpired, Equals(false) );
    timer.updateCurrentTime( START_TIME + 1.100 );
    AssertThat( timerExpired, Equals(true) );
  }
};
