#ifndef TEST_CW_CORE_INPUT_DISTRIBUTOR_HPP_INC
#define TEST_CW_CORE_INPUT_DISTRIBUTOR_HPP_INC

#include <cw/core/InputDistributor.hpp>

using namespace igloo;

Describe(the_InputDistributor)
{
  typedef cw::core::InputDistributor::CallbackId CallbackId;

  cw::core::InputDistributor dist;
  bool eventOccured;
  cw::core::ClickEvent lastEvent;

  int actualNumberOfCalls;
  int expectedNumberOfCalls;

  // It(should_be_registerable)
  void SetUp()
  {
    eventOccured = false;
    dist.registerClickedOn( [this](cw::core::ClickEvent ev)
    {
      lastEvent = ev;
      eventOccured = true;
    });
    actualNumberOfCalls = 0;
    expectedNumberOfCalls = 0;
  }

  CallbackId registerSelfCheckerCallback( cw::core::Pos expectedPos )
  {
    CallbackId id = dist.registerClickedOn( [this,expectedPos](cw::core::ClickEvent ev)
    {
      ++actualNumberOfCalls;
      AssertThat( ev.pos, Equals( expectedPos ) );
    });
    ++expectedNumberOfCalls;
    return id;
  }

  It(should_register_and_call_multiple_callbacks)
  {
    cw::core::Pos expectedPos( 100.0, 100.0 );
    registerSelfCheckerCallback( expectedPos );
    registerSelfCheckerCallback( expectedPos );
    registerSelfCheckerCallback( expectedPos );
    registerSelfCheckerCallback( expectedPos );

    dist.clickedAt( 100, 100 );
    AssertThat( actualNumberOfCalls, Equals( expectedNumberOfCalls ) );
  }

  It(should_call_the_callback_if_clickedAt_happened)
  {
    dist.clickedAt( 100, 100 );
    AssertThat( eventOccured, Equals(true) );
    AssertThat( lastEvent.pos, Equals( cw::core::Pos( 100.0, 100.0 ) ) );
  }

  It(should_return_its_callbackId)
  {
    CallbackId id;
    id = dist.registerClickedOn([](cw::core::ClickEvent){});
    if(id){}
  }

  It(should_deregister_callbacks)
  {
    cw::core::Pos expectedPos( 100.0, 100.0 );
    CallbackId id1, id2;
    id1 = registerSelfCheckerCallback( expectedPos );
    id2 = registerSelfCheckerCallback( expectedPos );

    dist.unregisterClickedOn( id2 );
    --expectedNumberOfCalls;
    dist.clickedAt( 100, 100 );

    AssertThat( actualNumberOfCalls, Equals( expectedNumberOfCalls ) );
    dist.unregisterClickedOn( id1 );
    dist.unregisterClickedOn( id2 );
  }

  // TODO mapping pixel coordinates into WorldCoordinates with ProjectionView...
};

#endif
