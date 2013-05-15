#include <igloo/igloo.h>
#include <igloo/igloo_alt.h>

#include "fake/PickingStub.hpp"

#include <cw/core/InputDistributor.hpp>

using namespace igloo;

Describe(AInputDistributor)
{
  typedef cw::core::InputDistributor::CallbackId CallbackId;

  fake::PickingStub pickingStub;
  cw::core::InputDistributor dist;
  bool eventOccured;
  cw::core::ClickEvent lastEvent;

  int actualNumberOfCalls;
  int expectedNumberOfCalls;

  AInputDistributor()
    : dist( pickingStub )
  {}

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
  It(should_map_2D_mouse_coordinates_into_3D_WorldCoordinates)
  {
    // NOTE assuming surface is at Z=0
  }

  It(can_register_scroll)
  {
    dist.registerScroll([](cw::core::ScrollEvent ev){});
  }

  It(should_call_scroll_callback)
  {
    bool isCalled = false;
    dist.registerScroll([&isCalled](cw::core::ScrollEvent ev)
    {
      isCalled = true;
    });
    dist.startScroll( cw::core::ScrollDir::UP );
    AssertThat(isCalled,Equals(true));
  }

  It(should_call_scroll_callback_with_proper_values)
  {
    cw::core::ScrollEvent startEvent, stopEvent;
    auto cb = [&startEvent,&stopEvent](cw::core::ScrollEvent ev)
    {
      if (ev.action == cw::core::ScrollEvent::START)
        startEvent = ev;
      else
        stopEvent = ev;
    };

    dist.registerScroll(cb);

    dist.startScroll(cw::core::ScrollDir::LEFT);
    AssertThat(startEvent.action, Equals(cw::core::ScrollEvent::START));
    AssertThat(startEvent.scrollDir, Equals(cw::core::ScrollDir::LEFT));


    dist.stopScroll();
    AssertThat(stopEvent.action, Equals(cw::core::ScrollEvent::STOP));
    AssertThat(stopEvent.scrollDir, Equals(cw::core::ScrollDir::LEFT));
  }

};
