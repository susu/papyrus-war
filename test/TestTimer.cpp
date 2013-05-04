#include <cw/core/Timer.hpp>

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

using namespace igloo;

Describe(the_Timer)
{
  const double START_TIME = 10_sec;
  const double DELTA = 1_nanosec;
  cw::core::Timer timer{START_TIME};

  It(can_be_instantiated_with_start_time)
  {
    AssertThat( timer.getElapsed(), EqualsWithDelta( 0_sec, DELTA ) );
  }

  It(can_be_updated)
  {
    timer.updateCurrentTime( START_TIME + 10_millisec );
    AssertThat( timer.getElapsed(), EqualsWithDelta( 10_millisec, DELTA ) );
  }

  It(should_call_back_if_timer_is_expired)
  {
    bool timerExpired = false;
    timer.setUpTimer( 1_sec, [ &timerExpired ]( )
    {
      timerExpired = true;
    });
    AssertThat( timerExpired, Equals(false) );
    timer.updateCurrentTime( START_TIME + 900_millisec );
    AssertThat( timerExpired, Equals(false) );
    timer.updateCurrentTime( START_TIME + 1100_millisec );
    AssertThat( timerExpired, Equals(true) );
  }
};
