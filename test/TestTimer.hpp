#ifndef TEST_TIMER_HPP_INC
#define TEST_TIMER_HPP_INC

#include <cw/core/Timer.hpp>

#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

using namespace igloo;

Describe(the_Timer)
{
  const double START_TIME = 10_sec;
  const double DELTA = 1_nanosec;
  It(can_be_instantiated_with_start_time)
  {
    cw::core::Timer timer{START_TIME};
    AssertThat( timer.getElapsed(), EqualsWithDelta( 0_sec, DELTA ) );
  }

  It(can_be_updated)
  {
    cw::core::Timer timer{START_TIME};
    timer.updateCurrentTime( START_TIME + 10_millisec );
    AssertThat( timer.getElapsed(), EqualsWithDelta( 10_millisec, DELTA ) );
  }
};

#endif
